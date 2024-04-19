#include "FrontEnd.h"
#include <SFML/Graphics.hpp>


sf::RenderWindow Screen::createWindow(int width, int height, string title) {
    
    sf::RenderWindow temp(sf::VideoMode(width,height), title, sf::Style::Close);


}

void Screen::displayWindow(sf::RenderWindow& window) {
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return;
            }
        }
        window.clear(sf::Color::Red);
        window.display();
    }
}
