#include "userdialog.h"
#include "ui_userdialog.h"
#include <QMessageBox>

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

void UserDialog::accept()
{
    DataUser user;
    user.setNombre(ui->lineEdit_Nombre->text().trimmed());
    user.setApellido(ui->lineEdit_Apellido->text().trimmed());
    user.setEdad(ui->lineEdit_Edad->text().toInt());

    if (!SetData(user))
        return;

    QDialog::accept();
}

bool UserDialog::SetData(const DataUser &user, bool validar)
{
    if (validar) {
        if (user.getNombre().isEmpty() || user.getApellido().isEmpty()) {
            QMessageBox::warning(this, tr("Datos inválidos"),
                                 tr("El nombre y el apellido no pueden estar vacíos."));
            return false;
        }
        if (user.getEdad() < 0) {
            QMessageBox::warning(this, tr("Datos inválidos"),
                                 tr("La edad no puede ser negativa."));
            return false;
        }
    }

    dataUser = user;

    ui->lineEdit_Nombre->setText(dataUser.getNombre());
    ui->lineEdit_Apellido->setText(dataUser.getApellido());
    ui->lineEdit_Edad->setText(QString::number(dataUser.getEdad()));
    return true;
}

DataUser UserDialog::GetData()
{
    return dataUser;
}
