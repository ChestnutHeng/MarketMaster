#include "UI_h/goods_history.h"
#include "ui_goods_history.h"
#include "Database/goods.h"

#include <QFont>

goods_history::goods_history(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goods_history)
{
    sale_db = new QSaleDB();
    ui->setupUi(this);
    QFont frt;
    frt.setPointSize(18);
    ui -> sum_l -> setFont(frt);
    TableSet();
}


goods_history::~goods_history()
{

    delete ui;
    delete sale_db;

}

void insert_row_h(QTableWidget *table_widget,QStringList str){
    int row_count = table_widget -> rowCount();
    table_widget->insertRow(row_count);

    QTableWidgetItem *item = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();
    QTableWidgetItem *item4 = new QTableWidgetItem();
    QTableWidgetItem *item5 = new QTableWidgetItem();
    QTableWidgetItem *item6 = new QTableWidgetItem();


    item -> setText(str[0]);
    item1 -> setText(str[1]);
    if(str[2] == "1")
        item2 -> setText("Sale");
    else
        item2 -> setText("In");
    QString price = QString::number(str[3].toFloat()/100,'f',2);

    item3 -> setText(price);
    item4 -> setText(str[4]);
    item5 -> setText(str[5]);
    item6 -> setText(str[6]);

    table_widget->setItem(row_count, 0, item);
    table_widget->setItem(row_count, 1, item1);
    table_widget->setItem(row_count, 2, item2);
    table_widget->setItem(row_count, 3, item3);
    table_widget->setItem(row_count, 4, item4);
    table_widget->setItem(row_count, 5, item5);
    table_widget->setItem(row_count, 6, item6);
}

void goods_history::TableSet(){
    ui -> table_g -> hide();

    QTableWidgetItem *h_no = new QTableWidgetItem("1");
    ui -> table_g -> setVerticalHeaderItem(0,h_no);
    ui -> table_g -> setSelectionBehavior(QAbstractItemView::SelectRows);
    ui -> table_g -> setSelectionMode(QAbstractItemView::SingleSelection);


    QStringList header;
    header << tr("Code") << tr("Name") <<tr("Sale/In") <<tr ("Price") << tr("Count") << tr("Date") <<tr("Time");
    ui -> table_g -> setHorizontalHeaderLabels(header);
    ui -> table_g -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui -> table_g -> horizontalHeader() -> setStretchLastSection(true);
    ui -> table_g -> show();
}

void goods_history::clear(){

    ui ->table_g ->clearContents();
    ui ->table_g ->setRowCount(0);
    TableSet();
}



void goods_history::on_search_p_clicked()
{
    clear();
    QString f_date,t_date;
    f_date = ui ->fy_c->currentText() + "-" + ui ->fm_c->currentText() + "-" + ui ->fd_c->currentText();
    t_date = ui ->ty_c->currentText() + "-" + ui ->tm_c->currentText() + "-" + ui ->td_c->currentText();
    std::vector< QStringList > ans = sale_db ->search(f_date,t_date);
    if(ans.size() == 0) {
        QMessageBox::information(this, QObject::tr("Advise.."),
                              QObject::tr("No History."));
        return;
    }
    float i_sum = 0;
    float o_sum = 0;
    for(unsigned int i = 0; i < ans.size(); ++i){
        insert_row_h(ui ->table_g,ans[i]);
        if(ans[i][2] == "1") o_sum += ans[i][3].toFloat()*ans[i][4].toFloat();
        if(ans[i][2] == "0") i_sum += ans[i][3].toFloat()*ans[i][4].toFloat();
    }
    QString st = "InSum : " + QString::number(i_sum/100,'f',2) +
            "  OSum : " + QString::number(o_sum/100,'f',2)
                + "   Bonus : " + QString::number((o_sum - i_sum)/100,'f',2);
    ui ->sum_l ->setText(st);
}
