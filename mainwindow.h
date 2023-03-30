#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "client.h"
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
     * \brief on_pushButton_select_clicked -
     */
    void on_pushButton_select_clicked();

    /*!
     * \brief on_radioButton_client_clicked - обработка выбора режима работы (клиент)
     */
    void on_radioButton_client_clicked();

    /*!
     * \brief on_radioButton_server_clicked - обработка выбора режима работы (сервер)
     */
    void on_radioButton_server_clicked();

    /*!
     * \brief on_checkBox_dont_show_stateChanged - обработка выбора галки (не показывать окно в будущем, если например, этот экземпляр программы всегда используется как клиент)
     * \param arg1
     */
    void on_checkBox_dont_show_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QSettings *settings{};
    Client *client{};
    Server *server{};
};
#endif // MAINWINDOW_H
