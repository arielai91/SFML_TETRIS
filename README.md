# Tetris en C++ con SFML

Este proyecto es una implementación del clásico juego de **Tetris**, desarrollado en **C++** utilizando la biblioteca **SFML**.
El objetivo principal es **aprender y profundizar en C++**, enfocándose especialmente en el paradigma de **Programación Orientada a Objetos (POO)**, así como en el uso de **SFML** para gráficos, entrada y sonido.

---

## Características

- ✅ **Multiplataforma**: Compatible con Windows, Linux y macOS
- ✅ **Código seguro**: Validación de entrada y manejo robusto de errores
- ✅ **Fácil integración**: Sistema de construcción CMake portable
- ✅ **Formateo consistente**: Configuración de clang-format incluida
- ✅ **Sin dependencias de plataforma**: No requiere APIs específicas de Windows

---

## Objetivos

- Aprender los fundamentos y buenas prácticas de programación en C++.
- Aplicar los conceptos de POO en un proyecto práctico.
- Utilizar la biblioteca SFML para crear aplicaciones gráficas interactivas.
- Desarrollar un juego completamente funcional desde cero.

---

## Requisitos

- **C++17** o superior
- **SFML 2.5.1** o superior
- **CMake 3.16** o superior (para construcción multiplataforma)
- Compilador compatible: GCC 7+, Clang 5+, MSVC 2017+, o Apple Clang 10+

---

## Instalación de Dependencias

### Windows

#### Opción 1: Usando vcpkg (Recomendado)
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
.\vcpkg install sfml:x64-windows
```

#### Opción 2: Manual
1. Descargar SFML desde [sfml-dev.org](https://www.sfml-dev.org/download.php)
2. Extraer en una ubicación conocida (ej: `C:\Libraries\SFML-2.5.1`)
3. Agregar la ruta al PATH del sistema

### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev
```

### Linux (Fedora)
```bash
sudo dnf install cmake gcc-c++ SFML-devel
```

### macOS
```bash
brew install cmake sfml
```

---

## Compilación

### Usando CMake (Recomendado - Multiplataforma)

```bash
# Crear directorio de construcción
mkdir build
cd build

# Configurar proyecto
cmake ..

# Compilar
cmake --build .

# Ejecutar
./tetris          # Linux/macOS
tetris.exe        # Windows
```

#### Opciones de CMake

```bash
# Compilación en modo Release (optimizado)
cmake -DCMAKE_BUILD_TYPE=Release ..

# Especificar ubicación de SFML (si no está en PATH)
cmake -DSFML_DIR=/ruta/a/SFML/lib/cmake/SFML ..

# Compilación en paralelo (más rápido)
cmake --build . -j 4
```

### Visual Studio 2022 (Windows)

#### Método 1: Con CMake
1. Abrir Visual Studio 2022
2. `File > Open > CMake...`
3. Seleccionar `CMakeLists.txt`
4. Presionar F5 para compilar y ejecutar

#### Método 2: Con archivos .sln (Tradicional)

##### Configuración para modo **Debug** (x64)

**VC++ Directories**
- `Include Directories`: Ruta donde se encuentran los archivos de cabecera de SFML
- `Library Directories`: Ruta donde se encuentran las bibliotecas (.lib) de SFML

**Linker > Input > Additional Dependencies**
```
opengl32.lib
sfml-system-d.lib
sfml-window-d.lib
sfml-graphics-d.lib
sfml-main-d.lib
sfml-audio-d.lib
sfml-network-d.lib
```

##### Configuración para modo **Release** (x64)

**Linker > Input > Additional Dependencies**
```
opengl32.lib
sfml-system.lib
sfml-window.lib
sfml-graphics.lib
sfml-main.lib
sfml-audio.lib
sfml-network.lib
```

---

## Estructura del Proyecto

```
SFML_TETRIS/
├── CMakeLists.txt           # Sistema de construcción CMake
├── .clang-format            # Configuración de formato de código
├── README.md                # Este archivo
├── CONTRIBUTING.md          # Guía de contribución
├── SFML_TETRIS/
│   ├── Main.cpp             # Punto de entrada
│   ├── Game.cpp/.h          # Clase principal del juego
│   ├── GameState.cpp/.h     # Estado del juego
│   ├── State.cpp/.h         # Clase base de estados
│   ├── Global.h             # Headers globales
│   ├── Config/              # Archivos de configuración
│   ├── Resources/           # Recursos (música, texturas)
│   ├── Fonts/               # Fuentes tipográficas
│   └── Datos/               # Datos del juego
```

---

## Controles

- **←/→**: Mover pieza izquierda/derecha
- **↑**: Rotar pieza
- **↓**: Acelerar caída
- **Espacio**: Caída instantánea
- **P**: Pausar el juego
- **ESC**: Salir del juego

---

## Configuración

Los archivos de configuración se encuentran en `SFML_TETRIS/Config/`:

- `window.ini`: Configuración de la ventana (resolución, fullscreen, framerate)
- `supported_keys.ini`: Mapeo de teclas
- `gamestates_keybinds.ini`: Controles del juego

### Ejemplo de `window.ini`:
```
Tetris
1280 720
0
120
0
0
```
(Título, Ancho, Alto, Fullscreen, FPS Límite, VSync, Antialiasing)

---

## Prácticas de Seguridad Implementadas

1. ✅ **Validación de entrada**: Todos los archivos de configuración son validados
2. ✅ **Manejo de errores**: Try-catch para operaciones críticas
3. ✅ **Sin buffer overflows**: Uso de contenedores STL seguros
4. ✅ **Sin dependencias inseguras**: Removida la dependencia de `Windows.h`
5. ✅ **Generador aleatorio seguro**: Uso de `<random>` en lugar de `rand()`
6. ✅ **Valores por defecto**: El juego funciona sin archivos de configuración
7. ✅ **Smart pointers ready**: Código preparado para migración a smart pointers

---

## Solución de Problemas

### El juego no encuentra los recursos
Asegúrate de que los directorios `Resources/`, `Config/`, `Fonts/`, y `Datos/` estén en el mismo directorio que el ejecutable.

### Error al compilar con CMake
```bash
# Limpiar caché y reconfigurar
rm -rf build/
mkdir build && cd build
cmake ..
```

### SFML no encontrado
```bash
# Especificar ruta de SFML
cmake -DSFML_DIR=/ruta/completa/a/SFML/lib/cmake/SFML ..
```

---

## Contribuir

Por favor lee [CONTRIBUTING.md](CONTRIBUTING.md) para detalles sobre el proceso de contribución y el código de conducta.

---

## Licencia

Este proyecto es de código abierto y está disponible para fines educativos.

---

## Créditos

Desarrollado con fines educativos para reforzar el aprendizaje de C++ y el uso de SFML.

## Agradecimientos

- [SFML Team](https://www.sfml-dev.org/) por la excelente biblioteca multimedia
- La comunidad de C++ por las mejores prácticas y recursos educativos
