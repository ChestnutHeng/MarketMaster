#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T16:31:47
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarketMaster
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login_window.cpp \
    user_manage_window.cpp \
    goods_manage_window.cpp \
    goods_info.cpp \
    goods_history.cpp

HEADERS  += mainwindow.h \
    people.h \
    login_window.h \
    goods.h \
    user_manage_window.h \
    goods_manage_window.h \
    goods_info.h \
    goods_history.h

FORMS    += mainwindow.ui \
    login_window.ui \
    user_manage_window.ui \
    goods_manage_window.ui \
    goods_info.ui \
    goods_history.ui

DISTFILES +=
LIBS += -ldl

RESOURCES += \
    logo.qrc \
    icon.qrc

RC_FILE += icon.rc
