#include "udpserver.h"

UdpServer::UdpServer(QObject *parent) : QObject(parent)
{
    pudp = new QUdpSocket();

    QTimer *timer = new QTimer();
    timer->setInterval(500);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(slotSendDatagram()));
}

//void UdpServer::slotSendDatagram()
//{
//    qDebug() << "1";
//    QByteArray baDatagram;
//    char a = a;
//    baDatagram.insert(20,a);
////    QDataStream out(&baDatagram, QIODevice::WriteOnly);
//    pudp->writeDatagram(baDatagram,*ip,9000);
//    qDebug() << baDatagram;
//}
