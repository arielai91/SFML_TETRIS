#include "State.h"
#include "Global.h"
#include "Button.h"


class ControlState :
    public State
{
private:

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Font text;


    sf::Text txt_1; //mover a la izquierda
    sf::Text txt_2; //mover a la derecha
    sf::Text txt_3; //girar la pieza
    sf::Text txt_4; //bajar rapido
    sf::Text txt_5; //Controles

    sf::Texture txt_capa2; //letra w
    sf::Sprite spr_capa2;
    sf::Texture txt_capa3; //función de w
    sf::Sprite spr_capa3;

    sf::Texture txt_capa4; //letra a
    sf::Sprite spr_capa4;
    sf::Texture txt_capa5; //función de a
    sf::Sprite spr_capa5;

    sf::Texture txt_capa6; //letra s
    sf::Sprite spr_capa6;
    sf::Texture txt_capa7; //función de s
    sf::Sprite spr_capa7;

    sf::Texture txt_capa8; //letra d
    sf::Sprite spr_capa8;
    sf::Texture txt_capa9; //función de d
    sf::Sprite spr_capa9;





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
    ControlState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~ControlState();

    void updateInput(const float& dt);
    void updateText();
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = NULL);
    void renderText(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);

};