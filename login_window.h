#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW
#include <QDialog>
#include "people.h"

namespace Ui {
    class login_window;
}
class login_window:public QDialog{
    Q_OBJECT
public:
    QPeopleDB *people;
    explicit login_window(QWidget *parent = 0);
    ~login_window();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login_window *ui;
};

#endif // LOGIN_WINDOW

