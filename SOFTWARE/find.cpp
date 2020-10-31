#include "find.h"
#include "ui_find.h"
#include "mainwindow.h"

Find::Find(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Find)
{
    ui->setupUi(this);

    ui->pushButton_2->setStyleSheet("QPushButton{background: transparent;}");

    _name = "";
    _sok = new QTcpSocket(this);
    _sok->connectToHost(leHost, 1234);
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
}

Find::~Find()
{
    delete ui;
}

void Find::onSokDisplayError(QAbstractSocket::SocketError socketError)
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


void Find::onSokReadyRead()
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
            QStringList l =  users.split(",");
            ui->lwUsers->addItems(l);
        }
        break;
        case MyClient::comPublicServerMessage:
        {
            QString message;
            in >> message;
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
            _name = user;
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
        case MyClient::comUserJoin:
        {
            QString name;
            in >> name;
            ui->lwUsers->addItem(name);
        }
        break;
        case MyClient::comUserLeft:
        {
            QString name;
            in >> name;
            for (int i = 0; i < ui->lwUsers->count(); ++i)
                if (ui->lwUsers->item(i)->text() == name)
                {
                    ui->lwUsers->takeItem(i);
                    break;
                }
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

void Find::onSokConnected()
{
    _blockSize = 0;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)MyClient::comAutchReq;
    out << NameClient;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void Find::onSokDisconnected()
{
    ui->lwUsers->clear();
}




void Find::on_pushButton_clicked()
{
    pb_name = ui->leName->text();
    emit pbEmit(_name, pb_name);
    close();
    _sok->disconnectFromHost();
}

void Find::on_pushButton_2_clicked()
{
    close();
}
