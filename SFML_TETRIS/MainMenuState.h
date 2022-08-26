#pragma once

#include "GameState.h"
#include "Button.h"
#include "AboutState.h"
#include "ControlState.h"
#include "LeaderboardState.h"

class MainMenuState :
    public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Font font2;
	sf::Text wordTitle;

	std::map<std::string, Button*> buttons;

	void initVariables();
	void initText();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:

	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	// Funciones
	void updateInput(const float& dt);
	void updateText();
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	void renderText(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};


