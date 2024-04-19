#pragma once
#include <SFML/Graphics.hpp>
#include "Flight.h"
#include <vector>

struct FrontEnd {
    sf::RenderWindow window;
    sf::Font font;
    sf::Color backgroundColor;
    sf::Color textColor;
    sf::Color outlineColor;

    // Constructor
    FrontEnd(int width, int height, const std::string& title);

    // Methods
    void run();
    void loadFont(const std::string& fontPath);
    void drawBoardingPass(const Flight& flight);
    void handleUserInput(std::vector<Flight>& availableFlights, Flight& selectedFlight);
};

