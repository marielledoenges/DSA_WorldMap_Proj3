#include "FrontEnd.h"
#include <SFML/Graphics.hpp>
#include <iostream>

FrontEnd::FrontEnd(int width, int height, const std::string& title) :
        backgroundColor(sf::Color::White), textColor(sf::Color::Black), outlineColor(sf::Color::Black) {
    window.create(sf::VideoMode(width, height), title, sf::Style::Close);
}

void FrontEnd::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Could not load font at: " << fontPath << std::endl;
        exit(EXIT_FAILURE);
    }
}

void FrontEnd::drawBoardingPass(const Flight& flight) {
    // Clear previous content
    window.clear(backgroundColor);

    // Draw the boarding pass background
    sf::RectangleShape passBackground(sf::Vector2f(600, 300));
    passBackground.setPosition(100, 150);
    passBackground.setFillColor(sf::Color(230, 230, 250)); // Light shade for the boarding pass
    passBackground.setOutlineThickness(2);
    passBackground.setOutlineColor(outlineColor);
    window.draw(passBackground);

    // Set up text elements on the boarding pass
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(textColor);

    // Display flight number
    text.setString("Flight Number: " + flight.flightNumber);
    text.setPosition(120, 160);
    window.draw(text);

    // Display origin and destination
    text.setString("From: " + flight.originCity + " To: " + flight.destinationCity);
    text.setPosition(120, 200);
    window.draw(text);

    // Display departure time
    text.setString("Departure: " + flight.time);
    text.setPosition(120, 240);
    window.draw(text);

    // Display distance and duration
    text.setString("Distance: " + std::to_string(flight.distance) + " miles, Duration: " + std::to_string(flight.duration) + " hours");
    text.setPosition(120, 280);
    window.draw(text);

    // Display price
    text.setString("Price: $" + std::to_string(flight.price));
    text.setPosition(120, 320);
    window.draw(text);
    // Display the window content
    window.display();
}


void FrontEnd::run() {
    std::vector<Flight> availableFlights = {
            // Flight fetching logic
    };

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        Flight selectedFlight;
        handleUserInput(availableFlights, selectedFlight); // Allow the user to select a flight
        drawBoardingPass(selectedFlight); // Draw the selected flight's boarding pass
    }
}


void FrontEnd::handleUserInput(std::vector<Flight>& availableFlights, Flight& selectedFlight) {
    int index = 0;
    std::cout << "Available Flights:" << std::endl;
    for (size_t i = 0; i < availableFlights.size(); ++i) {
        std::cout << i + 1 << ": From " << availableFlights[i].originCity
                  << " to " << availableFlights[i].destinationCity << std::endl;
    }
    std::cout << "Enter the number of the flight you want to select: ";
    std::cin >> index;
    if (index > 0 && index <= availableFlights.size()) {
        selectedFlight = availableFlights[index - 1];
    }
}
