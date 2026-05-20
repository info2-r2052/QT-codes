#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userdialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Cambiá esta ruta para guardar el CSV en otro lugar
    rutaCsv = QDir(QCoreApplication::applicationDirPath())
                  .filePath(QStringLiteral("usuarios.csv"));

    CargarCSV();
    ActualizarDataPlantilla();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Crear_clicked()
{
    UserDialog userDialog;

    if (userDialog.exec() == QDialog::Accepted) {
        DataUser user = userDialog.GetData();

        AgregarDataSave(user);
        ActualizarDataPlantilla();
        GuardarCSV();
    }
}

void MainWindow::on_pushButton_Modificar_clicked()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    QModelIndex index = ui->treeWidget->currentIndex();

    if (!item) {
        QMessageBox::information(this, tr("Sin selección"),
                                 tr("Seleccione una fila para modificar."));
        return;
    }

    UserDialog userDialog;
    userDialog.SetData(LeerDataSave(index.row()), false);

    if (userDialog.exec() == QDialog::Accepted) {
        DataUser user = userDialog.GetData();

        ModificarDataSave(user, index.row());
        ActualizarDataPlantilla();
        GuardarCSV();
    }
}

void MainWindow::on_pushButton_Borrar_clicked()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    QModelIndex index = ui->treeWidget->currentIndex();

    if (!item) {
        QMessageBox::information(this, tr("Sin selección"),
                                 tr("Seleccione una fila para borrar."));
        return;
    }

    const int fila = index.row();
    const DataUser user = LeerDataSave(fila);
    const auto respuesta = QMessageBox::question(
        this,
        tr("Confirmar borrado"),
        tr("¿Desea borrar a %1 %2?").arg(user.getNombre(), user.getApellido()),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No);

    if (respuesta != QMessageBox::Yes)
        return;

    BorrarDataSave(fila);
    ActualizarDataPlantilla();
    GuardarCSV();
}

void MainWindow::AgregarDataSave(DataUser user)
{
    dataSave.push_back(user);
}

void MainWindow::ModificarDataSave(DataUser user, int index)
{
    dataSave.replace(index, user);
}

DataUser MainWindow::LeerDataSave(int index)
{
    return dataSave.at(index);
}

void MainWindow::BorrarDataSave(int index)
{
    dataSave.removeAt(index);
}

void MainWindow::ActualizarDataPlantilla(void)
{
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

void MainWindow::GuardarCSV()
{
    QFile file(rutaCsv);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const DataUser &user : dataSave) {
        out << user.getNombre() << ','
            << user.getApellido() << ','
            << user.getEdad() << '\n';
    }
}

void MainWindow::CargarCSV()
{
    QFile file(rutaCsv);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    dataSave.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        const QString linea = in.readLine().trimmed();
        if (linea.isEmpty())
            continue;

        const QStringList campos = linea.split(QLatin1Char(','));
        if (campos.size() < 3)
            continue;

        DataUser user;
        user.setNombre(campos.at(0));
        user.setApellido(campos.at(1));
        user.setEdad(campos.at(2).toInt());
        dataSave.append(user);
    }
}
