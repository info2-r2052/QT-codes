#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datauser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AgregarDataSave(DataUser user);
    DataUser LeerDataSave(int index);
    void BorrarDataSave(int index);
    void ModificarDataSave(DataUser user, int index);

    void ActualizarDataPlantilla(void);

private slots:
    void on_pushButton_Crear_clicked();

    void on_pushButton_Modificar_clicked();

private:
    Ui::MainWindow *ui;

    QVector<DataUser> dataSave;
};
#endif // MAINWINDOW_H
