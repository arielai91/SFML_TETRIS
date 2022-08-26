#include "ControlState.h"


void ControlState::initVariables()
{

}

void ControlState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		));
	this->backgroundTexture.loadFromFile("Resources/Images/Controls4.jpg");
	this->background.setTexture(&this->backgroundTexture);

}

void ControlState::initPictures()
{
	cargar_graficos();
	spr_capa2.setPosition(900, 50); //letra w
	spr_capa2.scale(0.5, 0.5);
	spr_capa3.setPosition(1000, 125); //funci�n de w
	spr_capa3.scale(0.5, 0.5);

	spr_capa4.setPosition(200, 50); //letra a
	spr_capa4.scale(0.5, 0.5);
	spr_capa5.setPosition(100, 150); //funci�n de a
	spr_capa5.scale(1, 1);

	spr_capa6.setPosition(900, 400); //letra s
	spr_capa6.scale(0.5, 0.5);
	spr_capa7.setPosition(1000, 500); //funci�n de s
	spr_capa7.scale(0.5, 0.5);

	spr_capa8.setPosition(200, 400); //letra d
	spr_capa8.scale(0.5, 0.5);
	spr_capa9.setPosition(100, 500); //funci�n de d
	spr_capa9.scale(1, 1);


}


void ControlState::initFounts()
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

void ControlState::initText()
{
	this->txt_1.setFont(this->font);
	this->txt_1.setCharacterSize(40);
	this->txt_1.setFillColor(sf::Color(255, 255, 51));
	this->txt_1.setPosition(310, 60);

	this->txt_2.setFont(this->font);
	this->txt_2.setCharacterSize(40);
	this->txt_2.setFillColor(sf::Color(255, 255, 51));
	this->txt_2.setPosition(310, 400);

	this->txt_3.setFont(this->font);
	this->txt_3.setCharacterSize(40);
	this->txt_3.setFillColor(sf::Color(255, 255, 51));
	this->txt_3.setPosition(1000, 60);

	this->txt_4.setFont(this->font);
	this->txt_4.setCharacterSize(40);
	this->txt_4.setFillColor(sf::Color(255, 255, 51));
	this->txt_4.setPosition(1000, 400);

	this->txt_5.setFont(this->text);
	this->txt_5.setCharacterSize(40);
	this->txt_5.setFillColor(sf::Color(255, 255, 51));
	this->txt_5.setPosition(500, 10);

}

void ControlState::cargar_graficos()
{
	txt_capa2.loadFromFile("Resources/Images/Capa2.png"); //imagen de w
	spr_capa2.setTexture(txt_capa2);
	txt_capa3.loadFromFile("Resources/Images/cambio.png"); //imagen de la funci�n de w
	spr_capa3.setTexture(txt_capa3);

	txt_capa4.loadFromFile("Resources/Images/Capa3.png"); //imagen de a
	spr_capa4.setTexture(txt_capa4);
	txt_capa5.loadFromFile("Resources/Images/izquierda.png"); //imagen de la funci�n de a
	spr_capa5.setTexture(txt_capa5);

	txt_capa6.loadFromFile("Resources/Images/Capa4.png"); //imagen de s
	spr_capa6.setTexture(txt_capa6);
	txt_capa7.loadFromFile("Resources/Images/caida.png"); //imagen de la funci�n de s
	spr_capa7.setTexture(txt_capa7);

	txt_capa8.loadFromFile("Resources/Images/Capa5.png"); //imagen de d
	spr_capa8.setTexture(txt_capa8);
	txt_capa9.loadFromFile("Resources/Images/derecha.png"); //imagen de la funci�n de d
	spr_capa9.setTexture(txt_capa9);


}

void ControlState::initKeybinds()
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

void ControlState::initButtons()
{
	this->buttons["REGRESAR"] = new Button(100, 750, 250, 100,
		&this->font, "Regresar",
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));
}


ControlState::ControlState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
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

ControlState::~ControlState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}

}

void ControlState::updateInput(const float& dt)
{
}

void ControlState::updateText()
{
	std::stringstream izquierda;
	izquierda << "Mover a la izquierda";
	this->txt_1.setString(izquierda.str());

	std::stringstream derecha;
	derecha << "Mover a la derecha";
	this->txt_2.setString(derecha.str());

	std::stringstream girar;
	girar << "Girar la pieza";
	this->txt_3.setString(girar.str());

	std::stringstream bajar;
	bajar << "Ca�da rapida";
	this->txt_4.setString(bajar.str());

	std::stringstream controls;
	controls << "D controles D";
	this->txt_5.setString(controls.str());
}

void ControlState::updateButtons()
{
	// 
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// REGRESAR AL MENU
	if (this->buttons["REGRESAR"]->isPressed())
	{
		this->endState();
	}

}

void ControlState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateText();
	this->updateButtons();
}

void ControlState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void ControlState::renderText(sf::RenderTarget* target)
{
	target->draw(this->txt_1);
	target->draw(this->txt_2);
	target->draw(this->txt_3);
	target->draw(this->txt_4);
	target->draw(this->txt_5);

}

void ControlState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->spr_capa2);
	target->draw(this->spr_capa3);
	target->draw(this->spr_capa4);
	target->draw(this->spr_capa5);
	target->draw(this->spr_capa6);
	target->draw(this->spr_capa7);
	target->draw(this->spr_capa8);
	target->draw(this->spr_capa9);

	this->renderButtons(target);
	this->renderText(target);
}
