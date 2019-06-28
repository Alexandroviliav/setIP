#include "udpclient.h"

UdpClient::UdpClient(QObject *parent) : QObject(parent)
{
    pudp = new QUdpSocket();
    pudp->bind(*ip, 9001);
    connect(pudp,SIGNAL(readyRead()),this,SLOT(slotProcessDatagrams()));
}

void UdpClient::slotProcessDatagrams()
{
    QByteArray baDatagram;
    do {
        baDatagram.resize(pudp->pendingDatagramSize());
        pudp->readDatagram(baDatagram.data(),baDatagram.size());
    }   while (pudp->hasPendingDatagrams());

    qDebug() << baDatagram;
}
