#ifndef GOODS
#define GOODS

#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSql>
#include <QSqlError>
#include <QDebug>
//#define QDEBUG

struct SALE_GOODS{
    QString code;
    QString name;
    int count;
    int store;
    float price;
    bool operator ==(SALE_GOODS s){
        return s.code == code;
    }
};

struct IN_GOODS{
    QString name;
    QString code;
    QString count;
    QString iprice;
    QString oprice;
};

class QGoodsDB{
public:

    QSqlDatabase goods_db;


    QGoodsDB(){
        this -> goods_db = QSqlDatabase::addDatabase("QSQLITE","connection2");
        this -> goods_db.setDatabaseName("db2.db");
        if (!goods_db.open()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  goods_db.lastError().text());
        }else{
            qDebug() << "succ in DB2.\n";
#ifdef QDEBUG
            QSqlQuery query(this -> goods_db);
            query.exec("drop table goods;");
            query.exec("create table goods(\
                        ID INTEGER PRIMARY KEY,\
                        CODE int NOT NULL,\
                        NAME char(50) NOT NULL,\
                        COUNTS int NOT NULL,\
                        BUY_PRICE int NOT NULL,\
                        SALE_PRICE int NOT NULL,\
                        TIME char(50) NOT NULL\
                       );");
            query.exec("insert into goods (code,name,counts,buy_price,sale_price,time)\
                       values (6922711091396,\"NoteBook\",95,100,200,\"2015-9-20\");" );
            query.exec("insert into goods (code,name,counts,buy_price,sale_price,time)\
                       values (6922711091397,\"TextBook\",195,120,250,\"2015-9-20\");" );
#endif
        }

    }

    QStringList find(QString code,int count){
        QStringList ans;
        QStringList b_ans;
        b_ans.push_back("233");
        QString new_count;
        QSqlQuery query(this -> goods_db);

        query.exec("select * from goods where code like \'" + code + "\';");
        while (query.next()) {
           ans  << query.value(1).toString() << query.value(2).toString()
                     << QString::number(query.value(3).toInt() - count,10) << QString::number(count, 10)
                     << query.value(5).toString();
           if(query.value(3).toInt() - count <= 0){
               return b_ans;        // a 1 size list to raise errors
           }
           new_count = QString::number(query.value(3).toInt() - count,10);
        }

        //query.exec("update goods set counts="+new_count+" where code=\'" + code + "\';");
        return ans;
    }

    void update(std::vector<SALE_GOODS *>goods_list){
        QSqlQuery query(this -> goods_db);
        for (std::vector<SALE_GOODS *>::iterator it = goods_list.begin() ; it != goods_list.end(); ++it){
            query.exec("update goods set counts="+QString::number((*it) -> store,10)
                       +" where code=\'" + (*it) -> code + "\';");
            qDebug() << QString::number((*it) -> store,10) << " " <<(*it) -> code;
        }
    }


    QStringList add(QString code,int count){
        QStringList ans;
        QStringList bns;
        bns.push_back("0");
        QSqlQuery query(this -> goods_db);
        query.exec("select * from goods where code like \'" + code + "\';");
        while (query.next()) {
           ans  << query.value(1).toString() << query.value(2).toString()
                     << QString::number(query.value(3).toInt() + count,10) << QString::number(count, 10)
                     << query.value(4).toString();
        }
        qDebug() << ans.size();
        return ans;
    }
    bool add_new(IN_GOODS g){
        QSqlQuery query(this -> goods_db);
        query.exec("insert into goods (code,name,counts,buy_price,sale_price,time)\
                   values ("+ g.code +",\'" + g.name +"\'," + g.count + "," + g.iprice + "," + g.oprice +",\'2015-12-18\');");
        qDebug() << "insert into goods (code,name,counts,buy_price,sale_price,time)\
                           values ("+ g.code +",\'" + g.name +"\'," + g.count + "," + g.iprice + "," + g.oprice +",\'2015-12-18\');";
        return true;
    }

};

