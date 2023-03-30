#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QDateTime>
#include <QListWidgetItem>
#include <QTimer>
#include "addchatparams.h"

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QSettings *settings, QWidget *parent = nullptr);
    ~Client();

private:
    Ui::Client *ui;
    QSettings       *settings       {};
    QTcpSocket      *socket         {};
    AddChatParams   *addChatParams  {};
    bool connectStatus = false;
    int fullPackSize{};
    QByteArray packIn{};
    QVector<QPair<QString, QString>> userMap{};

    QMetaObject::Connection paramConn{};

    void connectToServer();

    /*!
     * \brief intToByteArray - меняет порядок байт для передачи по сети (смотри htons и ntohs, здесь действия аналогичны)
     * \param value
     * \return
     */
    QByteArray  intToByteArray              (int value)                                 ;

    /*!
     * \brief intFromByteArray - меняет порядок байт, полученных из сети, для дальнейшей распаковки
     * \param array
     * \return
     */
    int         intFromByteArray            (QByteArray array)                          ;

    /*!
     * \brief sendToServer - функция отправки информации на сервер
     * \param pack
     */
    void        sendToServer                (QByteArray pack)                           ;

    /*!
     * \brief showMessage - функция вывода сообщения в поле для сообщений чата. Поддерживает HTML разметку, можно форматировать
     * \param date
     * \param sender
     * \param text
     */
    void        showMessage                 (QString date, QString sender, QString text);

    /*!
     * \brief processConnectRequest - обработка ответа сервера на запрос клиента на присоединение пользователя
     * \param root
     */
    void        processConnectRequest       (QJsonObject root)                          ;

    /*!
     * \brief processSendMessageRequest - обработка пакета от сервера, содержащего сообщение от участника чата
     * \param root
     */
    void        processSendMessageRequest   (QJsonObject root)                          ;

    /*!
     * \brief processGetHistoryRequest - обработка пакета, содержащего историю сообщений
     * \param root
     */
    void        processGetHistoryRequest    (QJsonObject root)                          ;

private slots:
    /*!
     * \brief slotReadyRead - слот, выполнение которого запускается по сигналу от QTcpSocket о том, что был прислан некий пакет
     */
    void slotReadyRead();



    /*!
     * \brief on_action_exit_triggered - закрытие приложения
     */
    void on_action_exit_triggered();

    /*!
     * \brief on_action_openParams_triggered - открытие пареметров чата
     */
    void on_action_openParams_triggered();

    /*!
     * \brief on_pushButton_send_clicked - нажатие кнопки отправки сообщения
     */
    void on_pushButton_send_clicked();

    /*!
     * \brief on_listWidget_users_currentItemChanged - выделение какого либо пользователя в списке
     * \param current
     * \param previous
     */
    void on_listWidget_users_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

signals:

    void clientOpen();
};

#endif // CLIENT_H
