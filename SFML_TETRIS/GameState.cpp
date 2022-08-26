#include "GameState.h"

int blocks[7][4][4] =
{
	0, 0, 0, 0,//I shape
	1, 1, 1, 1,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 0, 0, 0,//J shape
	0, 1, 0, 0,
	0, 1, 1, 1,
	0, 0, 0, 0,

	0, 0, 0, 0,//L shape
	0, 0, 0, 1,
	0, 1, 1, 1,
	0, 0, 0, 0,

	0, 0, 0, 0,//O shape
	0, 1, 1, 0,
	0, 1, 1, 0,
	0, 0, 0, 0,

	0, 0, 0, 0,//S shape
	0, 0, 1, 1,
	0, 1, 1, 0,
	0, 0, 0, 0,

	0, 0, 0, 0,//Z shape
	0, 1, 1, 0,
	0, 0, 1, 1,
	0, 0, 0, 0,

	0, 0, 0, 0,//T shape
	0, 0, 1, 0,
	0, 1, 1, 1,
	0, 0, 0, 0,
};


void GameState::initVariables()
{
	// int
	this->r = 0;
	this->lef = 0;
	this->_next = rand() % 7;
	this->rig = 0;
	this->dx = 90;
	this->dy = -180;
	this->dow = 0;
	this->r1 = 0;
	this->c = 0;
	this->fps = 40;
	this->subScore = 0;
	this->aling = 0;
	this->tetris = 0;
	this->tetris1 = 0;
	this->score = 0;
	this->highScore = 0;
	this->level = 0;
	this->subScore = 0;
	
	// bool
	this->scorer = 0; //false
	this->tet = 0;
	this->z = 0;
	this->downs = 0;
	this->wait = 0;
	this->overGame = 0;
	this->stop = 0;
	this->fall = 0;
	this->mov = 0;
	this->rot = 0;
	this->_clear = 0;
	this->over_ = 0;
	this->gameOver_ = 0;
	this->_pause = 0;
	this->enterNick = 0;

	for (int i = 0; i < 23; i++)
	{
		grid.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	}
}

void GameState::initText()
{
	this->text.setFont(this->fuente);
	this->text.setCharacterSize(40);
	this->text.setFillColor(sf::Color(255, 255, 51));
	this->text.setPosition(450, 100);

	this->textGameOver.setFont(this->fuente);
	this->textGameOver.setCharacterSize(40);
	this->textGameOver.setFillColor(sf::Color(76, 175, 80));
	this->textGameOver.setPosition(450, 258);


}

void GameState::initMusic()
{
	// backGround song

	if (!this->bgSound.openFromFile(musics[song]))
	{
		std::cout << "error::mainmenustate::could not load musics";
	}
	this->bgSound.setVolume(50.0f);
	this->bgSound.play();

	// effects

	this->fallB.loadFromFile("Resources/Effects/falling.wav");
	this->fallS.setBuffer(fallB);
	this->fallS.setVolume(20.f);

	this->movB.loadFromFile("Resources/Effects/move.wav");
	this->movS.setBuffer(movB);
	this->movS.setVolume(20.f);


	this->rotB.loadFromFile("Resources/Effects/rotate.wav");
	this->rotS.setBuffer(rotB);
	this->rotS.setVolume(20.f);

	this->clearB.loadFromFile("Resources/Effects/clear.wav");
	this->clearS.setBuffer(clearB);
	this->clearS.setVolume(20.f);

	this->gameB.loadFromFile("Resources/Effects/gameover.wav");
	this->gameM.setBuffer(gameB);
	this->gameM.setVolume(20.f);

	this->pinB.loadFromFile("Resources/Effects/pause_in.wav");
	this->pinS.setBuffer(pinB);
	this->pinS.setVolume(20.f);

	this->poutB.loadFromFile("Resources/Effects/pause_out.wav");
	this->poutS.setBuffer(poutB);
	this->poutS.setVolume(20.f);	
}