class QSaleDB{
public:
    QSqlDatabase sale_db;
    QSaleDB(){
        this -> sale_db = QSqlDatabase::addDatabase("QSQLITE","connection3");
        this -> sale_db.setDatabaseName("db3.db");
        if (!sale_db.open()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  sale_db.lastError().text());
        }else{
            qDebug() << "succ in DB3.\n";
#ifdef QDEBUG
            QSqlQuery query(this -> sale_db);
            query.exec("drop table sale;");
            query.exec("create table sale(\
                        ID INTEGER PRIMARY KEY,\
                        CODE int NOT NULL,\
                        NAME char(50) NOT NULL,\
                        SALE int NOT NULL,\
                        COUNTS int NOT NULL,\
                        BUY_PRICE int ,\
                        SALE_PRICE int ,\
                        TIME char(20) NOT NULL,\
                        YEAR char(20) NOT NULL\
                       );");
            query.exec("insert into sale (code,name,sale,counts,buy_price,sale_price,time,year)\
                       values (6922711091396,\"NoteBook\",1,95,100,200,\'11:51:06\',\"2015-11-11\");" );
            query.exec("insert into sale (code,name,sale,counts,buy_price,sale_price,time,year)\
                       values (6922711091397,\"TextBook\",1,195,120,250,\'13:30:02\',\"2014-12-20\");" );
#endif
        }

    }

    void update_o(std::vector<SALE_GOODS *>goods_list){
        QSqlQuery query(this -> sale_db);
        for (std::vector<SALE_GOODS *>::iterator it = goods_list.begin() ; it != goods_list.end(); ++it){
            SALE_GOODS *g = (*it);
            query.exec("insert into sale (code,name,sale,counts,sale_price,time,year)\
                       values (" + g->code +",\'" +
                               g->name +"\',1," + QString::number(g->count,10)  + "," + QString::number((int)g->price,10)
                               +",(SELECT time('now', 'localtime')),(SELECT date('now')));");
            qDebug() << "insert into sale (code,name,sale,counts,sale_price,time,year)\
                        values (" + g->code +",\'" +
                                g->name +"\',1," + QString::number(g->count,10)  + "," + QString::number((int)g->price,10)
                                +",(SELECT time('now', 'localtime')),(SELECT date('now')));";
        }
    }
    void update_i(std::vector<SALE_GOODS *>goods_list){
        QSqlQuery query(this -> sale_db);
        for (std::vector<SALE_GOODS *>::iterator it = goods_list.begin() ; it != goods_list.end(); ++it){
            SALE_GOODS *g = (*it);
            query.exec("insert into sale (code,name,sale,counts,buy_price,time,year)\
                       values (" + g->code +",\'" +
                               g->name +"\',0," + QString::number(g->count,10)  + "," + QString::number((int)g->price,10)
                               +",(SELECT time('now', 'localtime')),(SELECT date('now')));");
            qDebug() << "insert into sale (code,name,sale,counts,buy_price,time,year)\
                        values (" + g->code +",\'" +
                                g->name +"\',0," + QString::number(g->count,10)  + "," + QString::number((int)g->price,10)
                                +",(SELECT time('now', 'localtime')),(SELECT date('now')));";
        }
    }
    void update_n(IN_GOODS g){
         QSqlQuery query(this -> sale_db);
        query.exec("insert into sale (code,name,sale,counts,buy_price,time,year)\
                   values (" + g.code +",\'" +
                           g.name +"\',0," + g.count  + "," + g.iprice
                           + ",(SELECT time('now', 'localtime')),(SELECT date('now')));");
        qDebug() <<"insert into sale (code,name,sale,counts,buy_price,time,year,month,day)\
                   values (" + g.code +",\'" +
                           g.name +"\',0," + g.count  + "," + g.iprice
                           + ",(SELECT time('now', 'localtime')),(SELECT date('now')));";
    }

    std::vector< QStringList > search(QString f_date,QString t_date){
       QSqlQuery query(this -> sale_db);
       QStringList ans;
       std::vector<QStringList> vans;
       query.exec("select * from sale where year>=\'" + f_date +  "\' group by id having year<=\'" + t_date + "\' order by year;");
       qDebug()<<"select * from sale where year>=\'" + f_date +  "\' group by id having year<= \'" + t_date + "\' order by year;";
       while (query.next()) {
          ans.clear();
          ans  << query.value(1).toString() << query.value(2).toString()
               << query.value(3).toString() << query.value(5).toString()
               << query.value(6).toString() << query.value(4).toString()
               << query.value(8).toString() << query.value(7).toString();
          if(ans.size() == 0) continue;
          if(ans[2] == "1")
                    ans.erase(ans.begin() + 3);
          else ans.erase(ans.begin() + 4);
          vans.push_back(ans);
       }
       return vans;
    }
};

#endif // GOODS

