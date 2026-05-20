# ABM Usuario — Ejercicio Qt (C++)

Aplicación de ejemplo para practicar un **ABM** (*Alta, Baja, Modificación*): gestionar una lista de usuarios en memoria y mostrarla en una tabla (`QTreeWidget`).

El objetivo didáctico principal es entender **cómo se pasan datos entre dos ventanas**: `MainWindow` (ventana principal) y `UserDialog` (formulario de carga/edición).

---

## Requisitos

- Qt 5 o Qt 6 con módulo **Widgets**
- Compilador con soporte **C++17**
- Qt Creator (recomendado) o `qmake` desde consola

### Compilar

1. Abrir `ABMUsuario.pro` en Qt Creator.
2. **Build → Run qmake** (si cambiaste el `.pro`).
3. **Build → Build Project**.

---

## Estructura del proyecto

| Archivo | Rol |
|---------|-----|
| `main.cpp` | Inicia la aplicación y muestra `MainWindow`. |
| `mainwindow.cpp/.h` | Ventana principal: tabla, botones ABM, lista `dataSave`. |
| `userdialog.cpp/.h` | Diálogo modal para cargar o editar un usuario. |
| `datauser.cpp/.h` | Clase de datos (`DataUser`): nombre, apellido, edad. |
| `mainwindow.ui` / `userdialog.ui` | Diseño visual de las ventanas. |

---

## Arquitectura en dos capas

```
┌─────────────────────────────────────────────────────────┐
│  MainWindow                                             │
│                                                         │
│   dataSave (QVector<DataUser>)  ←→  datos reales        │
│              │                                          │
│              │  ActualizarDataPlantilla()               │
│              ▼                                          │
│   treeWidget (QTreeWidget)      ←→  lo que ve el usuario│
└─────────────────────────────────────────────────────────┘
```

- **`dataSave`**: lista en memoria. Es la “fuente de verdad”.
- **`treeWidget`**: solo muestra lo que hay en `dataSave`. Después de cada alta, baja o modificación se llama a `ActualizarDataPlantilla()` para volver a dibujar la tabla.

`UserDialog` **no** guarda la lista completa: solo arma **un** usuario a la vez y se lo devuelve a `MainWindow`.

---

## Cómo se pasan datos entre MainWindow y UserDialog

No se comparten variables globales ni punteros a los `QLineEdit` de la otra ventana. El intercambio se hace con **dos métodos públicos** en `UserDialog` y un objeto intermedio **`DataUser`**.

### El “paquete” de datos: `DataUser`

`DataUser` es una clase simple (a veces se la llama **DTO** o modelo de datos). Agrupa los campos que queremos mover:

- `nombre` (`QString`)
- `apellido` (`QString`)
- `edad` (`int`)

Tanto `MainWindow` como `UserDialog` conocen `DataUser`. Así no hace falta pasar tres parámetros sueltos en cada dirección: se pasa **un solo objeto**.

### Entrada de datos al diálogo: `SetData(...)`

```cpp
void UserDialog::SetData(QString nombre, QString apellido, int edad);
```

**Qué hace:**

1. Guarda los valores en el miembro interno `dataUser` (setters).
2. Escribe esos valores en los `QLineEdit` de la pantalla (`setText`), para que el usuario los vea.

**Quién lo llama y cuándo:**

| Operación | ¿Se llama `SetData`? | Motivo |
|-----------|----------------------|--------|
| **CREAR** | No (antes de `exec`) | El diálogo abre vacío; el alumno escribe desde cero. |
| **MODIFICAR** | Sí, **antes** de `exec()` | `MainWindow` lee la fila seleccionada y precarga el formulario. |

Ejemplo en modificación (`mainwindow.cpp`):

```cpp
userDialog.SetData(item->text(0),      // columna NOMBRE
                   item->text(1),      // columna APELLIDO
                   item->text(2).toInt()); // columna EDAD
```

Los textos salen del `QTreeWidgetItem` de la fila seleccionada.

### Salida de datos del diálogo: `GetData()`

```cpp
DataUser UserDialog::GetData();
```

**Qué hace:** devuelve una copia del `dataUser` que quedó armado dentro del diálogo.

**Quién lo llama y cuándo:** `MainWindow`, **después** de que el usuario pulsa **Aceptar** y `exec()` devuelve `QDialog::Accepted`.

```cpp
if (userDialog.exec() == QDialog::Accepted) {
    DataUser user = userDialog.GetData();
    // usar user en AgregarDataSave o ModificarDataSave
}
```

### Qué pasa al pulsar Aceptar: `on_buttonBox_accepted`

Qt conecta automáticamente el slot `on_buttonBox_accepted` al botón **Aceptar** del `QDialogButtonBox` (convención `on_<widget>_<señal>`).

En ese slot, el diálogo **lee la pantalla** y vuelca todo en `dataUser`:

