#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "datauser.h"

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = nullptr);
    ~UserDialog();
    void SetData(QString nombre, QString apellido, int edad);
    DataUser GetData();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::UserDialog *ui;

    DataUser data;
};

#endif // USERDIALOG_H
