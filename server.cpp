#include "server.h"
#include "ui_server.h"
#include <QDebug>

Server::Server(QSettings *settings, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server),
    settings(settings)
{
    ui->setupUi(this);
    setWindowTitle("Сервер");

    /*Создаём объект базы данных*/
    db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName("chat.db"); //указываем имя файла с базой данных (База данных SQLite преставляет из себя просто файл)
    if(db.open()) //открываем базу данных. Если она не существовала, то файл создастся
    {
        /*Пробуем создаьб первую таблицу (список пользователей). Если она есть, то запрос будет проигнорирован*/
        QSqlQuery query(db);
        if(!query.exec("CREATE TABLE IF NOT EXISTS userList (id int not null primary key, name text, ip text, online bool);"))
        {
            writeLog("Не удалось выполнить попытку создать список пользователей");
        }
        query.clear();
        /* Пробуем создать вторую таблицу (История сообщений). Если она есть, запрос будет проигнорирован */
        if(!query.exec("CREATE TABLE IF NOT EXISTS msgList  (id int not null primary key, useridfrom int, useridto int, messtime text, messtext text, "
                       "FOREIGN KEY(useridfrom) REFERENCES userList(id));"))
        {
            writeLog("Не удалось выполнить попытку создать таблицу истории сообщений");
        }
    }
    else
    {
        qDebug() << "Ошибка при открытии базы данных";
    }

    /*Создаём объект сервера*/
    tcpServer = new QTcpServer(this);
    /* Он будет слушать все сетевые адреса по порту 2323*/
    if(tcpServer->listen(QHostAddress::Any, 2323)) {
        writeLog(QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy")+" Сервер запущен и ждёт соединений");
        /*КОннескт, отслеживающий появление новых подключений*/
        connect(tcpServer, &QTcpServer::newConnection, this, &Server::link);
    }
    else {
        /*Ошибка, если по каким- то причинам начать прослушивать порт не удалось (например он уже открыт другой программой)*/
        ui->listWidget_log->insertItem(ui->listWidget_log->count(),QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy")+" Сервер запушен, но возникла ошибка. Не удалось открыть порт");
        qDebug()<<"error";
    }
    //    nextBlockSize=0;
}

Server::~Server()
{
    delete ui;
}

void Server::link()
{
    /*Получем сокет, через который будем отправлять ответы подсоединившемуся пользоваелю*/
    QTcpSocket *clientSocket;

    clientSocket = tcpServer->nextPendingConnection();

    /*По аналогии с клиентом, как только в сокете поялвяется информация, запускаем слот slotReadyRead*/
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);

    /*В данном коннекте обрабатывается с помощью лямбда функции отсодинение клиента (напимер обрыв сети или клиент закрыли)*/
    connect(clientSocket, &QTcpSocket::disconnected, this, [=]()
    {
        /*Перебираем подключенные сокеты*/
        for(int sockIndex=0; sockIndex < sockets.count(); sockIndex++)
        {
            /*Находим тот сокет, который отцепился*/
            if(sockets.at(sockIndex).first == clientSocket) {
                /*меняем статус в базе данных, для того чтобы пометить, что данный пользователь сейчас не в сети и его отображать не нужно*/
                QSqlQuery query(db);
                query.exec("UPDATE userList SET online = false WHERE id = "+QString::number(sockets.at(sockIndex).second));

                /* Создаём пакет, которым оповещаем все клиенты о списке пользователей on line */
                QJsonObject packObj;
                if (query.exec("SELECT name, ip FROM userList WHERE online = true"))
                {
                    QJsonArray userArray;
                    while(query.next()){
                        QJsonObject userInfo;
                        userInfo.insert("name", query.value("name").toJsonValue());
                        userInfo.insert("ip",   query.value("ip").toJsonValue());
                        userArray.insert(userArray.count(), userInfo);
                    }

                    packObj.insert("packType", "connect");
                    packObj.insert("userInfoList", userArray);

                }
                else
                {
                    writeLog("Не удалось получить список пользователей в он лайн");
                }

                /*Удаляем отключенный сокет из списка*/
                sockets.removeAt(sockIndex);

                QJsonDocument packDoc(packObj);
                QByteArray ansverPack{} ;
                ansverPack += intToByteArray(packDoc.toJson().size());
                ansverPack += packDoc.toJson();

                for(int sockIndex = 0; sockIndex < sockets.count(); sockIndex++)
                {
                    sendToClient(ansverPack, sockets.at(sockIndex).first);
                }
            }
        }
    });
}

void Server::writeLog(QString text)
{
    ui->listWidget_log->insertItem(ui->listWidget_log->count(),text);
}

void Server::processConnectRequest(QJsonObject root)
{

    QSqlQuery query(db);
    writeLog(QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy")+" Подключился пользователь: "+root.value("text").toString());

    /* Разбираемся с БД */

    QJsonObject packObj;

    if (query.exec("SELECT id FROM userList WHERE ip = '"+clientSocket->localAddress().toString()+"' AND name = '"+root.value("text").toString()+"'"))
    {
        if(query.next())
        {
            QSqlQuery queryUpdate(db);
            if(!queryUpdate.exec("UPDATE userList SET online = true WHERE id = "+query.value(0).toString()))
                writeLog("Не удалось обновить статус пользователя");
        }
        else
        {
            QSqlQuery queryInsert(db);
            queryInsert.exec("SELECT max(id) FROM userList");
            queryInsert.next();
            int newEntryNum = queryInsert.value(0).toInt()+1;

            if(!queryInsert.exec("INSERT INTO userList (id, name, ip, online) VALUES ("+QString::number(newEntryNum)+",'"+root.value("text").toString()+"', '"+clientSocket->localAddress().toString()+"', true)")) {
                writeLog("Не удалось добавить нового пользователя");
            }
        }
        query.clear();

        if (query.exec("SELECT name, ip FROM userList WHERE online = true"))
        {
            QJsonArray userArray;
            QJsonObject userInfo;
            while(query.next()){
                userInfo.insert("name", query.value("name").toJsonValue());
                userInfo.insert("ip",   query.value("ip").toJsonValue());
                userArray.insert(userArray.count(), userInfo);
            }
            ui->listWidget_log->insertItem(ui->listWidget_log->count(),
                   QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy")+
                   " Количество пользователей, отправленных клиенту "+QString::number(userArray.count()));
            packObj.insert("packType", "connect");
            packObj.insert("userInfoList", userArray);

        }
        else
        {
            writeLog("Не удалось получить список пользователей в он лайн");
        }
    }
    else
    {
        writeLog("Не удалось выполнить запрос к списку пользователей");
    }

    query.clear();
    query.exec("SELECT id FROM userList WHERE ip = '"+clientSocket->localAddress().toString()+"' AND name = '"+root.value("text").toString()+"'");
    query.next();
    sockets.push_back({clientSocket, query.value("id").toInt()});

    QJsonDocument packDoc(packObj);
    QByteArray ansverPack{} ;
    ansverPack += intToByteArray(packDoc.toJson().size());
    ansverPack += packDoc.toJson();
    for(int sockIndex = 0; sockIndex < sockets.count(); sockIndex++)
    {
        sendToClient(ansverPack, sockets.at(sockIndex).first);
    }
}

void Server::processSendMessageRequest(QJsonObject root)
{
    QSqlQuery query(db);
    query.clear();
    query.exec("SELECT max(id) FROM msgList");
    query.next();
    QString newEntryNum = QString::number(query.value(0).toInt()+1);

    query.clear();
    QString fromEntryId{};
    for(int sockIndex = 0; sockIndex < sockets.count(); sockIndex++)
    {
        if(sockets.at(sockIndex).first == clientSocket)
        {
            fromEntryId = QString::number(sockets.at(sockIndex).second);
            break;
        }
    }

    query.exec("SELECT id FROM userList WHERE name = '"+root.value("destUser").toString()+"' AND ip = '"+root.value("destIp").toString()+"'");
    query.next();
    QString toEntryId = query.value(0).toString();
    query.clear();


    query.exec("SELECT name FROM userList WHERE id = "+fromEntryId);
    query.next();
    QString fromUser = query.value(0).toString();

    QString currTime = QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy");
    QString message = root.value("text").toString();
    query.clear();
    query.exec("INSERT INTO msgList (id, useridfrom, useridto, messtime, messtext) VALUES ("+newEntryNum+","+fromEntryId+","+toEntryId+",'"+currTime+"','"+message+"')");

    QJsonObject packObj;
    packObj.insert("packType", "sendMessage");
    packObj.insert("text",      root.value("text").toString());
    packObj.insert("fromName",  fromUser);
    packObj.insert("fromIp",    clientSocket->localAddress().toString());

    QTcpSocket *toSocket{};
    for(int sockIndex = 0; sockIndex < sockets.count(); sockIndex++)
    {
        if(sockets.at(sockIndex).second == toEntryId.toInt())
        {
            toSocket = sockets.at(sockIndex).first;
            break;
        }
    }

    QJsonDocument packDoc(packObj);

    /* Здесь нужно разослать всем присланные клиентом изображения, если они были */
    QByteArray ansverPack{} ;
    ansverPack += intToByteArray(packDoc.toJson().size());
    ansverPack += packDoc.toJson();
    ansverPack += inPack;
    sendToClient(ansverPack, toSocket);
}

void Server::processGetHistoryRequest(QJsonObject root)
{
    qDebug() << "ПОЛУЧЕНИЕ ИСТОРИИ";
    QSqlQuery query(db);
    QString userIdFrom{};
    for(int userIndex = 0; userIndex < sockets.count(); userIndex++)
    {
        if(sockets.at(userIndex).first == clientSocket)
        {
            userIdFrom = QString::number(sockets.at(userIndex).second);
            break;
        }
    }

    query.clear();
    query.exec("SELECT id FROM userList WHERE name = '"+root.value("destUser").toString()+"' AND ip = '"+root.value("destIp").toString()+"'");
    query.next();
    QString userIdTo = query.value(0).toString();
    QString resultCount = root.value("messCount").toString();
    query.clear();
    QJsonObject packObj;
    if (query.exec("SELECT messtime, messtext, userlist.name as name FROM msgList "
                   "INNER JOIN userlist ON userlist.id = msgList.useridfrom"
               " WHERE useridfrom = "+userIdFrom+" OR useridfrom = "+userIdTo+" OR useridto = "+userIdTo+" OR useridto = "+userIdFrom+""
               " ORDER BY msgList.id DESC LIMIT "+resultCount ))
    {

        QJsonArray messArray;
        while(query.next()){
            QJsonObject messInfo;
            messInfo.insert("messTime", query.value("messtime").toJsonValue());
            messInfo.insert("messText", query.value("messtext").toJsonValue());
            messInfo.insert("name",     query.value("name").toJsonValue());
            messArray.insert(messArray.count(), messInfo);
        }
        qDebug() ;
        packObj.insert("packType", "getHistory");
        packObj.insert("messHistory", messArray);
        QJsonDocument packDoc(packObj);
        QByteArray ansverPack{} ;
        ansverPack += intToByteArray(packDoc.toJson().size());
        ansverPack += packDoc.toJson();
        sendToClient(ansverPack, clientSocket);
    }
    else
    {
        qDebug() << query.lastQuery();
        writeLog("Не удалось получить историю сообщений");
    }
}

void Server::slotReadyRead() {

    clientSocket = (QTcpSocket*)QMainWindow::sender();

    QByteArray pack{};

    while(clientSocket->bytesAvailable())
    {
        pack.append(clientSocket->readAll());
    }

    /* Получаем размер отправленных данных для сбора всего пакета, если он ранее не получен */
    if(!fullPackSize) {
        fullPackSize = intFromByteArray(pack.left(sizeof(int)));
        qDebug() << "Полный размер пакета" << fullPackSize;
        /* Удаляем информацию о размере переданных данных из пакета */
        pack.remove(0, sizeof(int));
    }
    inPack += pack;
    /* Если переданы все данные, начинаем их разбирать */
    if(inPack.size() == (fullPackSize - sizeof (int))) {
        /*Извлекаем int с размером json в пакете*/
        int jsonSize  = intFromByteArray(inPack.left(sizeof(int)));
        /*Удаляем информацию о размере json*/
        inPack.remove(0, sizeof(int));
        /* Получаем JSON */
        QByteArray json = inPack.left(jsonSize);
        /* Удаляем информацию о JSON */
        inPack.remove(0, jsonSize);
        /* Обрабатываем JSON */
        QJsonDocument document = QJsonDocument::fromJson(json);
        QJsonObject root = document.object();
        QSqlQuery query(db);
        if(root.value("packType").toString() == "connect")
        {
            processConnectRequest(root);

        } else if(root.value("packType").toString() == "sendMessage") {
            processSendMessageRequest(root);
        }
        else if(root.value("packType").toString() == "getHistory") {
            processGetHistoryRequest(root);
        }
        /* На данном этапе обработка принятого пакета завершилась, нужно обнулить переменные */
        inPack.clear();
        fullPackSize = 0;
    }
}

int Server::intFromByteArray(QByteArray array)
{
    QDataStream intSt(array);

    intSt.setVersion(QDataStream::Qt_5_11);
    intSt.setByteOrder(QDataStream::BigEndian);
    int intValue {};
    intSt >> intValue;
    return intValue;
}

QByteArray Server::intToByteArray(int value)
{
    QByteArray byteVal{};
    QDataStream toByte(&byteVal, QIODevice::ReadWrite);
    toByte.setVersion(QDataStream::Qt_5_11);
    toByte.setByteOrder(QDataStream::BigEndian);
    toByte << (qint32)value;

    return byteVal;
}

void Server::sendToClient(QByteArray pack, QTcpSocket *clientSocket)
{
    int fullPackSize = pack.size()+sizeof(int);
    QByteArray resultPack = intToByteArray(fullPackSize);
    resultPack += pack;
    clientSocket->write(resultPack);
}
