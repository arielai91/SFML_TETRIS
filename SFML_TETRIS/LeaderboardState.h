#pragma once

#include "State.h"
#include "Global.h"
#include "Button.h"


class LeaderboardState :
    public State
{
private:

    //struct registro
    //{
    //    std::string nick;

    //    float score;
    //};
    //std::vector<registro> playesss;


    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Font text;

    sf::Text txt_1;
    sf::Text txt_2;
    sf::Text txt_3;
    std::string player;
    int scores;


    std::map<std::string, Button*> buttons;




    void initVariables();
    void initBackground();
    void initFounts();
    void initText();
    void initKeybinds();
    void initButtons();

public:
    LeaderboardState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~LeaderboardState();

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void updateText();
    void renderButtons(sf::RenderTarget* target = NULL);
    void renderText(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);
};