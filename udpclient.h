#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <QByteArray>
#include <QDebug>

class UdpClient : public QObject
{
    Q_OBJECT
public:
    explicit UdpClient(QObject *parent = nullptr);

signals:

public slots:
    void slotProcessDatagrams();
private:
    QUdpSocket *pudp;
    QHostAddress *ip = new QHostAddress("169.254.1.2");
};

#endif // UDPCLIENT_H
