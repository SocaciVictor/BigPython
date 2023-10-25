#include "Game.h"

void Game::initVariable()
{
	this->EndGame = false;
}

void Game::initWindow()
{
	this->videoMode.width = 800;	 // Window width
	this->videoMode.height = 600;    //Window height
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
	int line = 24;
	int colum = 24;
	//Board
	sf::RectangleShape square(sf::Vector2f(520, 520));
	square.setPosition(100, 50);
	square.setFillColor(sf::Color(192, 192, 192, 255));

	sf::RectangleShape line1(sf::Vector2f(430, 3));
	line1.setPosition(148, 91.5);
	line1.setFillColor(sf::Color::Red);

	sf::RectangleShape line2(sf::Vector2f(430, 3));
	line2.setPosition(148, 531.5);
	line2.setFillColor(sf::Color::Red);

	sf::RectangleShape line3(sf::Vector2f(3, 430));
	line3.setPosition(141.5, 97.5);
	line3.setFillColor(sf::Color::Black);

	sf::RectangleShape line4(sf::Vector2f(3, 430));
	line4.setPosition(581.5, 97.5);
	line4.setFillColor(sf::Color::Black);
	this->window->clear();

	//Render stuff

	this->window->draw(square);
	this->window->draw(line1);
	this->window->draw(line2);
	this->window->draw(line3);
	this->window->draw(line4);

	for (int i = 0; i < line; i++) {
		for (int j = 0; j < colum; j++) {
			if ((i != 0 || j != 0) && (i != 23 || j != 23) && (i != 23 || j != 0) && (i != 0 || j != 23)) {
				sf::CircleShape circle(3);
				circle.setFillColor(sf::Color(128, 128, 128, 255));
				circle.setPosition(i * 20 + 130, j * 20 + 80);
				this->window->draw(circle);
			}
		}
	}

	//Display stuff
	this->window->display();
}


