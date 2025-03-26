#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


#define LED_GREEN_ON        0
#define LED_RED_ON          1
#define LED_GRAY            2
#define LED_BLUE_ON         3
#define LED_RED_GRAYED      4
#define LED_GREEN_GRAYED    5
#define LED_BLUE_GRAYED     6

using namespace Qt::StringLiterals;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->pushButton_LedRed->setStyleSheet("background-color: rgb(200, 150, 150);");
    ui->pushButton_LedGreen->setStyleSheet("background-color: rgb(150, 200, 150);");
    ui->pushButton_LedBlue->setStyleSheet("background-color: rgb(150, 150, 200);");
    ui->label_LedRed->setColour(LED_RED_GRAYED);
    ui->label_LedGreen->setColour(LED_GREEN_GRAYED);
    ui->label_LedBlue->setColour(LED_BLUE_GRAYED);
    ui->lcdNumber_2->setDigitCount(4);

    timerLCD = new QTimer(this);
    timerLedRojo = new QTimer(this);
    timerLedVerde = new QTimer(this);
    timerLedAzul = new QTimer(this);
    connect(timerLCD, &QTimer::timeout, this, &MainWindow::TimerLCDVencido);
    connect(timerLedRojo, &QTimer::timeout, this, &MainWindow::TimerLedRojoVencido);
    connect(timerLedVerde, &QTimer::timeout, this, &MainWindow::TimerLedVerdeVencido);
    connect(timerLedAzul, &QTimer::timeout, this, &MainWindow::TimerLedAzulVencido);

    server.listen(QHostAddress::Any, PORTsERVER);
    //Connect to slot
    connect( &server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_LedGreen_clicked()
{
    static bool flag = true;
    QString buffer;
    char chk=0;

    if( flag ){
        flag = false;
        ui->pushButton_LedGreen->setText("Off");
        ui->pushButton_LedGreen->setStyleSheet("background-color: green;");
        ui->label_LedGreen->setColour(LED_GREEN_ON);

    }else{
        flag = true;
        ui->pushButton_LedGreen->setText("On");
        ui->pushButton_LedGreen->setStyleSheet("background-color: rgb(150, 200, 150);");
        ui->label_LedGreen->setColour(LED_GREEN_GRAYED);

    }
    if( flag )
        buffer = ">L,G,0,";
    else
        buffer = ">L,G,1,";

    for (int i = 0; i < buffer.size() ;i++) {
        chk ^= buffer.toStdString()[i];

    }
    buffer.append(chk);
    buffer.append('<');
    buffer.append('\n');

    if(!sockets.isEmpty() && sockets.at(0)->state() == QAbstractSocket::ConnectedState) {
        sockets.at(0)->write(buffer.toUtf8());
        sockets.at(0)->flush();
    }


    qDebug() << buffer;
    fTimerLedVerdeVencido = false;
    timerLedVerde->start(3000);
}


void MainWindow::on_pushButton_LedRed_clicked()
{
    static bool flag = true;
    QString buffer;
    char chk=0;

    if( flag ){
        flag = false;
        ui->pushButton_LedRed->setText("Off");
        ui->label_LedRed->setColour(LED_RED_ON);
        ui->pushButton_LedRed->setStyleSheet("background-color: red;");
    }else{
        flag = true;
        ui->pushButton_LedRed->setText("On");
        ui->pushButton_LedRed->setStyleSheet("background-color: rgb(200, 150, 150);");
        ui->label_LedRed->setColour(LED_RED_GRAYED);
    }

    if( flag )
        buffer = ">L,R,0,";
    else
        buffer = ">L,R,1,";

    for (int i = 0; i < buffer.size() ;i++) {
        chk ^= buffer.toStdString()[i];

    }
    buffer.append(chk);
    buffer.append('<');
    buffer.append('\n');

    if(!sockets.isEmpty() && sockets.at(0)->state() == QAbstractSocket::ConnectedState) {
        sockets.at(0)->write(buffer.toUtf8());
        sockets.at(0)->flush();
    }

    qDebug() << buffer;
    fTimerLedRojoVencido = false;
    timerLedRojo->start(3000);
}


void MainWindow::on_pushButton_LedBlue_clicked()
{
    static bool flag = true;
    QString buffer;
    char chk=0;

    if( flag ){
        flag = false;
        ui->pushButton_LedBlue->setText("Off");
        ui->pushButton_LedBlue->setStyleSheet("background-color: blue;");
        ui->label_LedBlue->setColour(LED_BLUE_ON);

    }else{
        flag = true;
        ui->pushButton_LedBlue->setText("On");
        ui->pushButton_LedBlue->setStyleSheet("background-color: rgb(150, 150, 200);");
        ui->label_LedBlue->setColour(LED_BLUE_GRAYED);
    }

    if( flag )
        buffer = ">L,B,0,";
    else
        buffer = ">L,B,1,";

    for (int i = 0; i < buffer.size() ;i++) {
        chk ^= buffer.toStdString()[i];

    }
    buffer.append(chk);
    buffer.append('<');
    buffer.append('\n');

    if(!sockets.isEmpty() && sockets.at(0)->state() == QAbstractSocket::ConnectedState) {
        sockets.at(0)->write(buffer.toUtf8());
        sockets.at(0)->flush();
    }

    qDebug() << buffer;
    fTimerLedAzulVencido = false;
    timerLedAzul->start(3000);

}

void MainWindow::MessageReceived(const QString &msg){
    //>D,2345,z<
    //>D,0986,}<
    //>R,OK<
    //>G,OK<
    //>B,OK<
    QString tramaRecibida = msg;
    QStringList campos = tramaRecibida.split(',');
    char chk=0;
    int valor = 0, contadorComas = 0;
    qDebug() << "Mensaje recibido en el tema:" << msg;
    qDebug() << "Contenido del mensaje:" << tramaRecibida;

    //Chequeo de ACKS de Leds
        if( tramaRecibida == ">R,OK<" )
            fTimerLedRojoVencido = true;
        if( tramaRecibida == ">G,OK<" )
            fTimerLedVerdeVencido = true;
        if( tramaRecibida == ">B,OK<" )
            fTimerLedAzulVencido = true;

    if( campos.length() >= 3 ){     //Trama para refresco LCD

        fTimerLCDVencido = true;

        if( campos.at(0) == ">D" ){
            valor = campos.at(1).toInt();

        }

        for( QChar caracter : tramaRecibida ){

            if( contadorComas < 2 ){
                chk ^= caracter.toLatin1();
            }

            if( caracter == ',' )
                contadorComas ++;

        }

        //Chequeo checksum
        if( chk == campos.at(2).at(0).toLatin1() ){
            std::cout << valor << std::endl;
            if( campos.at(2).at(1).toLatin1() == '<' ){  //Chequeo de fin de trama
                ui->lcdNumber_2->display(valor);
                ui->label_LedAck->setColour(LED_GREEN_ON);

            }else{
                ui->lcdNumber_2->display("----");
                ui->label_LedAck->setColour(LED_GRAY);
            }
        }
        fTimerLCDVencido = false;
        timerLCD->stop();
        timerLCD->start(3500);
    }else{                      //Son los ACKs
        //if( tramaRecibida == ">R,OK<" )
        //    fTimerLedRojoVencido = true;
        //if( tramaRecibida == ">G,OK<" )
        //    fTimerLedVerdeVencido = true;
        //if( tramaRecibida == ">B,OK<" )
        //    fTimerLedAzulVencido = true;

    }
}

void MainWindow::TimerLCDVencido(){
    if( !fTimerLCDVencido ){   //No llegó una muestra de LCD en 1 segundo
        ui->label_LedAck->setColour(LED_GRAY);
    }
}


void MainWindow::TimerLedRojoVencido(){
    if( !fTimerLedRojoVencido ){
        ui->label_LedRed->setColour(LED_GRAY);
    }
}

void MainWindow::TimerLedVerdeVencido(){
    if( !fTimerLedVerdeVencido ){
        ui->label_LedGreen->setColour(LED_GRAY);
    }
}

void MainWindow::TimerLedAzulVencido(){
    if( !fTimerLedAzulVencido ){
        ui->label_LedBlue->setColour(LED_GRAY);
    }

}


void MainWindow::onNewConnection()
{
    qDebug() << "onNewConnection\r\n";
    QTcpSocket *clientSocket = server.nextPendingConnection();
    // Ready read
    connect( clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()) );

    connect( clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT( onStateChanged(QAbstractSocket::SocketState)) );
    sockets.push_back(clientSocket);

}

void MainWindow::onStateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << "onStateChanged\r\n";
    if( state == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket *s = static_cast<QTcpSocket*>(QObject::sender());
        sockets.removeOne(s);
    }

}

void MainWindow::onReadyRead()
{
    qDebug() << "onReadyRead\r\n";
    QTcpSocket *s = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray data = s->readAll();
    QString message = data;

    for(QTcpSocket* socket : sockets )
    {
        qDebug() << data;
        MessageReceived(message);

        if( socket != s )
        {

            socket->write(data);
        }
    }
}
