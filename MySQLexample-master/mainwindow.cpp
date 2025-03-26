#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    if( mDatabase.isOpen() )
    {
        QMessageBox::information(this,"Disconnection","<FONT COLOR='#ffffff'>Database disconnection succesfully</FONT>");
        qDebug()<<"database Disconnected ";
        mDatabase.close();
    }
    else
    {
        QMessageBox::information(this,"Error Disconnection","<FONT COLOR='#ffffff'>Database can't Disconnect. Check previous open</FONT>");
        qDebug()<<"database failed to disconnect ";
        qDebug() << mDatabase.lastError();
    }
    delete ui;
}


void MainWindow::on_pushButton_nuevo_clicked()
{
    model->insertRow(model->rowCount());
}

void MainWindow::on_pushButton_eliminar_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
    model->select();
}

void MainWindow::on_pushButton_actualizar_clicked()
{
    model->select();
}

void MainWindow::on_pushButton_connect_clicked()
{
    mDatabase = QSqlDatabase::addDatabase("QMYSQL");

    //mDatabase.setHostName("192.168.1.102");
    mDatabase.setHostName("192.168.7.101");
    //mDatabase.setHostName("localhost");
    //mDatabase.setHostName("192.168.43.207");
    mDatabase.setPort(3306);
    mDatabase.setUserName("info2");
    mDatabase.setPassword("info2");
    mDatabase.setDatabaseName("info2QT");


    bool aa = mDatabase.open();
    if( aa == true )
    {
      QMessageBox::information(this,"Connection","<FONT COLOR='#ffffff'>Database connection succesfully</FONT>");
      qDebug()<<"database connected";
    }
    else
    {

      QMessageBox::information(this,"No Connected","<FONT COLOR='#ffffff'>Database is not Connected</FONT>");
      qDebug()<<"database failed to connect ";
      qDebug() << mDatabase.lastError();
      return;
    }

    model = new QSqlTableModel(this);
    model->setTable("users");
    model->select();
    ui->tableView->setModel(model);
}
