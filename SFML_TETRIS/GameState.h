#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "Global.h"
#include "State.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"



class GameState :
	public State
{
private:

	/*SFML*/
	sf::Music bgSound;   // BackGround sound

	sf::SoundBuffer fallB, movB, rotB, clearB, gameB, pinB, poutB; // fallB = Fall Buffer
	sf::Sound fallS, movS, rotS, clearS, gameM, pinS, poutS;       // FallS = Fall Sound

	sf::RectangleShape backGround, gridShapeGame, gridShapeNextpiece;

	sf::Texture block, epT, bT, backGroundTexture, sticker1T, sticker2T;     // ep Texture
	sf::Sprite s, epS, bS, sticker1S,sticker2S;							   // ep Sprite

	sf::Clock times, times2, times3, over, pause_, clear1, clear2;

	sf::Font fuente;
	sf::Text text, textGameOver;

	// normal c++
	std::vector<std::vector<int>> grid;

	std::vector<sf::Vector2f> objets;


	int current[4][4];

	int r, lef, _next, rig, dx, dy, dow, r1, c, dx2, dy2, fps, subScore, duplicateX, duplicateY, duplicateX1,
		duplicateY1, aling, tetris, tetris1, score, highScore, level, subScore1;

	unsigned points, nivel, pointGameOver, NivelGameOver;

	int song = rand() % 5;
	

	int Random = rand() % 3;
	int player = rand() % 10;

	bool scorer, tet, z, downs, wait, overGame, stop, fall, mov, rot, _clear, over_, gameOver_, _pause, enterNick;

	sf::String players[10] = {
		"Player 1", "Player 2", "Player 3", "Player 4", "Player 5", 
		"Player 6", "Player 7", "Player 8", "Player 9", "Player 10"
	};

	sf::String musics[5] =
	{
		"resources/music/backgroundmusic.ogg", "resources/music/backgroundmusic2.ogg", "resources/music/backgroundmusic3.ogg", 
		"resources/music/backgroundmusic4.ogg", "resources/music/backgroundmusic5.ogg"

	};

	std::string textconsole;

	sf::String rowClear = "Classic";


	sf::IntRect shapes[9] =
	{
		sf::IntRect(0, 0, 30, 30), sf::IntRect(30, 0, 30, 30), sf::IntRect(60, 0, 30, 30), sf::IntRect(90, 0, 30, 30), 
		sf::IntRect(120, 0, 30, 30), sf::IntRect(150, 0, 30, 30), sf::IntRect(180, 0, 30, 30), sf::IntRect(210, 0, 30, 30), sf::IntRect(240, 0, 30, 30)
	};

    // Estados
	PauseMenu* pmenu;
	GameOverMenu* pGameOverMenu;




	void initMusic();
	void initFonts();
	void initTexture();
	void initVariables();
	void initText();
	void initPauseMenu();
	void initGameOverMenu();
	void initKeybinds();
    
public:
 
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	// Accesors game
	void drawBlocks();
	void currentBlockSetter();
	void rotateBlocks();
	void checkRows();
	void checkPossible();
	void blocksAdder();
	void SavePlayer();



	// bool Accesors game
	bool checkCollision(int x, int y);
	bool gameOver();
	bool collision(int x, int y, int x1, int y1);
	bool clearRow(int x);



	// Funciones
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void updateGameOverMenuButttons();
	void updateText();


	// game
	void updateWorld(const float& dt);
	void updatePlayer(sf::RenderTarget* target = NULL);
	void updateEffects();

	void update(const float& dt); // actualizar despues
	void render(sf::RenderTarget* target = NULL);
};

#endif

