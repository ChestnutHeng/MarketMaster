#include "ui_user_manage_window.h"
#include "mainwindow.h"

#include "UI_h/user_manage_window.h"
#include "UI_h/login_window.h"
#include "Database/people.h"

#include <QMessageBox>

user_manage_window::user_manage_window(QWidget *parent):
    QDialog(parent)
{
    ui = new Ui::user_manage_window;
    ui -> setupUi(this);
    this->setMinimumSize(this->width(),this->height());
    this->setMaximumSize(this->width(),this->height());

    people = new QPeopleDB();
}

user_manage_window::~user_manage_window()
{
    delete ui;
}


void user_manage_window::on_add_b_clicked()
{
    PEOPLE p ;
    p.name = ui ->user_l ->text();
    p.password = ui ->pwd_l ->text();
    if(p.name == "" || p.password == ""){
        QMessageBox::information(this, QObject::tr("Error"),
                                tr("Every item can't be null"));
        return;
    }
    if(ui ->admin_c ->isChecked()){
        p.permission = ADMIN;
    }else{
        p.permission = USER;
    }
    people ->add(p);
    QMessageBox::information(this, QObject::tr("Info"),
                            tr("User Added."));
}


void user_manage_window::on_del_b_clicked()
{
    PEOPLE p ;
    p.name = ui ->user_l ->text();
    p.password = ui ->pwd_l ->text();
    people ->del(p);
    QMessageBox::information(this, QObject::tr("Info"),
                            tr("User Deleted."));
}
