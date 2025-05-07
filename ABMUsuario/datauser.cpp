#include "datauser.h"

const QString &DataUser::getNombre() const
{
    return nombre;
}

void DataUser::setNombre(const QString &newNombre)
{
    nombre = newNombre;
}

const QString &DataUser::getApellido() const
{
    return apellido;
}

void DataUser::setApellido(const QString &newApellido)
{
    apellido = newApellido;
}

int DataUser::getEdad() const
{
    return edad;
}

void DataUser::setEdad(int newEdad)
{
    edad = newEdad;
}

DataUser::DataUser()
{

}
