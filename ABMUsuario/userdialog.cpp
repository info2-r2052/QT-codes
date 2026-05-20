#include "userdialog.h"
#include "ui_userdialog.h"
#include "datauser.h"

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
}

UserDialog::~UserDialog()
{
    delete ui;
}

// Al pulsar Aceptar, copiamos lo escrito en los controles hacia dataUser
void UserDialog::on_buttonBox_accepted()
{
    SetData(ui->lineEdit_Nombre->text(),
            ui->lineEdit_Apellido->text(),
            ui->lineEdit_Edad->text().toInt());
}

void UserDialog::SetData(QString nombre, QString apellido, int edad)
{
    // Validación simple de ejemplo (en un proyecto real podrías mostrar un mensaje)
    if (edad > 150)
        return;

    dataUser.setNombre(nombre);
    dataUser.setApellido(apellido);
    dataUser.setEdad(edad);

    // Actualizar los campos visibles (útil en MODIFICAR para ver lo que se cargó)
    ui->lineEdit_Nombre->setText(dataUser.getNombre());
    ui->lineEdit_Apellido->setText(dataUser.getApellido());
    ui->lineEdit_Edad->setText(QString::number(dataUser.getEdad()));
}

DataUser UserDialog::GetData(void)
{
    return dataUser;
}
