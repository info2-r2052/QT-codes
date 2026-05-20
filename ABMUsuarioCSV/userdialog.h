#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "datauser.h"

namespace Ui {
class UserDialog;
}

/*
 * Diálogo reutilizable para ALTA y MODIFICACIÓN.
 *
 * - En CREAR: se abre vacío; el usuario completa los campos y Aceptar guarda en dataUser.
 * - En MODIFICAR: MainWindow llama SetData() antes de exec() para precargar los campos.
 *
 * GetData() devuelve el objeto listo para guardar en dataSave.
 */
class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = nullptr);
    ~UserDialog();

    // Carga datos en el modelo interno y en los QLineEdit.
    // Si validar es true, rechaza nombre/apellido vacíos o edad negativa.
    bool SetData(const DataUser &user, bool validar = true);

    // Devuelve lo que quedó guardado al aceptar el diálogo
    DataUser GetData();

protected:
    void accept() override;

private:
    Ui::UserDialog *ui;

    // Buffer: aquí se arma el usuario antes de devolverlo a MainWindow
    DataUser dataUser;
};

#endif // USERDIALOG_H
