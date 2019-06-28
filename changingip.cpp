#include "changingip.h"

ChangingIP::ChangingIP(QObject *parent) : QObject(parent)
{

    foreach(currentInterface, QNetworkInterface::allInterfaces())
    {
         if (currentInterface.flags().testFlag(QNetworkInterface::IsUp) &&
                !currentInterface.flags().testFlag(QNetworkInterface::IsLoopBack))
            foreach (currentEntry, currentInterface.addressEntries())
            {
                if (currentInterface.hardwareAddress() != "00:00:00:00:00:00" &&
                    currentEntry.ip().toString().contains(".") &&
                        !currentInterface.humanReadableName().contains("VM")){
                    defaultInterface = currentInterface;
                    defaultEntry = currentEntry;
                }

            }
    }

    qDebug() << "default ip: " << defaultEntry.ip().toString();
    qDebug() << "default netmask: " << defaultEntry.netmask().toString();
}

void ChangingIP::setIP(QString ip, QString mask)
{
    qDebug() << "setAdress";
    address.setAddress(ip);
    QString message("Cmd /x/c netsh interface ip set address Ethernet static " + ip + " " + mask);
    QByteArray b1 = message.toLocal8Bit();
    char *c1 = b1.data();
    system(c1);
}

void ChangingIP::setAdressDefault()
{
    qDebug() << "setAdressDefault()";
    system("Cmd /x/c netsh interface ip set address name=Ethernet source=dhcp");
}

QHostAddress ChangingIP::getAddress()
{
    qDebug() << "current ip: " << currentEntry.ip().toString();
    qDebug() << "current netmask: " << currentEntry.netmask().toString();
    return address;
}
