#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QString Button_name;

private slots:
    void on_action_nu_triggered();
    void pbSlot(QString name_, QString pb_);
    //void UseButton();
    void Button();
    //void UseButton();



    void on_actiond_triggered();

signals:
    void dev(QString, QString);
    //void useButton();

private:
    Ui::MainWindow *ui;

    int pb_count= 0;

    int n = 0;

    QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
    QString myPath = home + "/testInput.txt";
    QFile file;
    QString buffer_pb;
    QString buffer_Name;
    QString buffer_pb2;
    QString buffer_Name2;

    QStringList pb_List;
    QStringList pb_Name;


};

#endif // MAINWINDOW_H
