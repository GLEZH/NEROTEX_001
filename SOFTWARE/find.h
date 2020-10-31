#ifndef FIND_H
#define FIND_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include "C:\Users\Povelitel\Desktop\TS\Lab2_server\myclient.h"
#include <QMessageBox>
class MyClient;


namespace Ui {
class Find;
}

class Find: public QWidget
{
    Q_OBJECT

public:
    explicit Find(QWidget *parent = 0);
    ~Find();

private slots:
    void onSokConnected();
    void onSokDisconnected();
    void onSokReadyRead();
    void onSokDisplayError(QAbstractSocket::SocketError socketError);


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void pbEmit(QString name_, QString pb_);

private:
    Ui::Find        *ui;
    QTcpSocket      *_sok;
    quint16         _blockSize;
    QString         _name;
    QString         NameClient      = "MainClient";
    QString         leHost          = "192.168.0.17";
    //QString         leHost          = "127.0.0.1";
    QString         pb_name;
};

#endif // FIND_H
