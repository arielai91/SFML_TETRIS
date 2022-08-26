#include "PauseMenu.h"

// Inicia la Pausa del juego

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));



	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 4.f,
		static_cast<float>(window.getSize().y) - 100.f
	));
	this->container.setFillColor(sf::Color(33, 47, 60, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(236, 240, 241, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSE");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 40.f
	);
}

// Elimina los botones
PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}
}

// Almacena los botones registrados
std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

// Verifica si el boton fue pulsado
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

// Agrega o dibuja los botones
void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 150.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new Button(
		x, y, width, height,
		&this->font, text,
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));
}

// Actualiza los eventos del manejo del boton
void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

// Dibuja el boton
void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto &i : this->buttons)
	{
		i.second->render(&target);
	}

	target.draw(this->menuText);
}
