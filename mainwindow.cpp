#include "mainwindow.h"
#include "ui_mainwindow.h"

//мой порт 9001, адрес 169.254.1.2
//порт Вовы 9000, адрес 169.254.1.3
//посылка 20 байт

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addr = new ChangingIP;
    udpServer = new QUdpSocket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setIPButton_clicked()
{
    //Создание визуального таймера на паузу для идентификации сети
    timerCounter = 4;
    time = new QTime(0, 0, timerCounter);
    ui->timerSetIP->setText(time->toString());
    tmr = new QTimer;
    tmr->setInterval(1000);
    connect(tmr,SIGNAL(timeout()),this,SLOT(updateTime()));
    tmr->start();

    addr->setIP("192.168.1.100", "255.255.255.0");

    //Пауза нужна для идентификации сети
    QTest::qWait(4000);
    udpClient = new QUdpSocket();

    //Задаем ip адрес и порт клиента
    QHostAddress adr("192.168.1.100");
    qDebug() << udpClient->bind(adr,9001,QUdpSocket::ShareAddress);
    qDebug() << "Состояние 1: " << udpClient->state();

    //Задаем ip адрес и порт сервера, подключаемся к нему
    udpClient->connectToHost("169.254.1.3",9000,QIODevice::ReadWrite,QAbstractSocket::AnyIPProtocol);
    qDebug() << "Состояние 2: " << udpClient->state();
    qDebug() << "Адрес: " << udpClient->peerAddress().toString();

    udpClient->open(QIODevice::ReadWrite);
    connect(udpClient,SIGNAL(readyRead()),this,SLOT(slotProcessDatagrams()));
}

void MainWindow::on_setDefaultIPButton_clicked()
{
    addr->setAdressDefault();
}

void MainWindow::slotSendDatagram()
{
    //Передача данных на порт
    char a = 1;
    QByteArray baDatagram(20,a);
    udpServer->writeDatagram(baDatagram,*ipServer,9000);  
    qDebug() << "Ушло: " << baDatagram.constData();   
}

void MainWindow::slotProcessDatagrams()
{
    //Чтение датаграммы по сигналу readyRead()
    while (udpClient->hasPendingDatagrams())
    {
        QByteArray baDatagramIn;
        baDatagramIn.resize(udpClient->pendingDatagramSize());
        udpClient->readDatagram(baDatagramIn.data(),baDatagramIn.size());
        qDebug() << "Пришло: " << baDatagramIn.constData();
     }
}

void MainWindow::on_dataTransferButton_clicked()
{
    //По таймеру отсылаем посылки на сервер
    QTimer *timer = new QTimer();
    timer->setInterval(1000);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(slotSendDatagram()));
}

void MainWindow::updateTime()
{
    timerCounter--;
    time->setHMS(0,0,timerCounter);
    ui->timerSetIP->setText(time->toString());

    if (timerCounter == 0){
        tmr->stop();
    }
}
