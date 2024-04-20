#include <iostream>
#include "FrontEnd.h"
#include <SFML/Graphics.hpp>
using namespace std;


//sf::RenderWindow MapScreen::createWindow(int width, int height, string title) {
//
//    sf::RenderWindow temp(sf::VideoMode(width,height), title, sf::Style::Close);
//
//
//}

MapScreen::MapScreen() {
    map.setTexture(mapTexture);
    map.setOrigin(0,0);

    zoomInT.loadFromFile("images/zoom_in.jpg");
    zoomOutT.loadFromFile("images/zoom_out.jpg");
    pinT.loadFromFile("images/red_pin.png");

    zoomIn.setTexture(zoomInT);
    zoomIn.setPosition(40, 500);

    zoomOut.setTexture(zoomOutT);
    zoomOut.setPosition(40, 560);

    pin.setTexture(pinT);
    pin.setPosition(500,300);



    //view.setCenter(0,0);
    //view.setSize(1494, 700);
    //map.setScale(0.7,0.7);

}

void MapScreen::displayWindow() {
    sf::RenderWindow window(sf::VideoMode(1494,700), "testing", sf::Style::Close);

    view.setCenter(window.getSize().x/2,window.getSize().y/2);
    view.setSize(window.getSize().x/3, window.getSize().y/3);


    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return;
            }
            if(event.type == sf::Event::MouseButtonReleased){
                sf::Vector2i mouse;
                mouse = sf::Mouse::getPosition(window);
                int clickX = mouse.x;
                int clickY = mouse.y;
                //cout << clickX << " " << clickY << endl;
               // map.scale(0.9, 0.9);
                //map.setPosition(map.getPosition().x+10, map.getPosition().y-100);

                if(zoomIn.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    if(map.getScale().x < 2.6) {
                        map.setScale(map.getScale().x + 0.2, map.getScale().y + 0.2);
                        cout << map.getScale().x << " " << map.getScale().y << endl;
                        map.setOrigin(mapTexture.getSize().x / 2, mapTexture.getSize().y / 2);
                        map.setPosition(window.getSize().x / 2, window.getSize().y / 2);
                    }

                }else if(zoomOut.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    if(map.getScale().x > 1) {
                        map.setScale(map.getScale().x - 0.2, map.getScale().y - 0.2);
                        cout << map.getScale().x << " " << map.getScale().y << endl;
                        map.setOrigin(mapTexture.getSize().x / 2, mapTexture.getSize().y / 2);
                        map.setPosition(window.getSize().x / 2, window.getSize().y / 2);
                    }
                }else{
                    cout << clickX << ", " << clickY << endl;
                }
            }
        }
        window.clear(sf::Color::Red);
        window.draw(map);
        window.draw(zoomIn);
        window.draw(zoomOut);
        window.draw(pin);
        window.setView(view);
        window.display();
    }
}



Ticket::Ticket(int width, int height, const std::string& title) :
        backgroundColor(sf::Color::White), textColor(sf::Color::Black), outlineColor(sf::Color::Black) {
    window.create(sf::VideoMode(width, height), title, sf::Style::Close);
}

void Ticket::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Could not load font at: " << fontPath << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Ticket::drawBoardingPass(const Flight& flight) {
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


void Ticket::run() {
    std::vector<Flight> availableFlights = {
            // Flight fetching logic
    };
    Flight selectedFlight;
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        handleUserInput(availableFlights, selectedFlight); // Allow the user to select a flight
        drawBoardingPass(selectedFlight); // Draw the selected flight's boarding pass
    }
}


void Ticket::handleUserInput(std::vector<Flight>& availableFlights, Flight& selectedFlight) {
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