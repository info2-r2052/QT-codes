#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Crear_clicked()
{
    UserDialog userDialog;

    if(userDialog.exec() == QDialog::Accepted){
        DataUser user = userDialog.GetData();

        AgregarDataSave(user);

        //-------------------------------------
        // Esta funcion se encarga de agregar una fila a la plantilla
        ActualizarDataPlantilla();
    }
}

void MainWindow::AgregarDataSave(DataUser user){
    dataSave.push_back(user);
}

void MainWindow::ModificarDataSave(DataUser user, int index){
    dataSave.replace(index, user);
}

DataUser MainWindow::LeerDataSave(int index){
    return dataSave.at(index);
}

void MainWindow::BorrarDataSave(int index){
    dataSave.removeAt(index);
}

void MainWindow::ActualizarDataPlantilla(void){

    ui->treeWidget->clear();

    for(int i = 0 ; i < dataSave.size() ; i++){
        DataUser temp = dataSave.at(i);

        QStringList columnas;

        columnas.append(temp.getNombre());
        columnas.append(temp.getApellido());
        columnas.append(QString::number(temp.getEdad()));

        QTreeWidgetItem* tmpitem = new QTreeWidgetItem(columnas);

        ui->treeWidget->addTopLevelItem(tmpitem);
    }
}


void MainWindow::on_pushButton_Modificar_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();

    QModelIndex index = ui->treeWidget->currentIndex();

    if (item) {
        UserDialog userDialog;

        userDialog.SetData( item->text(0),
                            item->text(1),
                            item->text(2).toInt());

        if(userDialog.exec() == QDialog::Accepted){
            DataUser user = userDialog.GetData();

            //-------------------------------------
            // Esta funcion se encarga de agregar una fila a la plantilla
            ModificarDataSave(user, index.row());

            ActualizarDataPlantilla();
        }


    } else {

    }
}