void GameState::initFonts()
{
	if (!this->fuente.loadFromFile("Fonts/Pixellari.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTexture()
{
;
	this->backGround.setSize(
	sf::Vector2f
	(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	));
	this->backGroundTexture.loadFromFile("Resources/Images/Game3.jpg");
	this->backGround.setTexture(&this->backGroundTexture);

	this->epT.loadFromFile("Resources/Tetromino/sample.png");
	this->epS.setTexture(epT);

	this->bT.loadFromFile("Resources/Tetromino/spriteSheet.png");
	this->bS.setTexture(bT);

	this->gridShapeGame.setPosition(0, 0);
	this->gridShapeGame.setSize(sf::Vector2f(300,570));
	this->gridShapeGame.setFillColor(sf::Color(33, 33, 33));

	this->gridShapeNextpiece.setPosition(450, 335);
	this->gridShapeNextpiece.setSize(sf::Vector2f(200, 150));
	this->gridShapeNextpiece.setFillColor(sf::Color(33, 33, 33));


	// stickers

	this->sticker1T.loadFromFile("Resources/Images/Sticker1.png");
	this->sticker1S.setTexture(sticker1T);
	this->sticker1S.setPosition(sf::Vector2f(870, 80));
	//this->sticker1S.setScale(sf::Vector2f(50, 50));

	this->sticker2T.loadFromFile("Resources/Images/Sticker2.png");
	this->sticker2S.setTexture(sticker2T);
	this->sticker2S.setPosition(sf::Vector2f(400, 400));
	//this->sticker2S.setScale(sf::Vector2f(50, 50));


}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestates_keybinds.ini");

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

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->fuente);
	this->pmenu->addButton("QUIT", 500.f, "Salir");
	this->pmenu->addButton("GAME_STATE", 400.f, "Reiniciar");
}

void GameState::initGameOverMenu()
{
	this->pGameOverMenu = new GameOverMenu(*this->window, this->fuente);
	this->pGameOverMenu->addButton("QUIT", 600.f, "Salir");
	this->pGameOverMenu->addButton("SAVE", 500.f, "Guardar");

}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initFonts();
	this->initVariables();	
	this->initMusic();
	this->currentBlockSetter();
	this->initGameOverMenu();
	this->initTexture();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	
	

}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->pGameOverMenu;
}

void GameState::drawBlocks()
{

	int x = 0;
	rig = 0;
	dow = 0;
	for (int i = 0; i < 120; i+= 30)
	{
		for (int j = 0; j < 120; j += 30)
		{
			if (current[i / 30][j / 30] == 1)
			{
				if (x == 0)
				{
					lef = i + dx;
					x = 1;
				}
				if (j + dy > dow)
				{
					dow = j + dy;
				}
				if (i + dx > rig)
				{
					rig = i + dx;
				}
				bS.setTextureRect(shapes[r]);
				bS.setPosition((i + dx), (j + dy));
				this->window->draw(bS);
			}
		}
	}
	for (int i = 0; i < 23; i++)  //23
	{
		for (int j = 0; j < 10; j++) //10
		{
			if (grid[i][j] != 0) 
			{
				bS.setTextureRect(shapes[grid[i][j] - 1]);
				bS.setPosition(j * 30, i * 30);

				this->window->draw(bS);
			}
		}
	}
	for (int i = 0; i < 120; i += 30)
	{
		for (int j = 0; j < 120; j += 30)
		{
			if (blocks[_next][i / 30][j / 30] == 1)
			{
				bS.setTextureRect(shapes[_next]);
				bS.setPosition(i + 500, j + 350);

				this->window->draw(bS);
			}
		}
	}

}

void GameState::currentBlockSetter()
{
	r = _next;
	r1 = r;
	_next = rand() % (sizeof(blocks) / sizeof(blocks[0]));
	for (int i = 0; i < 4 ; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			current[i][j] = blocks[r][i][j];
		}
	}
}

void GameState::rotateBlocks()
{
	int temp[4][4];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = current[i][j];
		}
	}

	current[0][0] = temp[3][0];
	current[0][1] = temp[2][0];
	current[0][2] = temp[1][0];
	current[0][3] = temp[0][0];

	current[1][0] = temp[3][1];
	current[1][1] = temp[2][1];
	current[1][2] = temp[1][1];
	current[1][3] = temp[0][1];

	current[2][0] = temp[3][2];
	current[2][1] = temp[2][2];
	current[2][2] = temp[1][2];
	current[2][3] = temp[0][2];

	current[3][0] = temp[3][3];
	current[3][1] = temp[2][3];
	current[3][2] = temp[1][3];
	current[3][3] = temp[0][3];


	lef = 0; rig = 0; dow = 0;

	int x = 0;

	for (int i=0; i < 120; i += 30)
	{
		for (int j = 0; j < 120; j += 30)
		{
			if (current[i/30][j/30] == 1)
			{
				if (x == 0)
				{
					lef = i + dx;
					x = 1;
				}
				if (j + dy > dow)
				{
					dow = j + dy;
				}
				if (i + dx > rig)
				{
					rig = i + dx;
				}
			}
		}
	}

	if ((lef < 0 || rig >= 300) || !collision(0,0,dx,dy) || wait)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				current[i][j] = temp[i][j];
			}
		}
	}
	else
	{
		rotS.play();
		rot = 1;
	}

}


