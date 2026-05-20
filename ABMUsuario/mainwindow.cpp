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

// =============================================================================
// ALTA (CREAR): agregar un usuario nuevo
// =============================================================================
// Flujo:
//   1) Abrir el diálogo vacío (UserDialog).
//   2) Si el usuario pulsa Aceptar, leer los datos con GetData().
//   3) Guardar en dataSave con AgregarDataSave().
//   4) Refrescar la tabla con ActualizarDataPlantilla().
// =============================================================================
void MainWindow::on_pushButton_Crear_clicked()
{
    UserDialog userDialog;

    // exec() abre el diálogo en forma modal y devuelve Accepted o Rejected
    if (userDialog.exec() == QDialog::Accepted) {
        DataUser user = userDialog.GetData();

        AgregarDataSave(user);
        ActualizarDataPlantilla();
    }
}

// =============================================================================
// MODIFICACIÓN: cambiar un usuario ya existente
// =============================================================================
// Flujo:
//   1) Obtener la fila seleccionada en treeWidget (currentItem + currentIndex).
//   2) Si hay selección, abrir el diálogo con los datos actuales (SetData).
//   3) Si acepta, reemplazar en dataSave en esa posición (index.row()).
//   4) Refrescar la tabla.
// =============================================================================
void MainWindow::on_pushButton_Modificar_clicked()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    QModelIndex index = ui->treeWidget->currentIndex();

    if (item) {
        UserDialog userDialog;

        // text(0), text(1), text(2) corresponden a las columnas NOMBRE, APELLIDO, EDAD
        userDialog.SetData(item->text(0),
                           item->text(1),
                           item->text(2).toInt());

        if (userDialog.exec() == QDialog::Accepted) {
            DataUser user = userDialog.GetData();

            ModificarDataSave(user, index.row());
            ActualizarDataPlantilla();
        }
    }
    // Si no hay fila seleccionada, no se hace nada (podrías mostrar un QMessageBox)
}

// =============================================================================
// BAJA (BORRAR): eliminar el usuario de la fila seleccionada
// =============================================================================
// Flujo:
//   1) Verificar que haya una fila seleccionada.
//   2) index.row() indica la posición en dataSave (misma que en treeWidget).
//   3) Quitar de dataSave con BorrarDataSave().
//   4) Refrescar la tabla.
// =============================================================================
void MainWindow::on_pushButton_Borrar_clicked()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    QModelIndex index = ui->treeWidget->currentIndex();

    if (item) {
        BorrarDataSave(index.row());
        ActualizarDataPlantilla();
    }
}

// --- Operaciones sobre dataSave (lista en memoria) ---------------------------

void MainWindow::AgregarDataSave(DataUser user)
{
    // push_back agrega al final del QVector
    dataSave.push_back(user);
}

void MainWindow::ModificarDataSave(DataUser user, int index)
{
    // replace sustituye el elemento en la posición index
    dataSave.replace(index, user);
}

DataUser MainWindow::LeerDataSave(int index)
{
    return dataSave.at(index);
}

void MainWindow::BorrarDataSave(int index)
{
    // removeAt elimina un elemento y corre los índices de los que siguen
    dataSave.removeAt(index);
}

// --- Sincronizar la vista (treeWidget) con dataSave ---------------------------

void MainWindow::ActualizarDataPlantilla(void)
{
    // Estrategia "redibujar todo": vaciar la tabla y volver a cargarla desde cero.
    // Es simple de entender para alumnos; en apps grandes a veces se actualiza
    // solo la fila que cambió para ser más eficiente.
    ui->treeWidget->clear();

    for (int i = 0; i < dataSave.size(); i++) {
        DataUser temp = dataSave.at(i);

        QStringList columnas;
        columnas.append(temp.getNombre());
        columnas.append(temp.getApellido());
        columnas.append(QString::number(temp.getEdad()));

        QTreeWidgetItem *tmpitem = new QTreeWidgetItem(columnas);
        ui->treeWidget->addTopLevelItem(tmpitem);
    }
}
