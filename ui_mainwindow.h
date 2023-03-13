/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_client;
    QRadioButton *radioButton_server;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_select;
    QLabel *label_select;
    QCheckBox *checkBox_dont_show;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(282, 250);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButton_client = new QRadioButton(centralwidget);
        radioButton_client->setObjectName(QStringLiteral("radioButton_client"));

        gridLayout->addWidget(radioButton_client, 1, 1, 1, 1);

        radioButton_server = new QRadioButton(centralwidget);
        radioButton_server->setObjectName(QStringLiteral("radioButton_server"));

        gridLayout->addWidget(radioButton_server, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        pushButton_select = new QPushButton(centralwidget);
        pushButton_select->setObjectName(QStringLiteral("pushButton_select"));

        gridLayout->addWidget(pushButton_select, 3, 0, 1, 2);

        label_select = new QLabel(centralwidget);
        label_select->setObjectName(QStringLiteral("label_select"));

        gridLayout->addWidget(label_select, 0, 0, 1, 2);

        checkBox_dont_show = new QCheckBox(centralwidget);
        checkBox_dont_show->setObjectName(QStringLiteral("checkBox_dont_show"));

        gridLayout->addWidget(checkBox_dont_show, 4, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 282, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        radioButton_client->setText(QApplication::translate("MainWindow", "\320\232\320\273\320\270\320\265\320\275\321\202", nullptr));
        radioButton_server->setText(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200", nullptr));
        pushButton_select->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        label_select->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\200\320\265\320\266\320\270\320\274 \321\200\320\260\320\261\320\276\321\202\321\213:", nullptr));
        checkBox_dont_show->setText(QApplication::translate("MainWindow", "\320\221\320\276\320\273\321\214\321\210\320\265 \320\275\320\265 \320\277\320\276\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
