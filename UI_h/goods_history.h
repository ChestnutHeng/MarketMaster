#ifndef GOODS_HISTORY_H
#define GOODS_HISTORY_H

#include <QDialog>

class QGoodsDB;
struct SALE_GOODS;
struct IN_GOODS;
class goods_info;
class QSaleDB;

namespace Ui {
class goods_history;
}

class goods_history : public QDialog
{
    Q_OBJECT

public:
    explicit goods_history(QWidget *parent = 0);
    ~goods_history();
    void TableSet();
    void flush_price();
    void clear();

private slots:
    void on_search_p_clicked();

private:
    Ui::goods_history *ui;
    QSaleDB *sale_db;
};

#endif // GOODS_HISTORY_H
