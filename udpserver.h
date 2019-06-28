#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QDataStream>
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = nullptr);

signals:

public slots:
    //void slotSendDatagram();
private:
    QUdpSocket* pudp;
    QHostAddress *ip = new QHostAddress("169.254.1.3");
};

#endif // UDPSERVER_H
