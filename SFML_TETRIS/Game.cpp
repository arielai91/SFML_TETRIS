#include "Game.h"

// Funciones privadas

void Game::initVariables()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::InitWindow()
{
	// Default values in case config file is missing or invalid
	std::string title = "Tetris";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enable = false;
	unsigned antialiasing_level = 0;

	// Try to load configuration from file
	try {
		std::ifstream ifs("Config/window.ini");

		if (ifs.is_open())
		{
			std::getline(ifs, title);

			// Validate and read window dimensions
			if (!(ifs >> window_bounds.width >> window_bounds.height)) {
				std::cerr << "Warning: Invalid window dimensions in config file. Using defaults.\n";
				window_bounds = sf::VideoMode::getDesktopMode();
				ifs.clear();
			}

			// Validate window dimensions
			if (window_bounds.width < 640 || window_bounds.height < 480) {
				std::cerr << "Warning: Window dimensions too small. Using desktop mode.\n";
				window_bounds = sf::VideoMode::getDesktopMode();
			}

			// Read other settings with validation
			if (!(ifs >> fullscreen)) {
				fullscreen = false;
				ifs.clear();
			}

			if (!(ifs >> framerate_limit) || framerate_limit == 0 || framerate_limit > 300) {
				framerate_limit = 120;
				ifs.clear();
			}

			if (!(ifs >> vertical_sync_enable)) {
				vertical_sync_enable = false;
				ifs.clear();
			}

			if (!(ifs >> antialiasing_level) || antialiasing_level > 16) {
				antialiasing_level = 0;
				ifs.clear();
			}

			ifs.close();
		}
		else
		{
			std::cerr << "Warning: Could not open Config/window.ini. Using default settings.\n";
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error reading window config: " << e.what() << "\nUsing default settings.\n";
	}

	this->videomodes = sf::VideoMode::getFullscreenModes();
	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	// Create window with validated settings
	try {
		if (this->fullscreen) {
			this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
		}
		else {
			this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
		}

		this->window->setFramerateLimit(framerate_limit);
		this->window->setVerticalSyncEnabled(vertical_sync_enable);
	}
	catch (const std::exception& e) {
		std::cerr << "Fatal error creating window: " << e.what() << std::endl;
		throw;
	}
}

void Game::initKeys()
{
	try {
		std::ifstream ifs("Config/supported_keys.ini");

		if (ifs.is_open())
		{
			std::string key = "";
			int key_value = 0;

			while (ifs >> key >> key_value)
			{
				// Validate key value is within valid range
				if (key_value >= 0 && key_value < sf::Keyboard::KeyCount) {
					this->supportedKeys[key] = key_value;
				}
				else {
					std::cerr << "Warning: Invalid key value for '" << key << "': " << key_value << std::endl;
				}
			}

			ifs.close();

			if (this->supportedKeys.empty()) {
				std::cerr << "Warning: No valid keys loaded from config file.\n";
			}
		}
		else
		{
			std::cerr << "Warning: Could not open Config/supported_keys.ini\n";
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error loading key bindings: " << e.what() << std::endl;
	}
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

