#include "AboutState.h"

void AboutState::initVariables()
{
}

void AboutState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		));
	this->backgroundTexture.loadFromFile("Resources/Images/About2.jpg");
	this->background.setTexture(&this->backgroundTexture);
}

void AboutState::initPictures()
{
	cargar_graficos();
	spr_foto1.setPosition(1000, 125);
	spr_foto1.scale(2, 2);

	spr_foto2.setPosition(300, 125);
	spr_foto2.scale(1.4, 1.4);
}

void AboutState::initFounts()
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

void AboutState::initText()
{
	this->txt_1.setFont(this->font);
	this->txt_1.setCharacterSize(40);
	this->txt_1.setFillColor(sf::Color(255, 255, 51));
	this->txt_1.setPosition(100, 300);

	this->txt_2.setFont(this->font);
	this->txt_2.setCharacterSize(40);
	this->txt_2.setFillColor(sf::Color(255, 255, 51));
	this->txt_2.setPosition(800, 300);


	this->txt_3.setFont(this->text);
	this->txt_3.setCharacterSize(40);
	this->txt_3.setFillColor(sf::Color(255, 255, 51));
	this->txt_3.setPosition(400, 20);
}

void AboutState::cargar_graficos()
{
	txt_foto1.loadFromFile("Resources/Images/foto1.jpg");
	spr_foto1.setTexture(txt_foto1);

	txt_foto2.loadFromFile("Resources/Images/foto2.jpg");
	spr_foto2.setTexture(txt_foto2);
}

void AboutState::initKeybinds()
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

void AboutState::initButtons()
{
	this->buttons["VOLVER"] = new Button(100, 750, 250, 100,
		&this->font, "Regresar",
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));

}

AboutState::AboutState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initPictures();
	this->initFounts();
	this->initText();
	this->initKeybinds();
	this->initButtons();
}

AboutState::~AboutState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}

}

void AboutState::updateInput(const float& dt)
{
}

void AboutState::updateText()
{
	std::stringstream info;
	info << "Estudiante: Ariel Amagua�a \n\nEstudia en la Escuela Polit�cnica \nNacional \n\nCarrera: Ingeniero en Software\n\nariel.amaguana@epn.edu.ec ";
	this->txt_1.setString(info.str());

	std::stringstream info1;
	info1 << "Estudiante: Angel Anguaya \n\nEstudia en la Escuela Polit�cnica \nNacional \n\nCarrera: Ingeniero en Software\n\nangel.anguaya02@epn.edu.ec ";
	this->txt_2.setString(info1.str());

	std::stringstream info2;
	info2 << "D personas que colaboraron\n en la creacion del juego D";
	this->txt_3.setString(info2.str());
}

void AboutState::updateButtons()
{
	// 
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//REGRESAR AL MENU
	if (this->buttons["VOLVER"]->isPressed())
	{
		this->endState();
	}

}

void AboutState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateText();
	this->updateButtons();
}

void AboutState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void AboutState::renderText(sf::RenderTarget* target)
{
	target->draw(this->txt_1);
	target->draw(this->txt_2);
	target->draw(this->txt_3);
}

void AboutState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->spr_foto1);
	target->draw(this->spr_foto2);

	this->renderButtons(target);
	this->renderText(target);
}
