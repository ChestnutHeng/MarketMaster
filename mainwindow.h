#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

class QGoodsDB;
class QSaleDB;
struct SALE_GOODS;

namespace Ui {
    class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void HideButtons();
    void TableSet();
    void flush_price();
    void clear();

    QGoodsDB *goods_db;
    QSaleDB *sale_db;
private slots:

    void on_u1_clicked();


    void on_search_b_clicked();

    void on_remove_b_clicked();

    void on_done_b_clicked();

    void on_g1_clicked();

    void on_gh_p_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<SALE_GOODS *>goods_list;

};

#endif // MAINWINDOW_H
