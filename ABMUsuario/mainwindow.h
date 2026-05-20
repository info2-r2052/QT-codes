#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datauser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*
 * Ventana principal del ABM (Alta, Baja, Modificación).
 *
 * Arquitectura en dos capas:
 *   1) dataSave (QVector)  -> memoria interna, lista real de usuarios.
 *   2) treeWidget          -> vista en pantalla; se redibuja desde dataSave.
 *
 * Patrón común: primero se cambia dataSave y luego ActualizarDataPlantilla()
 * para que la tabla muestre lo mismo que hay guardado en memoria.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Operaciones sobre la lista en memoria (no tocan la tabla directamente)
    void AgregarDataSave(DataUser user);
    DataUser LeerDataSave(int index);
    void BorrarDataSave(int index);
    void ModificarDataSave(DataUser user, int index);

    // Sincroniza treeWidget con el contenido actual de dataSave
    void ActualizarDataPlantilla(void);

private slots:
    // Slots conectados por nombre a los botones del .ui (convención on_<objeto>_<señal>)
    void on_pushButton_Crear_clicked();
    void on_pushButton_Modificar_clicked();
    void on_pushButton_Borrar_clicked();

private:
    Ui::MainWindow *ui;

    // Contenedor donde persisten los usuarios mientras la app está abierta
    QVector<DataUser> dataSave;
};
#endif // MAINWINDOW_H
