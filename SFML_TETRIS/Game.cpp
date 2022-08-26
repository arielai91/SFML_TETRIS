#include "Game.h"



// Funciones privadas

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::InitWindow()
{

	std::ifstream ifs("Config/window.ini");
	this->videomodes = sf::VideoMode::getFullscreenModes();


	std::string title = "Tetris";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framrate_limit = 120;
	bool vertical_sync_enable = false;
	unsigned antialiasing_Level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framrate_limit;
		ifs >> vertical_sync_enable;
		ifs >> antialiasing_Level;
	}

	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_Level;

	if(this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

	this->window->setFramerateLimit(framrate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enable);


}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

}


void Game::InitStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}


// Construir | Destruir
Game::Game()
{
	this->InitWindow();
	this->initKeys();
	this->InitStates();
}


Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}


// Funciones publicas

void Game::endApplication()
{
	std::cout << "End application" << std::endl;
}

void Game::updateDT()
{
	/* actualiza la variable dt con el tiempo que lleva actualizar y renderizar un cuadro */

	this->dt = this->dtClock.restart().asSeconds();

}

void Game::updateSFMLEvents()
{
	// Evento de cierre de ventana
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}
void Game::update()
{
	// Actualiza los estados del videojuego

	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	// limpia la ventana

	this->window->clear(sf::Color::Black);

	// dibuja lo que tiene dentro de cada estado

	if (!this->states.empty())
		this->states.top()->render();

	// elimina lo que se encentra dentro de cada estado

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		
		this->update();
		this->render();
		this->updateDT();
	}
}

