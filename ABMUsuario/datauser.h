#ifndef DATAUSER_H
#define DATAUSER_H

#include <QDialog>

class DataUser
{
private:
    QString nombre;
    QString apellido;
    int edad;

public:
    DataUser();

    const QString &getNombre() const;
    void setNombre(const QString &newNombre);
    const QString &getApellido() const;
    void setApellido(const QString &newApellido);
    int getEdad() const;
    void setEdad(int newEdad);
};

#endif // DATAUSER_H
