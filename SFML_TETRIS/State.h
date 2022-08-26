#ifndef STATE_H
#define STATE_H

#include "Global.h"

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	bool pausedGameOVer;
	float keytime;
	float keytimeMax;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	std::vector<sf::Texture> textures;
	
	// Funcion privada
	virtual void initKeybinds() = 0;

public:

	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	// accesorios 
	const bool& getQuit() const;
	const bool getKeyTime();

	// Finaliza o comienza un estado dentro del juego
	void endState();
	void pauseState();
	void unpauseState();
	void GameOverState();
	void unGameOverState();

	/* 
		Funciones privadas que ayudan en el manejo de los estados
		
		updateMousePosition(), Ayuda en el manejo de la posicion del mouse.
		updateKeyTime(), Ayuda a no sobrepasar un limite de pulsaciones en el raton o teclado.
		updateInput(), Ayuda en la actualizacion de eventos que se realizan por el teclado o el mouse.
		update(), Ayuda a manejar todas las actualizaciones.
		render(), Ayuda a dibujar en pantalla.
	*/

	virtual void updateMousePosition();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;

	
};

#endif // !STATE_H
