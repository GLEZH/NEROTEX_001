#include "start1.h"
#include "ui_start1.h"
#include "mainwindow.h"
#include "signin.h"
#include <QTimer>
#include <QTime>

Start1::Start1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Start1)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(CloseStart()));
}

void Start1::CloseStart()
{
    SignIn *w = new SignIn();
    w->show();
    timer->stop();
    close();
}

Start1::~Start1()
{
    delete ui;
}
