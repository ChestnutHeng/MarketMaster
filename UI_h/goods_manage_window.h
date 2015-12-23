#ifndef GOODS_MANAGE_WINDOW
#define GOODS_MANAGE_WINDOW

#include <QDialog>
#include <QSql>
#include <vector>

class QGoodsDB;
struct SALE_GOODS;
struct IN_GOODS;
class goods_info;
class QSaleDB;

namespace Ui{
    class goods_manage_window;
}

class goods_manage_window:public QDialog{
    Q_OBJECT
public:
    explicit goods_manage_window(QWidget *parent = 0);
    ~goods_manage_window();
    void TableSet();
    void flush_price();
    void clear();

private slots:

    void on_search_b_clicked();

    void on_remove_b_clicked();

    void on_done_b_clicked();

    void on_new_b_clicked();

private:
    QGoodsDB *goods_db;
    QSaleDB *sale_db;
    std::vector<SALE_GOODS *>goods_list;
    Ui::goods_manage_window *ui;
    goods_info *g;

};
#endif // GOODS_MANAGE_WINDOW

