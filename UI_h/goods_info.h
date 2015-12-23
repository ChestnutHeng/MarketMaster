#ifndef GOODS_INFO
#define GOODS_INFO

#include <QDialog>
#include "mainwindow.h"

#include "Database/goods.h"

namespace Ui {
    class goods_info;
}

class goods_info:public QDialog{
    Q_OBJECT
public:
    explicit goods_info(QWidget *parent = 0);
    ~goods_info();

private slots:
    void on_pushButton_clicked();

private:
    Ui::goods_info *ui;
    IN_GOODS new_goods;
    MainWindow *p ;
};


#endif // GOODS_INFO

