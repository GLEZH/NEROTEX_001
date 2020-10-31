#include "signin.h"
#include "device.h"
#include "mainwindow.h"
#include "ui_signin.h"
#include <QMessageBox>

SignIn::SignIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_pbEnter_clicked()
{
    if(login == ui->leLogin->text() && password == ui->lePassword->text())
    {
       MainWindow *w = new MainWindow();
        w->show();
        close();
    }else{
        QMessageBox::warning(this, "Ошибка", "Не правильный логин или пароль");
        return;
    }
}
