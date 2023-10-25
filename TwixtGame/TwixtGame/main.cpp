#include <iostream>
#include<SFML/Graphics.hpp>

int main()
{
    std::cout << "Stemi Work Her\n";
    sf::RenderWindow window(sf::VideoMode(800, 600), "Setarea culorii unui cerc in SFML");

    // Crearea unui obiect CircleShape
    sf::CircleShape circle(50); // Raza cercului

    // Setarea poziției cercului
    circle.setPosition(375, 275); // Poziția x, y

    // Setarea culorii cercului (în acest caz, verde)
    circle.setFillColor(sf::Color::Green); // Setarea culorii

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(circle); // Desenarea cercului
        window.display();
    }
    return 0;
}

