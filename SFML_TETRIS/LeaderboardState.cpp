#include "LeaderboardState.h"


void LeaderboardState::initVariables()
{
}

void LeaderboardState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		));
	this->backgroundTexture.loadFromFile("Resources/Images/lead.jpg");
	this->background.setTexture(&this->backgroundTexture);

}

void LeaderboardState::initFounts()
{
	if (!this->font.loadFromFile("Fonts/Pixellari.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
	if (!this->text.loadFromFile("Fonts/VideoGameFont2.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void LeaderboardState::initText()
{
	this->txt_1.setFont(this->text);
	this->txt_1.setCharacterSize(40);
	this->txt_1.setFillColor(sf::Color(0, 0, 0));
	this->txt_1.setPosition(400, 50);

	this->txt_2.setFont(this->text);
	this->txt_2.setCharacterSize(40);
	this->txt_2.setFillColor(sf::Color(0, 0, 0));
	this->txt_2.setPosition(650, 290);

	this->txt_3.setFont(this->text);
	this->txt_3.setCharacterSize(40);
	this->txt_3.setFillColor(sf::Color(0, 0, 0));
	this->txt_3.setPosition(500, 300);


}

void LeaderboardState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void LeaderboardState::initButtons()
{

	this->buttons["REGRESAR_2"] = new Button(100, 750, 250, 100,
		&this->font, "Regresar",
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));
}


LeaderboardState::LeaderboardState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFounts();
	this->initText();
	this->initKeybinds();
	this->initButtons();

}

LeaderboardState::~LeaderboardState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}

}
void LeaderboardState::updateInput(const float& dt)
{
}

void LeaderboardState::updateButtons()
{
	// 
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// REGRESAR AL MENU
	if (this->buttons["REGRESAR_2"]->isPressed())
	{
		this->endState();
	}

}

void LeaderboardState::updateText()
{
	std::stringstream tabla;
	tabla << "        L clasificacion L\n\n\nnum			nick			score\n\n 1\n\n 2\n\n 3\n\n 4\n\n 5";
	this->txt_1.setString(tabla.str());


}


void LeaderboardState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateText();
	this->updateButtons();

}

void LeaderboardState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void LeaderboardState::renderText(sf::RenderTarget* target)
{
	target->draw(this->txt_1);
	target->draw(this->txt_2);
	target->draw(this->txt_3);
}

void LeaderboardState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);
	this->renderText(target);
}
