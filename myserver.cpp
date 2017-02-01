#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void MyServer::newConnection()
{
    MyClient *client = new MyClient(this);
    client->socket = server->nextPendingConnection();
    connect(client->socket,SIGNAL(disconnected()),this,SLOT(closedConnection()));
    client->sendMsg("Connected!\n");
    qDebug() << client->socket << "Connected!";
    mutex.lock();
    clientsList.insert((client->socket), client);
    mutex.unlock();
    connect(client->socket,SIGNAL(readyRead()),this,SLOT(broadcastMsg()));
}

void MyServer::closedConnection()
{
    qDebug() << sender() << "Closed connection!";
    qDebug() << clientsList;
    mutex.lock();
    clientsList.remove((QTcpSocket*)sender());
    mutex.unlock();
    sender()->deleteLater();
    qDebug() << clientsList;
}

void MyServer::runServer(QHostAddress address, int port)
{
    if(!server->listen(address,port))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started";
    }
}

void MyServer::broadcastMsg()
{
    mutex.lock();
    for (i = clientsList.begin(); i != clientsList.end(); ++i) {
        i.value()->sendMsg(clientsList[(QTcpSocket*)sender()]->recvMsg());
    }
    mutex.unlock();
}
