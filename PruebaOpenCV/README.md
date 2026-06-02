# PruebaOpenCV

Proyecto de ejemplo desarrollado en **Qt (Widgets) + OpenCV** para realizar pruebas básicas de procesamiento de imágenes, captura de video y reconocimiento de texto mediante redes neuronales.

## Características

El proyecto incluye tres ejemplos independientes:

### 1. Visualización de imagen y cámara

Permite:

* Cargar una imagen desde disco.
* Mostrarla en una ventana OpenCV.
* Abrir la cámara local.
* Mostrar video en tiempo real.

### 2. Detección de bordes (Canny)

Captura video desde una cámara y aplica el algoritmo de detección de bordes de Canny.

Permite visualizar en tiempo real:

* Contornos de objetos.
* Bordes de texto.
* Líneas y formas geométricas.

### 3. Detección y reconocimiento de texto (OCR)

Utiliza los modelos incluidos en OpenCV DNN:

* EAST Text Detector
* CRNN Text Recognizer

Funciones:

* Detecta regiones que contienen texto.
* Extrae cada región detectada.
* Corrige la perspectiva mediante transformación proyectiva.
* Reconoce el texto contenido en cada región.
* Superpone el resultado sobre la imagen de la cámara.

---

# Requisitos

## Linux

Probado sobre:

* Debian 13
* Qt 6.10.1
* OpenCV 4.10

Paquetes recomendados:

```bash
sudo apt update

sudo apt install \
    build-essential \
    qt6-base-dev \
    qt6-tools-dev \
    libopencv-dev
```

Verificar instalación:

```bash
pkg-config --modversion opencv4
```

---

# Estructura del proyecto

```text
PruebaOpenCV/
│
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
├── PruebaOpenCV.pro
│
├── autumn.jpeg
│
└── TextDetect/
    ├── frozen_east_text_detection.pb
    ├── CRNN_VGG_BiLSTM_CTC.onnx
    └── alphabet_36.txt
```

---

# Modelos utilizados

## EAST

Detector de regiones de texto:

```text
TextDetect/frozen_east_text_detection.pb
```

## CRNN

Reconocimiento OCR:

```text
TextDetect/CRNN_VGG_BiLSTM_CTC.onnx
```

## Vocabulario

```text
TextDetect/alphabet_36.txt
```

---

# Configuración importante

El proyecto utiliza una macro definida en el archivo `.pro`:

```pro
DEFINES += PROJECT_PATH=\\\"$$PWD\\\"
```

Esto permite localizar recursos utilizando la ruta donde se encuentra el proyecto fuente.

Ejemplo:

```cpp
QString imagePath =
    QDir(QString(PROJECT_PATH))
        .filePath("autumn.jpeg");
```

De esta forma no depende del directorio de ejecución generado por Qt Creator.

---

# Uso

## Botón "Image"

Funciones:

* Carga la imagen `autumn.jpeg`.
* Muestra la imagen.
* Abre la cámara local.
* Muestra video en tiempo real.

---

## Botón "Cam"

Funciones:

* Captura video desde la cámara.
* Ejecuta detección de bordes mediante Canny.
* Muestra el resultado procesado.

Algoritmo utilizado:

```cpp
Canny(cameraFrame,
      imagen_procesada,
      200,
      400);
```

---

## Botón "TextDetection"

Funciones:

* Captura video desde cámara local.
* Detecta regiones con texto.
* Aplica OCR sobre cada región.
* Dibuja el texto reconocido sobre la imagen.

También puede adaptarse fácilmente para cámaras IP utilizando:

```cpp
const std::string videoStreamAddress =
    "http://IP_CAM/stream";

VideoCapture cap(videoStreamAddress);
```

---

# Posibles mejoras

* Integrar visualización dentro de widgets Qt en lugar de usar `imshow()`.
* Agregar selección de cámara.
* Soporte para imágenes desde archivo.
* Exportación de resultados OCR.
* OCR multilenguaje.
* Captura y procesamiento en hilos separados.
* Empaquetado para Windows y Linux.

---

# Licencias

Los modelos incluidos pertenecen a sus respectivos autores y proyectos originales.

Revisar las licencias correspondientes antes de redistribuirlos en aplicaciones comerciales.

---

# Autor

Proyecto de experimentación con Qt y OpenCV orientado a:

* procesamiento digital de imágenes,
* visión artificial,
* OCR en tiempo real,
* integración Qt/OpenCV.

