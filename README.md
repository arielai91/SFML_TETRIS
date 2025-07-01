# Tetris en C++ con SFML

Este proyecto es una implementaci�n del cl�sico juego de **Tetris**, desarrollado en **C++** utilizando la biblioteca **SFML**.  
El objetivo principal es **aprender y profundizar en C++**, enfoc�ndose especialmente en el paradigma de **Programaci�n Orientada a Objetos (POO)**, as� como en el uso de **SFML** para gr�ficos, entrada y sonido.

---

## Objetivos

- Aprender los fundamentos y buenas pr�cticas de programaci�n en C++.
- Aplicar los conceptos de POO en un proyecto pr�ctico.
- Utilizar la biblioteca SFML para crear aplicaciones gr�ficas interactivas.
- Desarrollar un juego completamente funcional desde cero.

---

## Requisitos

- **C++11** o superior  
- **SFML 2.5.1** o superior  
- **Visual Studio 2022** (u otro IDE compatible)

---

## Compilaci�n (Visual Studio 2022)

### Configuraci�n para modo **Debug** (x64)

**VC++ Directories**  
- `Include Directories`: Ruta donde se encuentran los archivos de cabecera de SFML  
- `Library Directories`: Ruta donde se encuentran las bibliotecas (.lib) de SFML  

**Linker > Input > Additional Dependencies**  
Agregar las siguientes librer�as:

opengl32.lib
sfml-system-d.lib
sfml-window-d.lib
sfml-graphics-d.lib
sfml-main-d.lib
sfml-audio-d.lib
sfml-network-d.lib

---

### Configuraci�n para modo **Release** (x64)

**Linker > Input > Additional Dependencies**  
Agregar las siguientes librer�as:

opengl32.lib
sfml-system.lib
sfml-window.lib
sfml-graphics.lib
sfml-main.lib
sfml-audio.lib
sfml-network.lib

---

## Controles

(Agregar aqu� los controles del juego si ya los tienes definidos. Ejemplo:)  
- Flecha izquierda/derecha: Mover pieza  
- Flecha arriba: Rotar pieza  
- Flecha abajo: Acelerar ca�da  
- Barra espaciadora: Ca�da instant�nea  
- P: Pausar el juego  

---

## Estructura del Proyecto

(Se recomienda incluir si tienes carpetas espec�ficas como `src/`, `include/`, `resource/`, etc.)

---

## Cr�ditos

Desarrollado con fines educativos para reforzar el aprendizaje de C++ y el uso de SFML.

---

## Licencia