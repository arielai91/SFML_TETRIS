#include "MainMenuState.h"


void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		));
	
	this->backgroundTexture.loadFromFile("Resources/Images/Menu.jpg");
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Pixellari.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
	if (!this->font2.loadFromFile("Fonts/VideoGameFont2.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initText()
{
	this->wordTitle.setFont(this->font2);
	this->wordTitle.setCharacterSize(120);
	this->wordTitle.setFillColor(sf::Color(255, 255, 51));
	this->wordTitle.setPosition(310, 60);
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(370.f, 330.f, 250.f, 100.f, 
		&this->font, "Comenzar partida",
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));

	this->buttons["LEADERBOARD_STATE"] = new Button(770.f, 330.f, 250.f, 100.f,
		&this->font, "Leaderboard",
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));

	this->buttons["CONTROL_STATE"] = new Button(370.f, 530.f, 250.f, 100.f,
		&this->font, "Controles",
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));

	this->buttons["ABOUT_STATE"] = new Button(770.f, 530.f, 250.f, 100.f,
		&this->font, "About",
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));

	this->buttons["EXIT_STATE"] = new Button(1125.f, 722.f, 250.f, 100.f, 
		&this->font, "Salir",
		sf::Color(142, 68, 173, 200), sf::Color(82, 190, 128, 255), sf::Color(192, 57, 43, 200));

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}
}

void MainMenuState::updateText()
{

	std::stringstream Testris;

	Testris << "A tetris B";

	this->wordTitle.setString(Testris.str());


}

void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons()
{
	// 
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// START GAME
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//// LeaderBoard

	if (this->buttons["LEADERBOARD_STATE"]->isPressed())
	{
		this->states->push(new LeaderboardState(this->window, this->supportedKeys, this->states));
	}
	
	// Control
	if (this->buttons["CONTROL_STATE"]->isPressed())
	{
		this->states->push(new ControlState(this->window, this->supportedKeys, this->states));
	}

	 //About
	if (this->buttons["ABOUT_STATE"]->isPressed())
	{
		this->states->push(new AboutState(this->window, this->supportedKeys, this->states));
	}

	// SALIR DEL JUEGO
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}


void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateText();
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::renderText(sf::RenderTarget* target)
{
	target->draw(this->wordTitle);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	
	this->renderButtons(target);
	this->renderText(target);


	//sf::Text mouseText;
	//mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mousePosView.x << " " << this->mousePosView.y;
	//mouseText.setString(ss.str());

	//target->draw(mouseText);

}

