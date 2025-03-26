#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlTableModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSqLTableModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_nuevo_clicked();

    void on_pushButton_eliminar_clicked();

    void on_pushButton_actualizar_clicked();

    void on_pushButton_connect_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mDatabase;
    QSqlTableModel *model;


};
#endif // MAINWINDOW_H
