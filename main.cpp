#include <QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer mServer;
    mServer.runServer(QHostAddress::Any, 1234);

    return a.exec();
}
