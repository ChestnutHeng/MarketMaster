#ifndef USER_MANAGE_WINDOW
#define USER_MANAGE_WINDOW

#include <QDialog>
#include <QSql>

class QPeopleDB;

namespace Ui{
    class user_manage_window;
}

class user_manage_window:public QDialog{
    Q_OBJECT
    public:
        explicit user_manage_window(QWidget *parent = 0);
        ~user_manage_window();

private slots:
    void on_del_b_clicked();

    void on_add_b_clicked();

private:
    Ui::user_manage_window *ui;
    QPeopleDB *people;
};


#endif // USER_MANAGE_WINDOW

