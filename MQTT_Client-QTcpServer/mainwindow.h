#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttTopicName>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>

#define PORTsERVER  10234


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_LedGreen_clicked();

    void on_pushButton_LedRed_clicked();

    void on_pushButton_LedBlue_clicked();

    void TimerLCDVencido();

    void TimerLedRojoVencido();

    void TimerLedVerdeVencido();

    void TimerLedAzulVencido();

    void onNewConnection();

    void onReadyRead();

    void onStateChanged(QAbstractSocket::SocketState state);

    void MessageReceived(const QString &msg);


private:
    Ui::MainWindow *ui;
    QTimer *timerLCD;
    QTimer *timerLedRojo;
    QTimer *timerLedVerde;
    QTimer *timerLedAzul;
    bool fTimerLCDVencido = true;
    bool fTimerLedRojoVencido = true;
    bool fTimerLedVerdeVencido = true;
    bool fTimerLedAzulVencido = true;
    QTcpServer server;
    QList<QTcpSocket*> sockets;

};
#endif // MAINWINDOW_H
