#pragma once

#include "Global.h"
#include "Button.h"

class GameOverMenu
{
private:
	// Variables SFML
	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;


	// Varibles C++
	std::string text;
	std::map<std::string, Button*> buttons;



public:
	GameOverMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~GameOverMenu();

	// Accesorio
	std::map<std::string, Button*>& getButtons();
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);

	// Funciones publicas
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

};

