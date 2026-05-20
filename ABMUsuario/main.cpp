#include "mainwindow.h"

#include <QApplication>

// Punto de entrada: crea la aplicación Qt y muestra la ventana principal del ABM
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec(); // Bucle de eventos (clics, teclado, etc.)
}
