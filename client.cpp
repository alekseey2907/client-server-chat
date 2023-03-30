#include "client.h"
#include "ui_client.h"
#include <QDebug>
#include <QAbstractSocket>
Client::Client(QSettings *settings, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client),
    settings(settings)
{
    ui->setupUi(this);
    setWindowTitle("");

    /* Если параметры сети уже установлены */
    if (settings->contains("Network/ip") && settings->contains("Network/port") && settings->contains("User/userName"))
    {
        socket = new QTcpSocket(this);
        connect(socket, &QTcpSocket::connected, this, [=](){
            connectStatus = true;
        });


        connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        connectToServer();
    }
    else
    {
        /*Если не установлены, ставим по умолчанию*/

        settings->beginGroup("Network");
        settings->setValue("ip",   "127.0.0.1");
        settings->setValue("port", "2323");
        settings->endGroup();

        settings->beginGroup("User");
        settings->setValue("userName", "Вася Неизвестный");
        settings->endGroup();

        addChatParams = new AddChatParams(settings, this);

        /* Переподключение после изменения параметров. Коннект с использованием лямбда функции */
        connect(addChatParams, &AddChatParams::dialogClose, this, [=](bool isSave){
            if(isSave && connectStatus){
                socket->disconnectFromHost();
                connectToServer();
            } else if(isSave)
            {
                connectToServer();
            }

        });
        /*открываем окно ввода параметров*/
        addChatParams->show();
    }
    emit clientOpen();
}

Client::~Client()
{
    delete ui;
}

void Client::connectToServer()
{
    /* Команда соединения с сервером */
    socket->connectToHost(settings->value("Network/ip").toString(), settings->value("Network/port").toInt());
    /* Выдаёт true после установки соединения, до момента соединения подвешивает выполнение программы */
    if (socket->waitForConnected())
    {
        setWindowTitle("Клиент. Соединение установлено.");

        /*Сообщаем серверу, что подключается клиент с таким-то именем. Ожидаем возвращения списка клиентов. Используем JSON для формирования пакета*/
        QJsonObject packObj;
        packObj.insert("packType", "connect");
        packObj.insert("text", settings->value("User/userName").toString());
        QJsonDocument packDoc(packObj);

        /*Создаём массив байт, который в итоге будет отправляться по сети, цепляем к нему в начало размер пакета с json, затем запускаем функцию отправки*/
        QByteArray pack{};
        int sizeOfJson = packDoc.toJson().size();
        pack += intToByteArray(sizeOfJson);
        pack += packDoc.toJson();
        sendToServer(pack);
    }
}

QByteArray Client::intToByteArray(int value)
{
    QByteArray byteVal{};
    QDataStream toByte(&byteVal, QIODevice::ReadWrite);
    toByte.setVersion(QDataStream::Qt_5_11);
    toByte.setByteOrder(QDataStream::BigEndian);
    toByte << (qint32)value;
    return byteVal;
}

int Client::intFromByteArray(QByteArray array)
{
    QDataStream intSt(array);
    intSt.setVersion(QDataStream::Qt_5_11);
    intSt.setByteOrder(QDataStream::BigEndian);
    int intValue {};
    intSt >> intValue;
    return intValue;
}

void Client::sendToServer(QByteArray pack) {

    int fullPackSize = pack.size()+sizeof(int);
    qDebug() << "ПОЛНЫЙ РАЗМЕР отправляемого пакета" << fullPackSize;
    /*Цепляем в начало массива передаваемых данных итоговый размер пакета. Это нужно в случае, если ктото по сети попытается отправить сообщение
        с текстом войны и мира или наш чат в будущем будет поддерживать картинки. Тогда пакет при передаче по сети будет разбит на множество малых пакетов и их потом придётся обратно собирать на сервере.
        Имея в начале пакета байт итоговый размер передаваемой информации, можно на сервере корректно принять все части пакета и понять когда он полностью получен */
    QByteArray resultPack = intToByteArray(fullPackSize);
    resultPack += pack;
    /*Непосредственная отправка пакета*/
    if (socket->write(resultPack) == -1)
        qDebug() << "Ошибка при передаче пакета";
    socket->waitForBytesWritten();
    ui->lineEdit_enterMessage->clear();
}

void Client::showMessage(QString date, QString sender, QString text)
{
    ui->textEdit_messages->append("<pre>"+date+"    "+sender+" пишет:</pre>");
    ui->textEdit_messages->append("<pre>              "+text+"</pre>");
}

void Client::processConnectRequest(QJsonObject root)
{
    userMap.clear();
    QJsonArray userInfoArray = root.value("userInfoList").toArray();

    ui->listWidget_users->clear();
    for(int userIndex = 0; userIndex < userInfoArray.count(); userIndex++)
    {
        QJsonObject currUser = userInfoArray.at(userIndex).toObject();

        userMap.push_back(QPair<QString, QString>(currUser.value("name").toString(), currUser.value("ip").toString()));

        ui->listWidget_users->addItem(currUser.value("name").toString());

        QHostAddress localAddr = socket->localAddress();
        QHostAddress checkAddr(currUser.value("ip").toString());
        qDebug() << localAddr.isEqual(checkAddr);

        QListWidgetItem *item = ui->listWidget_users->item(userIndex);
        if(currUser.value("name").toString() == settings->value("User/userName").toString() && localAddr.isEqual(checkAddr))
        {
            item->setFlags(Qt::NoItemFlags);
            item->setText(item->text()+" (Это вы)");
            item->font().setItalic(true);
        }
    }
}

