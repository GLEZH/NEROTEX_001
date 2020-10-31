#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "find.h"
#include "device.h"
#include "qdynamicbutton.h"
#include <QPushButton>
#include <QVector>
#include <QDir>
#include <QFile>
#include <fstream>
#include <QTextStream>
#include <QMessageBox>
#include <QLineEdit>
#include <QTextDecoder>
#include <QStringList>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);



    QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
    QFile fileInput;

    QString myPath = home + "/testInput.txt";

    fileInput.setFileName(myPath);


       fileInput.open(QFile::ReadWrite);

           QTextStream streamInput(&fileInput);
            //double buff;
            streamInput >> pb_count;
            //QMessageBox::critical(this, " Critical Error", QString::number(buff), QMessageBox::Ok, 0);
            int i = 0;
           while(!streamInput.atEnd())
           {
               streamInput >> buffer_pb;
                    i++;
               buffer_pb2 += buffer_pb + " ";
           }
           pb_List = buffer_pb2.split(" ");
           fileInput.close();

           QDynamicButton *button;

           for(int i(0); i < pb_count; i++)
           {
               button = new QDynamicButton(this);
               button->setText(pb_List[i]);
               ui->layout_main->addWidget(button);
               connect(button, SIGNAL(clicked()), this, SLOT(Button()));

           }

           QFile fileOutput2;

           QString myPath2 = home + "/Name.txt";

           fileOutput2.setFileName(myPath2);

           fileOutput2.open(QIODevice::WriteOnly | QIODevice::Truncate);
           i = 0;
           for(int i(0); i < pb_count; i++)
           {
              streamInput >> buffer_Name;
              buffer_Name2 += buffer_Name + " ";
           }
          pb_List = buffer_Name2.split(" ");
          fileInput.close();





           /*QStringList lineData = QString(file.readLine()).split(" ");


           pb_count = lineData[0].toInt();
           QMessageBox::critical(this, " Critical Error", QString::number(pb_count), QMessageBox::Ok, 0);
           int i;
           while(!stream.atEnd())
           {
               QMessageBox::critical(this, " Critical Error", "12", QMessageBox::Ok, 0);
               //pb_count = lineData[0].toInt();
               //buffer_pb += stream.readLine() + " ";
               stream >> pb_List[i];
               QMessageBox::critical(this, " Critical Error", "16", QMessageBox::Ok, 0);
               i++;
           }
           QMessageBox::critical(this, " Critical Error", buffer_pb, QMessageBox::Ok, 0);

           pb_List = buffer_pb.split(" ");

           QMessageBox::critical(this, " Critical Error", "13", QMessageBox::Ok, 0);

           for(int i(0); i < pb_count; i++)
           {
               QMessageBox::critical(this, " Critical Error", QString::number(pb_count), QMessageBox::Ok, 0);
               QPushButton *button = new QPushButton(this);
               button->setText(pb_List[i]);
               ui->layout_main->addWidget(button);
           }

           QMessageBox::critical(this, " Critical Error", "14", QMessageBox::Ok, 0);

           file.close();
       }
   }

   QFile file2;
   QTextStream stream2(&file);
   QString myPath2 = home + "/testInput2.txt";
   file.setFileName(myPath2);

   if(!file.exists())
   {
       file.open(QIODevice::WriteOnly | QIODevice::Truncate);
       n = 1;
   }*/



}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_nu_triggered()
{
    Find *f = new Find(this);
    f->show();
    connect(f, SIGNAL(pbEmit(QString , QString )), this, SLOT(pbSlot(QString , QString )));
    //QMessageBox::warning(this, " Critical Error", "1", QMessageBox::Ok, 0);
}

void MainWindow::pbSlot(QString name_, QString pb_)
{


    for(int i(0); i < pb_count; i++)
    {
        for(int i = 0; i < ui->layout_main->count(); i++)
        {
            //Производим каст элемента слоя в объект динамической кнопки

            QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->layout_main->itemAt(i)->widget());

        button->hide();
        delete button;
    }
    }
    pb_count++;

    QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
    QFile fileOutput;

    QString myPath = home + "/testInput.txt";

    fileOutput.setFileName(myPath);

    fileOutput.open(QIODevice::WriteOnly | QIODevice::Truncate);
    //QMessageBox::warning(this, " Critical Error", "1", QMessageBox::Ok, 0);
    if(fileOutput.isOpen())
    {
        QTextStream streamOutput(&fileOutput);

        QDynamicButton *button;

            streamOutput << pb_count << "\n";
            //QMessageBox::warning(this, " Critical Error", "1", QMessageBox::Ok, 0);
            buffer_pb2 += pb_ + " ";
            pb_List = buffer_pb2.split(" ");
            //QMessageBox::warning(this, " Critical Error", buffer_pb2, QMessageBox::Ok, 0);

            for(int i(0); i < pb_count; i++)
            {
                streamOutput << pb_List[i] + "\n";
                //QMessageBox::warning(this, " Critical Error", pb_List[i], QMessageBox::Ok, 0);
            }

            for(int i(0); i < pb_count; i++)
            {
                button = new QDynamicButton(this);
                button->setText(pb_List[i]);
                ui->layout_main->addWidget(button);
                connect(button, SIGNAL(clicked()), this, SLOT(Button()));
            }


                 fileOutput.close();
    }

    QFile fileOutput2;

    QString myPath2 = home + "/Name.txt";

    fileOutput2.setFileName(myPath2);

    fileOutput2.open(QIODevice::WriteOnly | QIODevice::Truncate);


    if(fileOutput2.isOpen())
    {
        QTextStream streamOutput2(&fileOutput);

            buffer_Name += name_;
            pb_Name = buffer_Name.split(" ");
            QMessageBox::warning(this, " Critical Error", buffer_Name, QMessageBox::Ok, 0);

            for(int i(0); i < pb_count; i++)
            {
                streamOutput2 << pb_Name[i] + "\n";
            }


                 fileOutput2.close();
    }






}


void MainWindow::on_actiond_triggered()
{
    QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
    //QString home ="C:/";
    QString myPath = home + "/testInput.txt";
    QFile file;
    file.setFileName(myPath);
    file.remove();

}

void MainWindow::Button()
{
    QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
    QFile fileOutput;

    QString myPath = home + "/lName.txt";

    fileOutput.setFileName(myPath);

    fileOutput.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QTextStream streamOutput(&fileOutput);

    pb_List = buffer_pb2.split(" ");
    pb_Name = buffer_Name2.split(" ");
    QDynamicButton *button = (QDynamicButton*) sender();
    int i = (button->getID());
    i = i-1;
    QMessageBox::critical(this, " Critical Error", pb_List[i], QMessageBox::Ok, 0);
    QMessageBox::critical(this, " Critical Error", pb_Name[i], QMessageBox::Ok, 0);
    streamOutput << pb_List[i];
    streamOutput << pb_Name[i];
    device *d = new device(this);
    d->show();
    emit dev(pb_List[i], pb_Name[i]);
    //emit dev(button->text());
}


