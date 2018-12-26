#-------------------------------------------------
#
# Project created by QtCreator 2018-12-20T14:56:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = splitExcel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    configsetting.cpp


HEADERS += \
        mainwindow.h \
    configsetting.h

FORMS += \
        mainwindow.ui \
    configsetting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# qtxlsx
include(xlsx/qtxlsx.pri)

# stmp client
#include(smtpclient/smtpclient.pri)


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-SMTPEmail-Desktop_Qt_5_11_2_MinGW_32bit-Debug/release/ -lSMTPEmail
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-SMTPEmail-Desktop_Qt_5_11_2_MinGW_32bit-Debug/debug/ -lSMTPEmail
else:mac: LIBS += -F$$PWD/../build-SMTPEmail-Desktop_Qt_5_11_2_MinGW_32bit-Debug/ -framework SMTPEmail
else:unix: LIBS += -L$$PWD/../build-SMTPEmail-Desktop_Qt_5_11_2_MinGW_32bit-Debug/ -lSMTPEmail

INCLUDEPATH += $$PWD/../build-SMTPEmail-Desktop_Qt_5_11_2_MinGW_32bit-Debug/debug
DEPENDPATH += $$PWD/../build-SMTPEmail-Desktop_Qt_5_11_2_MinGW_32bit-Debug/debug

RC_FILE = splitExcel.rc

RESOURCES += \
    images.qrc
