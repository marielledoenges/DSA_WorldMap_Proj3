#include "FrontEnd.h"
#include <SFML/Graphics.hpp>

sf::RenderWindow Screen::createWindow(int width, int height, string title) {
    sf::RenderWindow temp(sf::VideoMode(width, height), title, sf::Style::Close);
    return temp;
}

void Screen::displayWindow(sf::RenderWindow& window) {
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        // If you have a flight to display, draw the boarding pass
        // drawBoardingPass(window, flight);
        window.display();
    }
}

void Screen::drawBoardingPass(sf::RenderWindow& window, Flight& flight) {
    // Create SFML shapes and text to represent the boarding pass
    sf::RectangleShape pass(sf::Vector2f(600, 300)); // Example size
    pass.setFillColor(sf::Color::White);
    pass.setOutlineColor(sf::Color::Black);
    pass.setOutlineThickness(2);
    pass.setPosition(100, 150); // Example position

    sf::Font font;
    font.loadFromFile(".ttf"); // Load your font

    sf::Text text;
    text.setFont(font);
    text.setString("Boarding Pass\n" +
                   "Flight Number: " + flight.flightNumber + "\n" +
                   "From: " + flight.originCity + " To: " + flight.destinationCity + "\n" +
                   // Add other details
                   "Departure: " + flight.date + " at " + flight.time);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(pass.getPosition().x + 20, pass.getPosition().y + 20);

    // Draw the shapes and text to the window
    window.draw(pass);
    window.draw(text);
    
}
