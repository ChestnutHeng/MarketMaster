#include "mainwindow.h"
#include "ui_login_window.h"
#include <QApplication>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSql>
#include <QSqlError>
#include <QDebug>
#include <QtSql>

#include "UI_h/login_window.h"
#include "UI_h/goods_manage_window.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    login_window *q = new login_window();
    q -> show();

//    goods_manage_window *g = new goods_manage_window();
//    g ->show();

    return a.exec();
}
