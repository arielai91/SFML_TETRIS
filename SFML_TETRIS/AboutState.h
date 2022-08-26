#pragma once

#include "State.h"
#include "Global.h"
#include "Button.h"

class AboutState :
    public State
{
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Font text;

    sf::Text txt_1;
    sf::Text txt_2;
    sf::Text txt_3;

    sf::Texture txt_foto1;
    sf::Sprite spr_foto1;

    sf::Texture txt_foto2;
    sf::Sprite spr_foto2;

    std::map<std::string, Button*> buttons;

    void initVariables();
    void initBackground();
    void initPictures();
    void initFounts();
    void initText();
    void cargar_graficos();

    void initKeybinds();

    void initButtons();

public:
    AboutState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~AboutState();


    void updateInput(const float& dt);
    void updateText();
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = NULL);
    void renderText(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);
};

