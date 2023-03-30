#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QSettings *settings, QWidget *parent = nullptr);
    ~Server();

private slots:
    /*!
     * \brief link
     */
    void link();

    /*!
     * \brief slotReadyRead
     */
    void slotReadyRead();
private:
    Ui::Server                          *ui;
    QSettings                           *settings{};
    QTcpServer                          *tcpServer{};
    QSqlDatabase                        db;
    QTcpSocket                          *clientSocket{};
    QByteArray                          inPack{};
    QByteArray                          Data{};
    int                                 fullPackSize{};
    QVector <QPair<QTcpSocket*, int>>   sockets; //сокет соответствует id пользователя в базе

    /*!
     * \brief intToByteArray - аналогично одноимённой функции в классе клиента
     * \param value
     * \return
     */
    QByteArray  intToByteArray              (int value);

    /*!
     * \brief intFromByteArray - аналогично одноимённой функции в классе клиента
     * \param array
     * \return
     */
    int         intFromByteArray            (QByteArray array);

    /*!
     * \brief sendToClient - функция отправки ответа клиенту
     * \param pack
     * \param clientSocket
     */
    void        sendToClient                (QByteArray pack, QTcpSocket *clientSocket);

    /*!
     * \brief writeLog - функция вывода сообщения в графический лог событий сервера
     * \param text
     */
    void        writeLog                    (QString text);

    /*!
     * \brief processConnectRequest - обработка пакета, содержащего информацию о подключающемся пользователе
     * \param root
     */
    void        processConnectRequest       (QJsonObject root);

    /*!
     * \brief processSendMessageRequest - обработка пакета передачи сообщения от одного пользователя другому
     * \param root
     */
    void        processSendMessageRequest   (QJsonObject root);

    /*!
     * \brief processGetHistoryRequest - обработка пакета с запросом истории общения двух пользователей
     * \param root
     */
    void        processGetHistoryRequest    (QJsonObject root);
};

#endif // SERVER_H
