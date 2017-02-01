#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>
#include <QHashIterator>
#include <QString>
#include <QMutex>
#include "myclient.h"

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void runServer(QHostAddress address, int port);

signals:

public slots:
    void newConnection();
    void closedConnection();
    void broadcastMsg();

private:
    QTcpServer *server;
    QHash<QTcpSocket*, MyClient*> clientsList;
    QHash<QTcpSocket*, MyClient*>::iterator i;
    QMutex mutex;
};

#endif // MYSERVER_H
