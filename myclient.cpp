#include "myclient.h"

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
}

void MyClient::sendMsg(QString msg)
{
    socket->write(msg.toLocal8Bit().constData());
    socket->flush();
}

QString MyClient::recvMsg()
{
    while (socket->bytesAvailable())
    {
        temp = socket->readAll();
    }
    return temp;
}
