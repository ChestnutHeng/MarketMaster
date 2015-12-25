#include "ui_goods_manage_window.h"

#include "UI_h/goods_manage_window.h"
#include "Database/goods.h"
#include "Database/people.h"
#include "UI_h/goods_info.h"

#include <QMessageBox>
#include <QTableWidget>


goods_manage_window::goods_manage_window(QWidget *parent):
    QDialog(parent)
{
    ui = new Ui::goods_manage_window;
    ui -> setupUi(this);
    goods_db = new QGoodsDB();
    sale_db = new QSaleDB();
    g = new goods_info(this);

    TableSet();
}

goods_manage_window::~goods_manage_window()
{
    delete ui;
    delete sale_db;
    delete goods_db;
    delete g;
}

void insert_row(QTableWidget *table_widget,QStringList str){
    int row_count = table_widget -> rowCount();
    table_widget->insertRow(row_count);

    QTableWidgetItem *item = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();
    QTableWidgetItem *item4 = new QTableWidgetItem();

    QString price = QString::number(str[4].toFloat()/100,'f',2);
    item -> setText(str[0]);
    item1 -> setText(str[1]);
    item2 -> setText(str[2]);
    item3 -> setText(str[3]);
    item4 -> setText(price);

    table_widget->setItem(row_count, 0, item);
    table_widget->setItem(row_count, 1, item1);
    table_widget->setItem(row_count, 2, item4);
    table_widget->setItem(row_count, 3, item3);
    table_widget->setItem(row_count, 4, item2);
}

void goods_manage_window::TableSet(){
    ui -> table_g -> hide();

    QTableWidgetItem *h_no = new QTableWidgetItem("1");
    ui -> table_g -> setVerticalHeaderItem(0,h_no);
    ui -> table_g -> setSelectionBehavior(QAbstractItemView::SelectRows);
    ui -> table_g -> setSelectionMode(QAbstractItemView::SingleSelection);


    QStringList header;
    header << tr("Code") << tr("Goods") <<tr ("INPrice") << tr("Count") << tr("Store");
    ui -> table_g -> setHorizontalHeaderLabels(header);
    ui -> table_g -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui -> table_g -> horizontalHeader() -> setStretchLastSection(true);
    ui -> table_g -> show();
}



void goods_manage_window::on_search_b_clicked()
{
    //change table

    int count = ui ->count_l-> text().toInt();
    if(count == 0)  {
        ui -> count_l ->setText(tr("1"));
        count = 1;
    }

    QStringList _data = this -> goods_db -> add(ui -> code_l ->text(),count);
    if(_data.size() == 0){
        g ->show();
    }else{
        //add goods and flush table
        SALE_GOODS *new_goods = new SALE_GOODS;
        new_goods ->name = _data[1];
        new_goods ->code = _data[0];
        new_goods ->store = _data[2].toInt();
        new_goods ->count = count;
        new_goods ->price = _data[4].toFloat();

        bool find_tag = false;
        for(unsigned int i = 0;i < goods_list.size(); ++i){
            if((*goods_list[i]) == (*new_goods)){
                //count
                goods_list[i] -> count += new_goods ->count;
                goods_list[i] -> store += new_goods ->count;
                QTableWidgetItem *item = new QTableWidgetItem();
                item ->setText(QString::number(goods_list[i] -> count,10));
                ui ->table_g ->setItem(i ,3,item);
                //store
                QTableWidgetItem *item2 = new QTableWidgetItem();
                item2 ->setText(QString::number(ui ->table_g ->item(i,4) ->text().toInt() + new_goods ->count,10));
                ui ->table_g ->setItem(i ,4,item2);
                find_tag = true;
            }
        }
        if(!find_tag){
            goods_list.push_back(new_goods);
            insert_row(ui -> table_g,_data);
        }
    }
}



void goods_manage_window::on_remove_b_clicked()
{
    int count  = ui ->count_l ->text().toInt();
    if(count == 0) {
        ui ->count_l ->setText("1");
        count = 1;
    }
    //change table
        //get selected row
    QList<QTableWidgetItem *> items = ui ->table_g ->selectedItems();
    if(items.size() == 0) return;
    int item_row = ui ->table_g ->row(items.at(0));
    qDebug() << "Remove:" << item_row;

    ui ->table_g ->removeRow(item_row);

    goods_list.erase(goods_list.begin() + item_row);

}
//6922711091396


void goods_manage_window::on_done_b_clicked()
{
       if(goods_list.size() == 0){
           QMessageBox::information(this, QObject::tr("Advise..."),
                                 QObject::tr("Add some goods.."));
           return;
       }
       goods_db ->update(goods_list);
       sale_db -> update_i(goods_list);
       goods_list.clear();
       ui ->table_g ->clearContents();
       ui ->table_g ->setRowCount(0);
       TableSet();
       QMessageBox::information(this, QObject::tr("Done!"),
                             QObject::tr("Goods Added!"));
}

void goods_manage_window::clear(){
    goods_list.clear();
    ui ->table_g ->clearContents();
    ui ->table_g ->setRowCount(0);
    TableSet();
}


void goods_manage_window::on_new_b_clicked()
{
    g -> show();
}
