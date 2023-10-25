#pragma once
#include "All_Include_File.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;

	bool EndGame;

	void initVariable();
	void initWindow();
public:
	//Constructor && Deconstructor
	Game();
	~Game();

	//Accesors

	//Modifiers

	//Functions
	void update();
	void render();
};

