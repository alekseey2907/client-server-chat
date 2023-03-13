/********************************************************************************
** Form generated from reading UI file 'addchatparams.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCHATPARAMS_H
#define UI_ADDCHATPARAMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddChatParams
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_port;
    QLabel *label_ip;
    QLabel *label_name;
    QLabel *label_port;
    QLineEdit *lineEdit_ip;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_save;
    QPushButton *pushButton_close;
    QLineEdit *lineEdit_name;
    QLabel *label_topic;

    void setupUi(QDialog *AddChatParams)
    {
        if (AddChatParams->objectName().isEmpty())
            AddChatParams->setObjectName(QStringLiteral("AddChatParams"));
        AddChatParams->resize(378, 253);
        gridLayout_2 = new QGridLayout(AddChatParams);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_port = new QLineEdit(AddChatParams);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));

        gridLayout->addWidget(lineEdit_port, 3, 1, 1, 1);

        label_ip = new QLabel(AddChatParams);
        label_ip->setObjectName(QStringLiteral("label_ip"));

        gridLayout->addWidget(label_ip, 2, 0, 1, 1);

        label_name = new QLabel(AddChatParams);
        label_name->setObjectName(QStringLiteral("label_name"));

        gridLayout->addWidget(label_name, 1, 0, 1, 1);

        label_port = new QLabel(AddChatParams);
        label_port->setObjectName(QStringLiteral("label_port"));

        gridLayout->addWidget(label_port, 3, 0, 1, 1);

        lineEdit_ip = new QLineEdit(AddChatParams);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        gridLayout->addWidget(lineEdit_ip, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_save = new QPushButton(AddChatParams);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));

        horizontalLayout->addWidget(pushButton_save);

        pushButton_close = new QPushButton(AddChatParams);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));

        horizontalLayout->addWidget(pushButton_close);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 2);

        lineEdit_name = new QLineEdit(AddChatParams);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));

        gridLayout->addWidget(lineEdit_name, 1, 1, 1, 1);

        label_topic = new QLabel(AddChatParams);
        label_topic->setObjectName(QStringLiteral("label_topic"));

        gridLayout->addWidget(label_topic, 0, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(AddChatParams);

        QMetaObject::connectSlotsByName(AddChatParams);
    } // setupUi

    void retranslateUi(QDialog *AddChatParams)
    {
        AddChatParams->setWindowTitle(QApplication::translate("AddChatParams", "Dialog", nullptr));
        label_ip->setText(QApplication::translate("AddChatParams", "\320\220\320\264\321\200\320\265\321\201 \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
        label_name->setText(QApplication::translate("AddChatParams", "\320\230\320\274\321\217", nullptr));
        label_port->setText(QApplication::translate("AddChatParams", "\320\237\320\276\321\200\321\202 \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
        pushButton_save->setText(QApplication::translate("AddChatParams", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        pushButton_close->setText(QApplication::translate("AddChatParams", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        label_topic->setText(QApplication::translate("AddChatParams", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\207\320\260\321\202\320\260:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddChatParams: public Ui_AddChatParams {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCHATPARAMS_H
