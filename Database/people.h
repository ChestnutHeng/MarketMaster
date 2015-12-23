#ifndef PEOPLE_H
#define PEOPLE_H
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSql>
#include <QSqlError>
#include <QDebug>

#define PDEBUG

enum PERMISSION{ADMIN,USER,GUEST};

struct PEOPLE{
    QString name;
    QString password;
    PERMISSION permission;
};

class QPeopleDB{
public:
    PERMISSION permission;
    bool correct;
    QSqlDatabase people_db;
    QString dbName;

    QPeopleDB(){
        permission = GUEST;
        this -> dbName = "db1.db";
        this -> people_db = QSqlDatabase::addDatabase("QSQLITE","connection1");
        this -> people_db.setDatabaseName("db1.db");
        if (!people_db.open()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  people_db.lastError().text());
        }else{
            qDebug() << "succ open DB.\n";
#ifdef PDEBUG
            QSqlQuery query(this -> people_db);
            query.exec("drop table people;");
            query.exec("create table people(\
                       ID INTEGER PRIMARY KEY,\
                       USER char(50) NOT NULL,\
                       PWD char(50) NOT NULL,\
                       PERMISSION int NOT NULL\
                       );");
            query.exec("insert into people (user,pwd,permission)\
                       values ('admin','admin',0);");
            query.exec("insert into people (user,pwd,permission)\
                               values ('mary','mary',1);");
#endif
        }

    }
    bool find(PEOPLE &p){
        qDebug() << "find:" << p.name << p.password;
        QSqlQuery query(this -> people_db);

        query.exec("select * from people;");
        while (query.next()) {
           qDebug() <<  query.value(0).toString() << query.value(1).toString()
                     <<query.value(2).toString()<<query.value(3).toString();
        }

        query.prepare("select pwd,permission from people where user like ?;");
        query.bindValue(0,p.name);

        query.exec();

        QString pwd;
        while(query.next()){
            pwd = query.value(0).toString();
            qDebug() << pwd;
            this -> permission = PERMISSION(query.value(1).toInt());
            qDebug() << permission;
        }
        if(pwd == p.password){
            return true;
        }
        return false;
    }
    bool add(PEOPLE &p){
        QString per = "0";
        if(p.permission != ADMIN) per = "1";
        if(permission != ADMIN){
           // return false;
        }
        QSqlQuery query(this -> people_db);
        query.exec("insert into people (user,pwd,permission)\
                   values (\'"+ p.name +"\',\'" + p.password + "\'," + per + ");");
        return true;
    }

    bool del(PEOPLE &p){
        if(permission != ADMIN){
           // return false;
        }
        QSqlQuery query(this -> people_db);
        query.exec("delete from people where user=\'" + p.name + "\';");
        return true;
    }

};


#endif // PEOPLE_H

