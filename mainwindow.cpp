#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Database/people.h"
#include "Database/goods.h"
#include "UI_h/user_manage_window.h"
#include "UI_h/goods_manage_window.h"
#include "UI_h/goods_history.h"

#include <QTableWidget>

void insert_row(QTableWidget *table_widget,QStringList str);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Allocate mem
    ui->setupUi(this);
    goods_db = new QGoodsDB();
    sale_db = new QSaleDB();
    //connect
    connect(ui->actionClear,&QAction::triggered,this,&MainWindow::clear);
    connect(ui->actionExit,&QAction::triggered,this,&MainWindow::close);
    //uiset
    TableSet();
        //label
    QFont frt;
    frt.setPointSize(25);
    ui -> label_p -> setFont(frt);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui -> label_p -> setPalette(pa);

}

void MainWindow::TableSet(){
    ui -> table_g -> hide();

    QTableWidgetItem *h_no = new QTableWidgetItem("1");
    ui -> table_g -> setVerticalHeaderItem(0,h_no);
    ui -> table_g -> setSelectionBehavior(QAbstractItemView::SelectRows);
    ui -> table_g -> setSelectionMode(QAbstractItemView::SingleSelection);


    QStringList header;
    header << tr("Code") << tr("Goods") <<tr ("Price") << tr("Count") << tr("Store");
    ui -> table_g -> setHorizontalHeaderLabels(header);
    ui -> table_g -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui -> table_g -> horizontalHeader() -> setStretchLastSection(true);
    ui -> table_g -> show();
}

void MainWindow::HideButtons(){
    ui -> g1 -> hide();
    ui -> u1 -> hide();
}

void MainWindow::flush_price(){
    float suum = 0;
    for(unsigned int i = 0; i < goods_list.size(); ++i){
        suum += goods_list[i] ->price * goods_list[i] ->count/100;
    }
    ui ->label_p->setText("$ "+QString::number(suum,'f',2));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete goods_db;
}

void MainWindow::on_u1_clicked()
{
//    QDialog *d = new QDialog(this);
//    d -> show();
    user_manage_window *u = new user_manage_window(this);
    u -> show();
}

void MainWindow::on_search_b_clicked()
{

    //change table
    int count = ui ->count_l-> text().toInt();
    if(count == 0)  {
        ui -> count_l ->setText(tr("1"));
        count = 1;
    }
    QStringList _data = this -> goods_db -> find(ui -> code_l ->text(),count);
    if(_data.size() == 1){
        QMessageBox::information(this, QObject::tr("Advise"),
                              QObject::tr("Lack of Goods!"));
        return;
    }else if(_data.size() == 0){
        ui -> count_l ->setText(tr(""));
        QMessageBox::information(this, QObject::tr("Check your goods code.."),
                                tr("No goods!"));
    }else{
        //add goods and flush table
        SALE_GOODS *new_goods = new SALE_GOODS;
        new_goods ->name = _data[1];
        new_goods ->code = _data[0];
        new_goods ->store = _data[2].toInt();
        new_goods ->count = count;
        new_goods ->price = _data[4].toFloat();
//        for(int i = 0;i < _data.size();++i)
//            qDebug() << _data[i];

        bool find_tag = false;
        for(unsigned int i = 0;i < goods_list.size(); ++i){
            if((*goods_list[i]) == (*new_goods)){
                if(count > ui ->table_g ->item(i,4) ->text().toInt()){
                    QMessageBox::information(this, QObject::tr("Advise"),
                                          QObject::tr("Lack of Goods!"));
                    flush_price();
                    return;
                }
                //count
                goods_list[i] -> count += new_goods ->count;
                goods_list[i] -> store -= new_goods ->count;
                QTableWidgetItem *item = new QTableWidgetItem();
                item ->setText(QString::number(goods_list[i] -> count,10));
                ui ->table_g ->setItem(i ,3,item);
                //store
                QTableWidgetItem *item2 = new QTableWidgetItem();
                item2 ->setText(QString::number(ui ->table_g ->item(i,4) ->text().toInt() - new_goods ->count,10));
                ui ->table_g ->setItem(i ,4,item2);
                find_tag = true;
            }
        }
        if(!find_tag){
            goods_list.push_back(new_goods);
            insert_row(ui -> table_g,_data);
        }
    }
    flush_price();
}


void MainWindow::on_remove_b_clicked()
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

    flush_price();
}
//6922711091396


void MainWindow::on_done_b_clicked()
{
       if(goods_list.size() == 0){
           QMessageBox::information(this, QObject::tr("Advise..."),
                                 QObject::tr("No goods in bukket."));
           return;
       }
       goods_db ->update(goods_list);
       sale_db ->update_o(goods_list);
       goods_list.clear();
       ui ->table_g ->clearContents();
       ui ->table_g ->setRowCount(0);
       TableSet();
       flush_price();
       QMessageBox::information(this, QObject::tr("Done!"),
                             QObject::tr("Goods Sold!"));
}

void MainWindow::clear(){
    goods_list.clear();
    ui ->table_g ->clearContents();
    ui ->table_g ->setRowCount(0);
    TableSet();
    flush_price();
}

void MainWindow::on_g1_clicked()
{
    goods_manage_window *g = new goods_manage_window(this);
    g ->show();
}

void MainWindow::on_gh_p_clicked()
{
    goods_history *gh = new goods_history(this);
    gh ->show();
}
