#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T14:58:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarketMaster
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    goods_manage_window.cpp \
    login_window.cpp \
    goods_info.cpp \
    user_manage_window.cpp \
    goods_history.cpp

HEADERS  += mainwindow.h \
    Database/people.h \
    Database/goods.h \
    UI_h/goods_history.h \
    UI_h/goods_manage_window.h \
    UI_h/login_window.h \
    UI_h/user_manage_window.h \
    UI_h/goods_info.h

RESOURCES += \
    Res/logo.qrc \
    Res/icon.qrc

FORMS += \
    UI/user_manage_window.ui \
    UI/goods_manage_window.ui \
    UI/goods_info.ui \
    UI/goods_history.ui \
    UI/login_window.ui \
    UI/mainwindow.ui
