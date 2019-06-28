#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <changingip.h>
#include <QUdpSocket>
#include <QByteArray>
#include <QDebug>
#include <udpclient.h>
#include <udpserver.h>
#include <QAbstractSocket>
#include <stdlib.h>
#include <QtTest/QTest>
#include <QTimer>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotProcessDatagrams();

private slots:
    void on_setIPButton_clicked();

    void on_setDefaultIPButton_clicked();

    void slotSendDatagram();

    void on_dataTransferButton_clicked();

    void updateTime();

private:
    Ui::MainWindow *ui;
    ChangingIP *addr;
    QUdpSocket *udpSocketSend;
    QUdpSocket *udpSocketGet;
    QByteArray *datagram;
    QUdpSocket *udpClient;
    QUdpSocket *udpServer;
    QHostAddress *ipServer = new QHostAddress("169.254.1.3");
    QHostAddress *ipClient = new QHostAddress("169.254.1.2");
    QTimer *tmr;
    int timerCounter;
    QTime *time;
};

#endif // MAINWINDOW_H
