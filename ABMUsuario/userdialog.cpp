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

void UserDialog::on_buttonBox_accepted()
{
    SetData(    ui->lineEdit_Nombre->text(),
                ui->lineEdit_Apellido->text(),
                ui->lineEdit_Edad->text().toInt());
}

void UserDialog::SetData(QString nombre, QString apellido, int edad){

    if(edad > 150)
        return;

    data.setNombre(nombre);
    data.setApellido(apellido);
    data.setEdad(edad);

    ui->lineEdit_Nombre->setText(data.getNombre());
    ui->lineEdit_Apellido->setText(data.getApellido());
    ui->lineEdit_Edad->setText(QString::number(data.getEdad()));
}

DataUser UserDialog::GetData(void){
    return data;
}



