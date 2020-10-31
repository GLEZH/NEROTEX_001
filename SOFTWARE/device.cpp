#include "device.h"
#include "ui_device.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "mainwindow.h"

device::device(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::device)
{
    ui->setupUi(this);

    QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
    QFile fileInput;

    QString myPath = home + "/lName.txt";

    fileInput.setFileName(myPath);

    fileInput.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QTextStream streamInput(&fileInput);

    streamInput >> Name;
    ui->lb_1->setText(Name);
    streamInput >> RealName;
    QMessageBox::critical(this, " Critical Error", Name, QMessageBox::Ok, 0);
    QMessageBox::critical(this, " Critical Error", RealName, QMessageBox::Ok, 0);

    _name = "";
    _sok = new QTcpSocket(this);
    _sok->connectToHost(leHost, 1234);
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));

}


device::~device()
{
    delete ui;
}

void device::onSokDisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Error", "The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Error", "The connection was refused by the peer.");
        break;
    default:
        QMessageBox::information(this, "Error", "The following error occurred: "+_sok->errorString());
    }
}

void device::onSokReadyRead()
{
    QDataStream in(_sok);
    //если считываем новый блок первые 2 байта это его размер
    if (_blockSize == 0) {
        //если пришло меньше 2 байт ждем пока будет 2 байта
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        //считываем размер (2 байта)
        in >> _blockSize;
        qDebug() << "_blockSize now " << _blockSize;
    }
    //ждем пока блок прийдет полностью
    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
        //можно принимать новый блок
        _blockSize = 0;
    //3 байт - команда серверу
    quint8 command;
    in >> command;
    qDebug() << "Received command " << command;

    switch (command)
    {
        break;
        case MyClient::comUsersOnline:
        {
            QString users;
            in >> users;
            if (users == "")
                return;
            l =  users.split(",");
            AddToLog();
        }
        break;
        case MyClient::comPublicServerMessage:
        {
            QString message;
            in >> message;
            msg = message;
        }
        break;
        case MyClient::comMessageToAll:
        {
            QString user;
            in >> user;
            QString message;
            in >> message;
        }
        break;
        case MyClient::comMessageToUsers:
        {
            QString user;
            in >> user;
            QString message;
            in >> message;
        }
        break;
        case MyClient::comPrivateServerMessage:
        {
            QString message;
            in >> message;
        }
        break;
        case MyClient::comErrNameInvalid:
        {
            QMessageBox::information(this, "Error", "This name is invalid.");
            _sok->disconnectFromHost();
        }
        break;
        case MyClient::comErrNameUsed:
        {
            QMessageBox::information(this, "Error", "This name is already used.");
            _sok->disconnectFromHost();
        }
        break;
    }
}

void device::onSokConnected()
{
    _blockSize = 0;

    //try autch
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)MyClient::comAutchReq;
    out << NameClient;
    _name = NameClient;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void device::AddToLog()
{
    for(int i(0); i < 20; i ++)
    {
        if(l[i] == RealName)
        {

        }
    }
}

void device::on_pushButton_clicked()
{
    close();
}
