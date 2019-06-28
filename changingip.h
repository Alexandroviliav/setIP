#ifndef CHANGINGIP_H
#define CHANGINGIP_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include <QHostAddress>
#include <stdlib.h>
#include <QByteArray>

class ChangingIP : public QObject
{
    Q_OBJECT
public:
    explicit ChangingIP(QObject *parent = nullptr);
    void setIP(QString ip, QString mask);
    QHostAddress getAddress();
    void setAdressDefault();

signals:

public slots:
private:
    QNetworkInterface defaultInterface;
    QNetworkInterface currentInterface;
    QNetworkAddressEntry defaultEntry;
    QNetworkAddressEntry currentEntry;
    QHostAddress address;
    QHostAddress defaultAddress;
};

#endif // CHANGINGIP_H
