#pragma once
#include "All_Include_File.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event sfmlEvent;
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
	const bool running() const;
	void pollEvents();

	void update();
	void render();
};

