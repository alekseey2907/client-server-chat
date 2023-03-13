/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QAction *action_openParams;
    QAction *action_exit;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_enterMessage;
    QPushButton *pushButton_send;
    QListWidget *listWidget_users;
    QTextEdit *textEdit_messages;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QStringLiteral("Client"));
        Client->resize(800, 600);
        action_openParams = new QAction(Client);
        action_openParams->setObjectName(QStringLiteral("action_openParams"));
        action_exit = new QAction(Client);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_enterMessage = new QLineEdit(centralwidget);
        lineEdit_enterMessage->setObjectName(QStringLiteral("lineEdit_enterMessage"));
        lineEdit_enterMessage->setEnabled(false);

        gridLayout->addWidget(lineEdit_enterMessage, 1, 0, 1, 1);

        pushButton_send = new QPushButton(centralwidget);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));

        gridLayout->addWidget(pushButton_send, 1, 1, 1, 1);

        listWidget_users = new QListWidget(centralwidget);
        listWidget_users->setObjectName(QStringLiteral("listWidget_users"));

        gridLayout->addWidget(listWidget_users, 0, 2, 2, 1);

        textEdit_messages = new QTextEdit(centralwidget);
        textEdit_messages->setObjectName(QStringLiteral("textEdit_messages"));

        gridLayout->addWidget(textEdit_messages, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        Client->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Client);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        Client->setMenuBar(menubar);
        statusbar = new QStatusBar(Client);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Client->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action_openParams);
        menu->addAction(action_exit);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "MainWindow", nullptr));
        action_openParams->setText(QApplication::translate("Client", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        action_exit->setText(QApplication::translate("Client", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        pushButton_send->setText(QApplication::translate("Client", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        menu->setTitle(QApplication::translate("Client", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