void Client::processSendMessageRequest(QJsonObject root)
{
    for(int userIndex = 0; userIndex < userMap.count(); userIndex++)
    {
        if(userMap.at(userIndex).first == root.value("fromName").toString() && userMap.at(userIndex).second == root.value("fromIp").toString())
        {
            if(ui->listWidget_users->currentRow() == userIndex)
            {
                QString currTime = QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy");
                showMessage(currTime, root.value("fromName").toString(), root.value("text").toString());
            }
            else
            {
                QListWidgetItem *item = ui->listWidget_users->item(userIndex);
                QFont selectFont = item->font();
                selectFont.setBold(true);
                item->setFont(selectFont);
            }
        }
    }
}

void Client::processGetHistoryRequest(QJsonObject root)
{
    QJsonArray messHistoryArray = root.value("messHistory").toArray();
    for(int messIndex = 0; messIndex < messHistoryArray.count(); messIndex++)
    {
        QJsonObject obj = messHistoryArray.at(messIndex).toObject();
        showMessage(obj.value("messTime").toString(), obj.value("name").toString(), obj.value("messText").toString());
    }
}

void Client::slotReadyRead()
{
    qDebug() << "ПАКЕТ ПОЛУЧЕН!!!!" << socket->bytesAvailable();
    QByteArray pack;
    while(socket->bytesAvailable())
    {
        pack.append(socket->readAll());
    }

    /* Получаем размер отправленных данных для сбора всего пакета, если он ранее не получен */
    if(!fullPackSize) {
        fullPackSize = intFromByteArray(pack.left(sizeof(int)));
        qDebug() << "Полный размер пакета" << fullPackSize;
        /* Удаляем информацию о размере переданных данных из пакета */
        pack.remove(0, sizeof(int));
        qDebug() << "ПОЛНЫЙ РАЗМЕР ПРИНЯТОГО пакета" << fullPackSize;
    }

    packIn += pack;

    if(packIn.size() == (fullPackSize - sizeof (int))) {
        fullPackSize = 0;
        /*Извлекаем int с размером json в пакете*/
        int jsonSize = intFromByteArray(packIn.left(sizeof(int)));
        /*Удаляем информацию о размере json*/
        packIn.remove(0, sizeof(int));
        /* Получаем JSON */
        QByteArray json = packIn.left(jsonSize);
        /* Удаляем информацию о JSON */
        packIn.remove(0, jsonSize);

        QJsonDocument document = QJsonDocument::fromJson(json);
        QJsonObject root = document.object();

        qDebug() << "Тип пакета" << root.value("packType").toString();
        if(root.value("packType").toString() == "connect")
        {
            processConnectRequest(root);
        }
        else if(root.value("packType").toString() == "sendMessage")
        {
            processSendMessageRequest(root);
        }
        else if(root.value("packType").toString() == "getHistory")
        {
            processGetHistoryRequest(root);
        }
    }
}

void Client::on_action_exit_triggered()
{
    close();
}


void Client::on_action_openParams_triggered()
{
    if(!addChatParams) {
        addChatParams = new AddChatParams(settings, this);
        addChatParams->show();

        paramConn = connect(addChatParams, &AddChatParams::dialogClose, this, [=](bool isSave){
            if(isSave && connectStatus){
                socket->disconnectFromHost();
                ui->listWidget_users->clear();
                connectToServer();

            }
            else if(isSave)
            {
                connectToServer();
                disconnect(paramConn);
            }
        });
    }
    else
        addChatParams->show();
}


void Client::on_pushButton_send_clicked()
{
    QJsonObject packObj;
    packObj.insert("packType", "sendMessage");
    packObj.insert("destIp", userMap.at(ui->listWidget_users->currentIndex().row()).second);
    packObj.insert("destUser",ui->listWidget_users->currentItem()->text());
    packObj.insert("text", ui->lineEdit_enterMessage->text());
    QJsonDocument packDoc(packObj);

    qDebug() << "TEXT" << ui->lineEdit_enterMessage->text();

    QString currTime = QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy");
    showMessage(currTime, "Вы пишете:", ui->lineEdit_enterMessage->text());

    QByteArray pack{};
    int sizeOfJson = packDoc.toJson().size();
    pack += intToByteArray(sizeOfJson);

    pack += packDoc.toJson();
    sendToServer(pack);

    ui->lineEdit_enterMessage->text().clear();
}


void Client::on_listWidget_users_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current->flags() == Qt::NoItemFlags) {
        ui->textEdit_messages->clear();
        ui->lineEdit_enterMessage->setEnabled(false);
    }
    else {
        ui->lineEdit_enterMessage->setEnabled(true);
        QJsonObject packObj;
        packObj.insert("packType", "getHistory");
        packObj.insert("destIp", userMap.at(ui->listWidget_users->currentIndex().row()).second);
        packObj.insert("destUser",current->text());
        packObj.insert("messCount", "50");
        QJsonDocument packDoc(packObj);

        QByteArray pack{};
        int sizeOfJson = packDoc.toJson().size();
        pack += intToByteArray(sizeOfJson);

        pack += packDoc.toJson();
        sendToServer(pack);
    }
}

