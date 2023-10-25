#include "Game.h"

void Game::initVariable()
{
	this->EndGame = false;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "TwixT BigPython", sf::Style::Close | sf::Style::Titlebar);
}

//Constructor && Deconstructor

Game::Game()
{
	this->initVariable();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::update()
{
}

void Game::render()
{
}

//Functions
