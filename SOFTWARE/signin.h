#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>

namespace Ui {
class SignIn;
}

class SignIn : public QWidget
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void on_pbEnter_clicked();

private:
    Ui::SignIn *ui;
    QString login = "admin";
    QString password = "admin";
};

#endif // SIGNIN_H