void GameState::checkRows()
{
	std::vector<int> row;
	
	int rows = 0;

	for (int i = 0; i < 23; i++)
	{
		bool isFilled = true;
		for (int j = 0; j < 10; j++)
		{
			if (grid[i][j] == 0)
			{
				isFilled = false;
			}
		}
		if (isFilled)
		{
			int tmp = 0;
			row.push_back(i);

			if (rowClear != "Classic")
			{
				while (!clearRow(i))
				{
					grid[i][tmp] = 0;
					tmp++;
					drawBlocks();
					_clear = 1;
					this->window->display();
				}
				grid.erase(grid.begin() + i);
				grid.insert(grid.begin(), { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
			}
			if (rows != 0)
			{
				rows += (1 * rows);
			}
			else
			{
				rows++;
			}

			duplicateY = i * 30;
			duplicateX = 115;
			duplicateY1 = duplicateY - 30;
			duplicateX1 = duplicateX - 30;
		}
	}
	if (rowClear == "Classic")
	{
		if (row.size() > 0)
		{
			_clear = 1;
			for (int k = 0; k < 13; k++)
			{
				for (int j = 0; j < 10; j++)
				{
					for (unsigned int i = 0; i < row.size(); i++)
					{
						grid[row[i]][j] = 9;
					}
				}
				drawBlocks();

				this->window->display();
			}

			for (int k = 0;  k < 15;  k++)
			{
				for (int j = 0; j < 10; j++)
				{
					for (unsigned int i = 0; i < row.size(); i++)
					{
						grid[row[i]][j] = 8;
					}
				}
				drawBlocks();
				this->window->display();
			}
		}
		for (unsigned int i = 0;  i < row.size(); i++)
		{
			grid.erase(grid.begin() + row[i]);
			grid.insert(grid.begin(), { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
		}
	}
	if (rows == 1)
	{
		score += rows * 100;
		
		this->points = score;
	}
	else
	{
		score += rows * 100 * (level);
		
		this->points = score;
	}

}

bool GameState::collision(int x, int y, int x1, int y1)
{
	for (int i = 0; i < 120; i += 30)
	{
		for (int j = 0; j < 120; j += 30)
		{
			if (current[i / 30][j / 30] == 1)
			{
				if (!checkCollision(i + (x1)+x, j + (y1 - y1 % 30) + y))
					return false;
			}
		}
	}
	return true;
}

bool GameState::clearRow(int x)
{
	for (int i = 0; i < 10; i++)
	{
		if (grid[x][i] != 0)
		{
			return false;
		}
	}
	return true;
}


void GameState::checkPossible()
{
	int y = 0;
	int con = 0;
	for (int i = 0; i < 120; i += 30)
	{
		for (int j = 0; j < 120; j += 30)
		{
			if (current[i / 30][j / 30] == 1)
			{
				if (j + dy2 > y)
					y = j + dy2;
				con += 30;
			}
		}
	}
	if (dow > 0)
	{
		while (y < 540)
		{
			if (!collision(0, 30, dx2, dy2))
				break;
			dy2 += 30;
			for (int i = 0; i < 120; i += 30)
			{
				for (int j = 0; j < 120; j += 30)
				{
					if (current[i / 30][j / 30] == 1)
					{
						if (j + dy2 > y)
							y = j + dy2;
						con += 30;
					}
				}
			}
		}

		for (int i = 0; i < 120; i += 30)
		{
			for (int j = 0; j < 120; j += 30)
			{
				if (current[i / 30][j / 30] == 1)
				{
					epS.setPosition(i + dx2, j + (dy2 - dy2 % 30));
					this->window->draw(epS);
				}
			}
		}
	}
}

void GameState::blocksAdder()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (current[i][j] == 1)
			{
				if (((j * 30) + (dy - dy % 30) + 4) / 30 > 0)
				{
					grid[((j * 30) + (dy - dy % 30) + 4) / 30][((i * 30) + dx) / 30] = r + 1;
				}
				else
					gameOver_ = 1;
			}
		}
	}
}


void GameState::SavePlayer()
{

	std::ifstream readfile;

	readfile.open("Datos/registro_player.txt", std::ios::in);

	std::multimap<int, std::string> PointsAndNamesMap;

	if (readfile)
	{
		unsigned int points;
		std::string name	;
		std::string pointsString;

		for (int i = 0; i < 5; i++)
		{
			std::getline(readfile, pointsString);
			std::getline(readfile, name);
			if (pointsString.length() > 0)
			{
				PointsAndNamesMap.insert(std::pair<int, std::string>(std::stoi(pointsString), name));
			}
		}
		readfile.close();
	}
	
	this->textconsole = players[player - Random];

	if (pointGameOver != 0 && textconsole.length() > 1)
	{
		PointsAndNamesMap.insert(std::pair<int, std::string>(pointGameOver, this->textconsole));
	}

	std::ofstream writeFile;

	writeFile.open("Datos/registro_player.txt", std::ios::out | std::ios::trunc);

	if (!WriteFile)
	{
		std::cout << "ERROR" << std::endl;
		exit(1);
	}

	while (PointsAndNamesMap.size() > 5)
	{
		PointsAndNamesMap.erase(PointsAndNamesMap.begin());
	}

	for (auto itr = PointsAndNamesMap.rbegin(); itr != PointsAndNamesMap.rend(); ++itr)
	{
		writeFile << (*itr).first << std::endl;
		writeFile << (*itr).second << std::endl;
	}
	writeFile.close();

}


void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->bgSound.pause();
			this->pauseState();

		}
		else
		{
			this->bgSound.play();
			this->unpauseState();
		}
	}
}

