cmake_minimum_required(VERSION 3.16)
project(SFML_Tetris VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)

# Source files
set(SOURCES
    SFML_TETRIS/Main.cpp
    SFML_TETRIS/Game.cpp
    SFML_TETRIS/State.cpp
    SFML_TETRIS/GameState.cpp
    SFML_TETRIS/MainMenuState.cpp
    SFML_TETRIS/LeaderboardState.cpp
    SFML_TETRIS/AboutState.cpp
    SFML_TETRIS/ControlState.cpp
    SFML_TETRIS/Button.cpp
    SFML_TETRIS/PauseMenu.cpp
    SFML_TETRIS/GameOverMenu.cpp
)

# Header files
set(HEADERS
    SFML_TETRIS/Global.h
    SFML_TETRIS/Game.h
    SFML_TETRIS/State.h
    SFML_TETRIS/GameState.h
    SFML_TETRIS/MainMenuState.h
    SFML_TETRIS/LeaderboardState.h
    SFML_TETRIS/AboutState.h
    SFML_TETRIS/ControlState.h
    SFML_TETRIS/Button.h
    SFML_TETRIS/PauseMenu.h
    SFML_TETRIS/GameOverMenu.h
)

# Create executable
add_executable(tetris ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(tetris PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)

# Copy resources to build directory
add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/SFML_TETRIS/Resources
        $<TARGET_FILE_DIR:tetris>/Resources
    COMMENT "Copying resources to build directory"
)

add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/SFML_TETRIS/Config
        $<TARGET_FILE_DIR:tetris>/Config
    COMMENT "Copying config files to build directory"
)

add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/SFML_TETRIS/Datos
        $<TARGET_FILE_DIR:tetris>/Datos
    COMMENT "Copying data files to build directory"
)

add_custom_command(TARGET tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/SFML_TETRIS/Fonts
        $<TARGET_FILE_DIR:tetris>/Fonts
    COMMENT "Copying fonts to build directory"
)

# Install target
install(TARGETS tetris DESTINATION bin)
install(DIRECTORY SFML_TETRIS/Resources DESTINATION share/tetris)
install(DIRECTORY SFML_TETRIS/Config DESTINATION share/tetris)
install(DIRECTORY SFML_TETRIS/Fonts DESTINATION share/tetris)
install(DIRECTORY SFML_TETRIS/Datos DESTINATION share/tetris)

# Compiler warnings
if(MSVC)
    target_compile_options(tetris PRIVATE /W4)
else()
    target_compile_options(tetris PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Enable debug symbols in debug build
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(tetris PRIVATE DEBUG_BUILD)
endif()
