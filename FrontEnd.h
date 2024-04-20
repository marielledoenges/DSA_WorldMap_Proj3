#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include <vector>

struct FrontEnd {
    sf::RenderWindow window;
    sf::Font font;
    sf::Color backgroundColor;
    sf::Color textColor;
    sf::Color outlineColor;

    FrontEnd(int width, int height, const std::string& title);
    void run();
    void loadFont(const std::string& fontPath);
    void drawBoardingPass(const Flight& flight);
    void handleUserInput(std::vector<Flight>& availableFlights, Flight& selectedFlight);
};
