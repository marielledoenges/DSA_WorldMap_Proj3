#include "FrontEnd.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constructor
FrontEnd::FrontEnd(int width, int height, const std::string& title) {
    window.create(sf::VideoMode(width, height), title, sf::Style::Close);
    backgroundColor = sf::Color::White;
    textColor = sf::Color::Black;
    outlineColor = sf::Color::Blue;
    loadFont("fonts/Roboto-Regular.ttf"); // Make sure to provide a valid path
}



// Load font
void FrontEnd::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font at: " << fontPath << std::endl;
        exit(EXIT_FAILURE);
    }
}



// Draw Boarding Pass
void FrontEnd::drawBoardingPass(const Flight& flight) {
    window.clear(backgroundColor);

    sf::RectangleShape passBackground(sf::Vector2f(500, 250));
    passBackground.setPosition(50, 50);
    passBackground.setFillColor(sf::Color(255, 250, 250)); // Light off-white
    passBackground.setOutlineThickness(5);
    passBackground.setOutlineColor(outlineColor);
    window.draw(passBackground);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(textColor);

    text.setString("Flight No: " + flight.flightNumber);
    text.setPosition(60, 60);
    window.draw(text);

    text.setString("From: " + flight.originCity + " To: " + flight.destinationCity);
    text.setPosition(60, 100);
    window.draw(text);

    text.setString("Departure: " + flight.date + " at " + flight.time);
    text.setPosition(60, 140);
    window.draw(text);

    text.setString("Duration: " + std::to_string(flight.duration) + " hours");
    text.setPosition(60, 180);
    window.draw(text);

    text.setString("Price: $" + std::to_string(flight.price));
    text.setPosition(60, 220);
    window.draw(text);

    window.display();
}



// Run Event Loop
void FrontEnd::run() {
    std::vector<Flight> availableFlights; // Populate this from external sources

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Assume a function to fetch or update available flights here
        if (!availableFlights.empty()) {
            Flight selectedFlight;
            handleUserInput(availableFlights, selectedFlight);
            drawBoardingPass(selectedFlight);
        }
    }
}



// Handle User Input
void FrontEnd::handleUserInput(std::vector<Flight>& availableFlights, Flight& selectedFlight) {
    std::cout << "Available flights (Enter index to select):" << std::endl;
    for (size_t i = 0; i < availableFlights.size(); i++) {
        std::cout << i + 1 << ": " << availableFlights[i].originCity << " to "
                  << availableFlights[i].destinationCity << " on "
                  << availableFlights[i].date << " at " << availableFlights[i].time << std::endl;
    }

    int choice;
    std::cin >> choice;
    if (choice > 0 && choice <= availableFlights.size()) {
        selectedFlight = availableFlights[choice - 1];
    }
}
