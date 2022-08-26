#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	));
	this->background.setFillColor(sf::Color(20, 20, 20, 200));

	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 2.f,
		static_cast<float>(window.getSize().y) - 20.f
	));
	this->container.setFillColor(sf::Color(84, 110, 122, 150));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(236, 240, 241, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("GAME OVER");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 40.f
	);
}

GameOverMenu::~GameOverMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}
}

std::map<std::string, Button*>& GameOverMenu::getButtons()
{
	return this->buttons;
}

const bool GameOverMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void GameOverMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 150.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new Button(
		x, y, width, height,
		&this->font, text,
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));
}

void GameOverMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void GameOverMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& i : this->buttons)
	{
		i.second->render(&target);
	}

	target.draw(this->menuText);
}