```cpp
void UserDialog::on_buttonBox_accepted()
{
    SetData(ui->lineEdit_Nombre->text(),
            ui->lineEdit_Apellido->text(),
            ui->lineEdit_Edad->text().toInt());
}
```

Por eso `GetData()` ya tiene los datos actualizados cuando `MainWindow` lo llama justo después de `exec()`.

### Diagrama del intercambio

**CREAR (MainWindow → UserDialog → MainWindow)**

```
MainWindow                          UserDialog
    │                                    │
    │  UserDialog dlg;                   │
    │  dlg.exec()  ──────────────────►  │  (campos vacíos)
    │                                    │  usuario escribe...
    │                                    │  Aceptar → on_buttonBox_accepted
    │                                    │           → SetData desde QLineEdit
    │  dlg.GetData() ◄──────────────────  │  devuelve DataUser
    │  AgregarDataSave(user)             │
    │  ActualizarDataPlantilla()         │
```

**MODIFICAR (ida y vuelta con precarga)**

```
MainWindow                          UserDialog
    │                                    │
    │  lee fila del treeWidget           │
    │  SetData(nombre, apellido, edad) ─►│  llena dataUser + QLineEdit
    │  exec()  ────────────────────────► │  usuario edita...
    │                                    │  Aceptar → actualiza dataUser
    │  GetData() ◄──────────────────────  │
    │  ModificarDataSave(user, índice)   │
```

### Resumen de la API de intercambio

| Método | Dirección | Momento |
|--------|-----------|---------|
| `SetData(...)` | MainWindow → UserDialog | Antes de `exec()`, solo en **modificar** (precarga). También lo usa el propio diálogo al aceptar. |
| `GetData()` | UserDialog → MainWindow | Después de `exec()`, si el resultado es `Accepted`. |
| `exec()` | — | Abre el diálogo **modal** (bloquea la ventana principal hasta cerrar). |

---

## Flujo ABM completo

### Alta (botón CREAR)

1. Crear `UserDialog` en el stack.
2. `exec()` → usuario completa y acepta.
3. `GetData()` → `DataUser`.
4. `AgregarDataSave(user)` → `dataSave.push_back(...)`.
5. `ActualizarDataPlantilla()` → redibuja `treeWidget`.

### Modificación (botón MODIFICAR)

1. Obtener `currentItem()` y `currentIndex()` del `treeWidget`.
2. Si hay fila: `SetData(...)` con los textos de las columnas.
3. `exec()` → usuario edita y acepta.
4. `GetData()` → `ModificarDataSave(user, index.row())`.
5. `ActualizarDataPlantilla()`.

El **`index.row()`** es la posición en `dataSave`. Debe coincidir con la fila de la tabla porque ambas listas se recorren en el mismo orden en `ActualizarDataPlantilla()`.

### Baja (botón BORRAR)

1. Fila seleccionada → `index.row()`.
2. `BorrarDataSave(index)` → `dataSave.removeAt(index)`.
3. `ActualizarDataPlantilla()`.

No se usa `UserDialog` en la baja: solo hace falta saber **qué índice** borrar.

---

## Por qué no pasar los QLineEdit directamente

En Qt es habitual **no** exponer widgets de una ventana a otra. En su lugar:

- Cada ventana maneja sus propios controles (`ui->lineEdit_...`).
- El intercambio se hace con **tipos de datos de negocio** (`DataUser`) y métodos claros (`SetData` / `GetData`).

Ventajas para aprender y para mantener el código:

- `MainWindow` no depende del diseño interno del formulario.
- Podés cambiar el `.ui` del diálogo sin romper la ventana principal.
- Un solo lugar valida o transforma datos (`SetData`).

---

## Convenciones Qt usadas en el ejercicio

- **Auto-conexión de slots**: funciones `on_<nombreWidget>_<señal>()` enlazadas al diseñador `.ui` sin `connect()` manual.
- **Diálogo modal**: `exec()` en lugar de `show()` cuando necesitás un resultado (Aceptar/Cancelar) antes de seguir.
- **Separación modelo / vista**: `DataUser` + `dataSave` vs `treeWidget`.

---

## Posibles extensiones (para practicar)

- Mostrar `QMessageBox` si se pulsa Modificar/Borrar sin fila seleccionada.
- Validar campos vacíos o edad negativa en `SetData`.
- Pasar un `DataUser` completo a `SetData(const DataUser &user)` en lugar de tres parámetros.
- Persistir `dataSave` en un archivo JSON o CSV al cerrar la aplicación.

---

## Archivos clave para estudiar el paso de parámetros

1. `userdialog.h` — declaración de `SetData` y `GetData`, miembro `dataUser`.
2. `userdialog.cpp` — implementación y slot `on_buttonBox_accepted`.
3. `mainwindow.cpp` — `on_pushButton_Crear_clicked` y `on_pushButton_Modificar_clicked`.
4. `datauser.h` — estructura del objeto que viaja entre ventanas.
