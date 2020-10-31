#ifndef DEVICE_H
#define DEVICE_H

#include <QWidget>
#include "mainwindow.h"
#include <QTcpSocket>
#include <QHostAddress>
#include "C:\Users\Povelitel\Desktop\TS\Lab2_server\myclient.h"
#include <QMessageBox>

namespace Ui {
class device;
}

class device : public QWidget
{
    Q_OBJECT

public:
    explicit device(QWidget *parent = nullptr);
    ~device();

private slots:

    void onSokReadyRead();
    void onSokDisplayError(QAbstractSocket::SocketError socketError);
    void onSokConnected();

    void on_pushButton_clicked();

private:
    Ui::device *ui;
    QTcpSocket *_sok;
    quint16 _blockSize;
    QString _name;
    QString RealName;
    QString Name;
    QStringList l;
    QString msg;
    QString         NameClient      = "MainClient";
    QString         leHost          = "192.168.0.17";
    //QString         leHost          = "127.0.0.1";
    void AddToLog();
};

#endif // DEVICE_H
