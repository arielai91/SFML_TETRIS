#ifndef GAME_H
#define GAME_H

#include "Global.h"
#include "MainMenuState.h"


/* Maneja la entrada y salida de datos del videojuego */

class Game
{
private:
	// Variables SFML
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;


	// Variables c++

	float dt;
	bool fullscreen;
	std::vector<sf::VideoMode> videomodes;
	sf::ContextSettings windowSettings;
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;



	// Funciones privadas
	void initVariables();
	void InitWindow();
	void InitStates();
	void initKeys();

public:
	// Construir | Destruir
	Game();
	virtual ~Game();

	// Funciones publicas

	// termina la aplicacion
	void endApplication();

	// actualizar los eventos y el tiempo
	void updateDT();
	void updateSFMLEvents();
	void update();

	// renderizar los objetos
	void render();

	// recorre el juego
	void run();
};

#endif // !GAME_H