bool GameState::gameOver()
{
	for (int i = 0; i < 10; i++)
	{
		if (grid[0][i] != 0)
		{
			return true;
		}
	}
	return false;
}

void GameState::updatePlayerInput(const float& dt)
{
	downs = 0;
	bool up = 0, down = 0, left = 0, right = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		left = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		right = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		down = 1;
		downs = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ROTATE"))))
	{
		up = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ROTATE_LEFT"))))
	{
		z = 1;
	}
	else
	{
		z = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ROTATE_RIGHT"))))
	{
		objets.clear();
	}

	if (times3.getElapsedTime().asMilliseconds() > fps)
	{
		if (dow < 540 && collision(0,30,dx,dy))
			dy += 3;
		times3.restart();
	}

	if (times.getElapsedTime().asMilliseconds() > 50)
	{
		if (left && (lef - 30) >= 0 && collision(-30, 0, dx, dy))
		{
			dx -= 30;
			bgSound.setVolume(10.0f);
			movS.play();
			mov = 1;
		}
		if (right && (rig + 30) < 300 && collision(30, 0, dx, dy))
		{
			dx += 30;
			bgSound.setVolume(10.0f);
			movS.play();
			mov = 1;
		}

		times.restart();
	}

	if (times2.getElapsedTime().asMilliseconds() > 100)
	{
		if (up)
		{
			rotateBlocks();
			bgSound.setVolume(10.0f);
			times2.restart();
		}
	}
	if (down && dow < 540 && dow > 0 && collision(0,30,dx,dy))
	{
		dy = dy - (dy % 30);
		dy += 30;
	}

	dx2 = dx;
	dy2 = dy;

}

bool GameState::checkCollision(int x, int y)
{
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (grid[i][j] != 0)
			{
				if (i * 30 == y && j * 30 == x)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
	if (this->pmenu->isButtonPressed("GAME_STATE"))
	{
		overGame = 1;
	}
}

void GameState::updateGameOverMenuButttons()
{
	if (this->pGameOverMenu->isButtonPressed("QUIT") && this->getKeyTime())
	{
		this->endState();
	}
	if (this->pGameOverMenu->isButtonPressed("SAVE") && this->getKeyTime())
	{
		this->SavePlayer();
	}
}

void GameState::updateText()
{
	std::stringstream ss;

	ss << "Points : " << this->points << "\nNivel : " << this->nivel;
	
	this->text.setString(ss.str());
	
	std::stringstream pp;

	pp << "Points : " << this->pointGameOver << "\tNivel : " << this->NivelGameOver;

	this->textGameOver.setString(pp.str());
}



void GameState::updateWorld(const float& dt)
{
	this->updatePlayerInput(dt);
	this->updatePlayer();
	this->updateText();
	this->updateEffects();
	
}

void GameState::updatePlayer(sf::RenderTarget* target)
{
	
	if (dow < 540 && collision(0, 30, dx, dy))
	{
		checkPossible();
	}
	if (dow >= 540 || !collision(0, 30, dx, dy))
	{
		dy = dy - (dy % 30);
		wait = 1;
	}
	if ((dow >= 540 || !collision(0, 30, dx, dy)) && !z)
	{
		wait = 0;
		score += 120;

		this->points = score;
		
		this->pointGameOver = points;


		if (score > subScore + 2000) 
		{
			level += 1;

			this->nivel = level;

			this->NivelGameOver = nivel;

			if (fps != 10) 
				fps--;
			subScore = score;
		}

		bgSound.setVolume(20.0f);
		fall = 1;
		blocksAdder();
		currentBlockSetter();
		duplicateX = dx + 20;
		duplicateY = dow;
		if (duplicateX < 20)
			duplicateX = 30;
		duplicateX1 = duplicateX - 30;
		duplicateY1 = duplicateY - 30;
		lef = 0;
		rig = 0;
		dx = 90;
		dy = -150;
		dow = 0;
	}

	if (overGame)
	{
		bgSound.stop();
		stop = 1;
		overGame = 0;
		grid.clear();
		for (int i = 0; i < 23; i++)
		{
			grid.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
		}
		currentBlockSetter();
		wait = 0;
		lef = 0;
		rig = 0;
		dx = 90;
		dy = -180;
		dow = 0;
		score = 0, level = 0, subScore = 0, subScore1 = 0, fps = 40;

		this->nivel = level;
		this->points = score;
	}
	if (gameOver_)
	{
		over.restart();
		bgSound.stop();
		stop = 1;
		gameOver_ = 0;
		gameM.play();
		gameM.stop();
		grid.clear();

		while (over.getElapsedTime().asSeconds() < 0.1f)
		{
			this->pausedGameOVer = true;
		}

		for (int i = 0; i < 23; i++)
		{
			grid.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
		}

		currentBlockSetter();
		lef = 0;
		rig = 0;
		dx = 90;
		dy = -180;
		dow = 0;
		score = 0, level = 0, subScore = 0, subScore1 = 0, fps = 40;

		this->nivel = level;
		this->points = score;
	}

	checkRows();

	if (score != subScore1 && !scorer)
	{
		scorer = 1;
	}
	if (scorer)
	{
		if (duplicateY > duplicateY1)
		{
			duplicateY -= 1;
		}
		else
		{
			scorer = 0;
			subScore1 = score;
		}
	}
}

void GameState::updateEffects()
{
	if (stop)
	{
		bgSound.play();
		stop = 0;
	}
	bgSound.setVolume(100.0f);
	if (fall && fallS.getPlayingOffset().asSeconds() >= fallB.getDuration().asSeconds())
	{
		fallS.stop();
		fall = 0;
	}
	if (mov && movS.getPlayingOffset().asSeconds() >= movB.getDuration().asSeconds())
	{
		movS.stop();
		mov = 0;
	}
	if (rot && rotS.getPlayingOffset().asSeconds() >= rotB.getDuration().asSeconds())
	{
		rotS.stop();
		rot = 0;
	}

	if (bgSound.getStatus() == 0)
	{
		if (song != 4)
			song++;
		else
			song = 0;
		bgSound.openFromFile(musics[song]);
		bgSound.play();
	}
}

void GameState::update(const float& dt)
{

	this->updateMousePosition();
	this->updateInput(dt);
	this->updateKeytime(dt);

	if (!this->pausedGameOVer)
	{
		if (!this->paused)
		{
			this->updateWorld(dt);
		}
		else
		{
			this->pmenu->update(this->mousePosView);
			this->updatePauseMenuButtons();
		}
	}
	else
	{
		bgSound.stop();
		this->pGameOverMenu->update(this->mousePosView);
		this->updateGameOverMenuButttons();
	}
}




void GameState::render(sf::RenderTarget* target)
{
	// pantalla
	if (!target)
		target = this->window;

	target->draw(backGround);
	target->draw(gridShapeGame);
	target->draw(gridShapeNextpiece);
	target->draw(sticker1S);
	target->draw(sticker2S);


	this->drawBlocks();

	this->updatePlayer(target);

	target->draw(this->text);

	if (this->paused)
		this->pmenu->render(*target);

	if (this->pausedGameOVer)
	{

		this->pGameOverMenu->render(*target);
		target->draw(this->textGameOver);
	}

	


	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->fuente);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());


	target->draw(mouseText);

	

}
