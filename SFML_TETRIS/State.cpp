
#include "State.h"

// funciones privadas || inicia las variables || constructor

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->paused = false;
	this->pausedGameOVer = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
}


// Destructor

State::~State()
{
}

// Ayuda para el cierre de ventanas
const bool& State::getQuit() const
{
	return  this->quit;
}

// Ayuda en el manejo de la entrada de las teclas

const bool State::getKeyTime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

// finalizar estado
void State::endState()
{
	this->quit = true;
}

// Pausar juego
void State::pauseState()
{
	this->paused = true;
}

// denter la pausa
void State::unpauseState()
{
	this->paused = false;
}

// Finaliza el juego
void State::GameOverState()
{
	this->pausedGameOVer = true;
}

// Reinicia el juego
void State::unGameOverState()
{
	this->pausedGameOVer = false;
}

// actualiza la posicion de mause en pantalla
void State::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

// actualiza el manejo de las teclas
void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;
}
