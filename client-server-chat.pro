QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addchatparams.cpp \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    server.cpp

HEADERS += \
    addchatparams.h \
    client.h \
    mainwindow.h \
    server.h

FORMS += \
    addchatparams.ui \
    client.ui \
    mainwindow.ui \
    server.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
