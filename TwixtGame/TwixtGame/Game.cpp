#include "Game.h"

void Game::initVariable()
{
	this->EndGame = false;
}

void Game::initWindow()
{
	this->videoMode.width = 1000;	 // Window width
	this->videoMode.height = 800;    //Window height
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

//Functions

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent)) {
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}

	}
}

void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	sf::CircleShape circle(50);
	std::cout << circle.getPosition().x<<"\n";
		
	circle.setFillColor(sf::Color(192, 192, 192, 255));

	this->window->clear();

	//Render stuff

	this->window->draw(circle);

	//Display stuff
	this->window->display();
}


