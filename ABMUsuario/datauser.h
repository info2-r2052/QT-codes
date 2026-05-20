#ifndef DATAUSER_H
#define DATAUSER_H

#include <QString>

/*
 * Modelo de un usuario (DTO / clase de datos).
 * No sabe nada de ventanas ni de la tabla: solo guarda nombre, apellido y edad.
 * MainWindow y UserDialog usan esta clase para pasar información entre sí.
 */
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
