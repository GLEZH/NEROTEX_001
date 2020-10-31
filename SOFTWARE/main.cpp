#include "mainwindow.h"
#include "start1.h"
#include <unistd.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Start1 s;
    s.show();


    return a.exec();
}
