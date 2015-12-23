#include "goods_info.h"
#include "ui_goods_info.h"

goods_info::goods_info(QWidget *parent):
    QDialog(parent)
{
    ui = new Ui::goods_info;
    ui -> setupUi(this);
    p = (MainWindow *)this ->parentWidget();
}

goods_info::~goods_info()
{
    delete ui;
}

void goods_info::on_pushButton_clicked()
{
    new_goods.code = ui ->code_l->text();
    new_goods.count = ui ->count_l->text();
    new_goods.name = ui ->name_l->text();
    new_goods.iprice = ui ->price_l->text();
    new_goods.oprice = ui ->oprice_l ->text();

    if(new_goods.code == "" || new_goods.count == "" ||
            new_goods.name == "" || new_goods.iprice == "" || new_goods.oprice == ""){
        return;
    }
    p ->goods_db->add_new(new_goods);
    p ->sale_db ->update_n(new_goods);
    this -> hide();
    ui ->code_l ->clear();
    ui ->count_l ->clear();
    ui ->name_l ->clear();
    ui ->oprice_l ->clear();
    ui ->price_l ->clear();
}
