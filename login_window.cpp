#include "UI_h/login_window.h"
#include "ui_login_window.h"
#include "Database/people.h"

#include "mainwindow.h"

#include <QImage>
#include <QPixmap>

login_window::login_window(QWidget *parent):
    QDialog(parent)
{
    ui = new Ui::login_window;
    people  = new QPeopleDB();
    ui -> setupUi(this);
    this->setMinimumSize(this->width(),this->height());
    this->setMaximumSize(this->width(),this->height());

    QPixmap pix;
    pix.load(":/logo/logo2");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5,Qt::KeepAspectRatio);
    ui ->logo_l ->setPixmap(pix);

}

login_window::~login_window()
{
    delete ui;
    delete people;
}


void login_window::on_pushButton_clicked()
{
    PEOPLE input;

    input.name = this -> ui -> lineEdit -> text();
    input.password = this -> ui -> lineEdit_2 -> text();

    if(input.password == ""){
        QMessageBox::information(this, tr("Cann't login"), tr("Please input password!"));
        return ;
    }

    this -> people -> correct = this -> people -> find(input);

    if(this -> people -> correct){
        this -> hide();
        MainWindow *w = new MainWindow(this);
        if(this -> people -> permission != ADMIN){
            w -> HideButtons();\
        }
        w -> show();
    }else{
        QMessageBox::information(this, tr("Cann't login"), tr("Incorrect password!"));
    }
}
