/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QAction *action_network_params;
    QAction *action_db_params;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QListWidget *listWidget_log;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName(QStringLiteral("Server"));
        Server->resize(800, 600);
        action_network_params = new QAction(Server);
        action_network_params->setObjectName(QStringLiteral("action_network_params"));
        action_db_params = new QAction(Server);
        action_db_params->setObjectName(QStringLiteral("action_db_params"));
        centralwidget = new QWidget(Server);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listWidget_log = new QListWidget(centralwidget);
        listWidget_log->setObjectName(QStringLiteral("listWidget_log"));

        gridLayout->addWidget(listWidget_log, 0, 0, 1, 1);

        Server->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Server);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        Server->setMenuBar(menubar);
        statusbar = new QStatusBar(Server);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Server->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action_network_params);
        menu->addAction(action_db_params);

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QMainWindow *Server)
    {
        Server->setWindowTitle(QApplication::translate("Server", "MainWindow", nullptr));
        action_network_params->setText(QApplication::translate("Server", "\320\241\320\265\321\202\320\265\320\262\321\213\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        action_db_params->setText(QApplication::translate("Server", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\261\320\260\320\267\321\213 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        menu->setTitle(QApplication::translate("Server", "\320\235\320\260\321\201\321\202\321\200\320\276\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
