#ifndef LOGINWINDOW
#define LOGINWINDOW

#include <QDialog>


class login_window:public QDialog{
    Q_OBJECT
public:
    explicit login_window(QWidget *parent = 0):
        QDialog(parent){

    }
    ~login_window(){}
private:
    //login_window *ui;
};



#endif // LOGINWINDOW

