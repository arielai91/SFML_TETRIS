# Guía de Contribución - SFML Tetris

Gracias por tu interés en contribuir a este proyecto. Este documento proporciona directrices para mantener el código limpio, seguro y fácil de integrar en cualquier entorno.

---

## Índice

1. [Código de Conducta](#código-de-conducta)
2. [Cómo Contribuir](#cómo-contribuir)
3. [Estilo de Código](#estilo-de-código)
4. [Prácticas de Seguridad](#prácticas-de-seguridad)
5. [Proceso de Pull Request](#proceso-de-pull-request)
6. [Reportar Bugs](#reportar-bugs)
7. [Sugerir Mejoras](#sugerir-mejoras)

---

## Código de Conducta

### Nuestra Promesa

- Ser respetuoso con todos los contribuyentes
- Mantener un ambiente de aprendizaje positivo
- Aceptar críticas constructivas
- Enfocarse en lo mejor para la comunidad

---

## Cómo Contribuir

### 1. Fork del Repositorio

```bash
# Clonar tu fork
git clone https://github.com/TU_USUARIO/SFML_TETRIS.git
cd SFML_TETRIS
```

### 2. Crear una Rama

```bash
# Crear rama descriptiva
git checkout -b feature/nueva-funcionalidad
# o
git checkout -b fix/correccion-bug
```

### 3. Hacer Cambios

- Sigue las [guías de estilo](#estilo-de-código)
- Escribe código claro y autodocumentado
- Agrega comentarios donde sea necesario
- Valida todas las entradas de usuario

### 4. Probar Cambios

```bash
# Compilar en modo Debug
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# Ejecutar y verificar funcionamiento
./tetris
```

### 5. Commit

```bash
# Agregar cambios
git add .

# Commit con mensaje descriptivo
git commit -m "feat: Agregar sistema de puntuación mejorado"
```

#### Formato de Mensajes de Commit

Usamos el formato [Conventional Commits](https://www.conventionalcommits.org/):

- `feat:` Nueva funcionalidad
- `fix:` Corrección de bug
- `docs:` Solo cambios en documentación
- `style:` Formateo, punto y coma faltantes, etc.
- `refactor:` Refactorización de código
- `perf:` Mejoras de rendimiento
- `test:` Agregar tests
- `chore:` Mantenimiento

**Ejemplos:**
```
feat: Agregar soporte para niveles de dificultad
fix: Corregir bug de rotación de piezas en borde
docs: Actualizar instrucciones de instalación en README
refactor: Mejorar manejo de errores en Game.cpp
```

### 6. Push y Pull Request

```bash
# Push a tu fork
git push origin feature/nueva-funcionalidad
```

Luego crea un Pull Request desde GitHub.

---

## Estilo de Código

### Formato General

Usamos `.clang-format` para mantener consistencia. Antes de hacer commit:

```bash
# Formatear todos los archivos
find SFML_TETRIS -name "*.cpp" -o -name "*.h" | xargs clang-format -i
```

### Convenciones de Nombres

#### Variables
```cpp
// Snake_case para variables locales y miembros privados
int player_score;
bool is_game_over;

// this-> para miembros de clase
this->window = nullptr;
```

#### Funciones
```cpp
// PascalCase para funciones públicas
void InitWindow();
void UpdatePlayer();

// camelCase para funciones privadas/protegidas
void initVariables();
void updateSFMLEvents();
```

#### Clases
```cpp
// PascalCase para clases
class GameState;
class MainMenuState;
```

#### Constantes
```cpp
// UPPER_CASE para constantes
const int MAX_PLAYERS = 10;
const float GRAVITY_SPEED = 0.5f;
```

### Comentarios

```cpp
// Comentarios de una línea para explicaciones breves
int score = 0;  // Puntuación del jugador

/**
 * @brief Comentarios de función tipo Doxygen
 * @param dt Delta time en segundos
 * @return true si la operación fue exitosa
 */
bool update(const float& dt);
```

### Headers

#### Orden de Includes

```cpp
// 1. Header propio (si es .cpp)
#include "Game.h"

// 2. Headers del proyecto
#include "State.h"
#include "Global.h"

// 3. Headers de SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// 4. Headers de la biblioteca estándar
#include <iostream>
#include <vector>
#include <memory>
```

#### Header Guards

```cpp
#ifndef CLASS_NAME_H
#define CLASS_NAME_H

// Contenido del header

#endif // CLASS_NAME_H
```

### Punteros

```cpp
// Preferir nullptr sobre NULL
void* ptr = nullptr;

// Asterisco pegado al tipo (alineación izquierda)
int* pointer;
sf::RenderWindow* window;
```

---

## Prácticas de Seguridad

### ✅ HACER

#### 1. Validación de Entrada

```cpp
// ✅ BIEN: Validar entrada de archivos
std::ifstream file("config.ini");
if (file.is_open()) {
    int value;
    if (file >> value) {
        // Validar rango
        if (value >= MIN_VALUE && value <= MAX_VALUE) {
            this->setting = value;
        } else {
            std::cerr << "Warning: Value out of range\n";
            this->setting = DEFAULT_VALUE;
        }
    }
}
```

#### 2. Manejo de Errores

```cpp
// ✅ BIEN: Try-catch para operaciones críticas
try {
    this->window = new sf::RenderWindow(mode, title);
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    throw;
}
```

#### 3. Valores por Defecto

```cpp
// ✅ BIEN: Siempre tener valores por defecto
unsigned framerate = 120;  // Default seguro
if (config_file.is_open()) {
    config_file >> framerate;
    // Validar
    if (framerate == 0 || framerate > 300) {
        framerate = 120;
    }
}
```

#### 4. Inicialización Segura de Variables

```cpp
// ✅ BIEN: Inicializar en constructor o initVariables()
void GameState::initVariables() {
    std::random_device rd;
    std::mt19937 gen(rd());
    this->random_value = gen() % max_value;
}
```

### ❌ EVITAR

#### 1. rand() en Headers

```cpp
// ❌ MAL: No inicializar con rand() en headers
class Game {
    int random_val = rand() % 10;  // ¡NO HACER ESTO!
};

// ✅ BIEN: Inicializar en constructor
class Game {
    int random_val;  // Declarar aquí
    Game() {
        std::random_device rd;
        std::mt19937 gen(rd());
        random_val = gen() % 10;  // Inicializar aquí
    }
};
```

#### 2. Dependencias de Plataforma

```cpp
// ❌ MAL: Dependencias específicas de Windows
#include <Windows.h>
#include <winsock2.h>

// ✅ BIEN: Usar código multiplataforma o condicional
#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#endif
```

#### 3. Punteros Raw sin Validación

```cpp
// ❌ MAL: No validar punteros
this->window->close();  // ¿Y si window es nullptr?

// ✅ BIEN: Validar antes de usar
if (this->window != nullptr) {
    this->window->close();
}
```

#### 4. Sin Manejo de Errores

```cpp
// ❌ MAL: Asumir que todo funciona
std::ifstream file("data.txt");
int value;
file >> value;  // ¿Y si falla?

// ✅ BIEN: Validar operaciones
std::ifstream file("data.txt");
if (file.is_open()) {
    int value;
    if (file >> value) {
        // Usar value
    } else {
        std::cerr << "Error reading value\n";
    }
} else {
    std::cerr << "Error opening file\n";
}
```

---

## Proceso de Pull Request

### Checklist antes de PR

- [ ] El código compila sin warnings
- [ ] Funciona en modo Debug y Release
- [ ] Se probó en al menos un sistema operativo
- [ ] Sigue el estilo de código del proyecto
- [ ] Incluye comentarios donde es necesario
- [ ] Valida todas las entradas de usuario
- [ ] No rompe funcionalidad existente
- [ ] Actualiza documentación si es necesario

### Descripción del PR

```markdown
## Descripción
Breve descripción de los cambios

## Tipo de Cambio
- [ ] Bug fix
- [ ] Nueva funcionalidad
- [ ] Refactorización
- [ ] Mejora de documentación

## ¿Cómo se probó?
Describe las pruebas realizadas

## Checklist
- [ ] Mi código sigue el estilo del proyecto
- [ ] He comentado código complejo
- [ ] He actualizado la documentación
- [ ] No genera nuevos warnings
```

---

## Reportar Bugs

### Incluir en el Reporte

1. **Descripción clara** del bug
2. **Pasos para reproducir**:
   - Paso 1
   - Paso 2
   - Paso 3
3. **Comportamiento esperado**
4. **Comportamiento actual**
5. **Información del sistema**:
   - SO y versión
   - Compilador y versión
   - Versión de SFML
6. **Screenshots** (si aplica)
7. **Logs de error** (si hay)

### Ejemplo

```markdown
**Descripción:** El juego crashea al rotar pieza en el borde

**Pasos para reproducir:**
1. Iniciar juego nuevo
2. Mover pieza al borde derecho
3. Presionar flecha arriba para rotar
4. Crash

**Esperado:** La pieza debe rotar o no hacer nada si no cabe

**Actual:** Segmentation fault

**Sistema:**
- Ubuntu 22.04 LTS
- GCC 11.3.0
- SFML 2.5.1
```

---

## Sugerir Mejoras

### Template de Sugerencia

```markdown
**Problema a resolver:**
Describe el problema actual o limitación

**Solución propuesta:**
Describe tu idea para resolver el problema

**Alternativas consideradas:**
Otras soluciones que pensaste

**Beneficios:**
- Beneficio 1
- Beneficio 2

**Posibles desventajas:**
- Desventaja 1
```

---

## Recursos Adicionales

### Documentación

- [SFML Documentation](https://www.sfml-dev.org/documentation/)
- [C++ Reference](https://en.cppreference.com/)
- [CMake Documentation](https://cmake.org/documentation/)

### Herramientas

- [Clang-Format](https://clang.llvm.org/docs/ClangFormat.html)
- [Valgrind](https://valgrind.org/) - Detección de memory leaks
- [cppcheck](http://cppcheck.sourceforge.net/) - Análisis estático

---

## Contacto

Si tienes preguntas, puedes:
- Abrir un Issue en GitHub
- Contactar a los mantenedores

---

¡Gracias por contribuir! 🎮
