#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*Команда вывода заголовка окна*/
    setWindowTitle("Тип клиента:");

    /* Класс QSettings открывает или создаёт ini файл для параметров */
    settings = new QSettings("params.ini",QSettings::IniFormat, this);



    /* В зависимости от записи в файле параметров чек бокс либо устанавливается, либо нет */
    ui->checkBox_dont_show->setChecked(settings->value("Main/dontShowSelectMode").toBool());

    /* Если файл параметров был создан ранее, то у него уже должен быть добавлен параметр, определяющий тип работы по умолчанию - сервер или клиент */
    if(settings->contains("Main/mode")) {
        /* Если галка не показывать это окно не установлена, выполнить условие */
        if(!ui->checkBox_dont_show->isChecked()) {
            if(settings->value("Main/mode").toString() == "client")
                ui->radioButton_client->setChecked(true);
            if(settings->value("Main/mode").toString() == "server")
                ui->radioButton_server->setChecked(true);
        } else {
            /* Если галка не показывать это окно установлена, переходим сразу к открытию основного окна */
            on_pushButton_select_clicked();
            QTimer::singleShot(50, this, SLOT(close()));
        }
    } else {
        /* Если файл параметров не был создан и заполнен ранее, добавлем в него новые значения и выприраем режим работы клиент   */
        ui->radioButton_client->setChecked(true);
        settings->setValue("Main/mode",QVariant("client"));
        settings->setValue("Main/dontShowSelectMode", QVariant(false));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_select_clicked()
{
    QString mode = settings->value("Main/mode").toString();
    if(mode == "client")
    {
        client = new Client(settings);
        client->show();
    }
    else if(mode == "server")
    {
        server = new Server(settings);
        server->show();
    }
    this->close();
}


void MainWindow::on_radioButton_client_clicked()
{
    settings->setValue("Main/mode",QVariant("client"));

}


void MainWindow::on_radioButton_server_clicked()
{
    settings->setValue("Main/mode",QVariant("server"));

}


void MainWindow::on_checkBox_dont_show_stateChanged(int arg1)
{
    settings->setValue("Main/dontShowSelectMode", ui->checkBox_dont_show->isChecked());

}

