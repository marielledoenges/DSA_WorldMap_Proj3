#include <iostream>
#include "FrontEnd.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
using namespace std;





string WelcomeScreen::showWelcomeScreen() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Welcome to the Travel App", sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load arial.ttf" << endl;
        return ""; // Exit if font not found
    }

    // Load a background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/world_map.jpg")) {
        cerr << "Failed to load world_map.jpg" << endl;
        return ""; // Exit if background image not found
    }
    sf::Sprite background(backgroundTexture);

    // Setup welcome text
    sf::Text welcomeText("Welcome! Select an Option:", font, 30);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(50, 50);

    // Style the buttons with a more geographical theme
    sf::RectangleShape mapButton(sf::Vector2f(250, 70));
    mapButton.setPosition(275, 150);
    mapButton.setFillColor(sf::Color(0, 102, 204, 150)); // Semi-transparent blue
    sf::Text mapButtonText("Explore the Map", font, 25);
    mapButtonText.setFillColor(sf::Color::White);
    mapButtonText.setPosition(285, 165);

    sf::RectangleShape passButton(sf::Vector2f(250, 70));
    passButton.setPosition(275, 250);
    passButton.setFillColor(sf::Color(102, 204, 0, 150)); // Semi-transparent green
    sf::Text passButtonText("View Boarding Pass", font, 25);
    passButtonText.setFillColor(sf::Color::White);
    passButtonText.setPosition(285, 265);

    // Add an animation or effect
    sf::CircleShape animationCircle(40);
    animationCircle.setFillColor(sf::Color(255, 255, 255, 50));
    animationCircle.setPosition(400, 300);
    float scale = 1.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            // Check for mouse button pressed and hover effects
            sf::Vector2f mouse(sf::Mouse::getPosition(window));
            bool isMouseOverMapButton = mapButton.getGlobalBounds().contains(mouse);
            bool isMouseOverPassButton = passButton.getGlobalBounds().contains(mouse);

            if (event.type == sf::Event::MouseMoved) {
                if (isMouseOverMapButton) {
                    mapButton.setFillColor(sf::Color(0, 102, 204)); // Brighter color on hover
                } else {
                    mapButton.setFillColor(sf::Color(0, 102, 204, 150)); // Original color when not hovered
                }
                if (isMouseOverPassButton) {
                    passButton.setFillColor(sf::Color(102, 204, 0)); // Brighter color on hover
                } else {
                    passButton.setFillColor(sf::Color(102, 204, 0, 150)); // Original color when not hovered
                }
            }

            // Check for mouse button pressed
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(sf::Mouse::getPosition(window));
                if (mapButton.getGlobalBounds().contains(mouse)) {
                    window.close();
                    return "map";
                    // Function to show map screen
                } else if (passButton.getGlobalBounds().contains(mouse)) {
                    window.close();
                    return "pass";
                    // Function to show boarding pass screen
                }
            }
        }

        // Animate the circle
        animationCircle.setScale(scale, scale);
        scale += 0.005;
        if (scale > 2.0) scale = 1.0;

        window.clear();
        window.draw(background); // Draw the background first
        window.draw(welcomeText);
        window.draw(mapButton);
        window.draw(mapButtonText);
        window.draw(passButton);
        window.draw(passButtonText);
        window.draw(animationCircle); // Draw the animated circle

        window.display();
    }
}




void MapScreen::loadPins() {
    ifstream file;
    file.open("cityCoordinates.csv");
    pinT.loadFromFile("images/red_pin.png");

    sf::Sprite temp;
    temp.setTexture(pinT);
    temp.setOrigin(pinT.getSize().x/2, pinT.getSize().y);
    int x, y;
    string loc;
    for(int i = 0; i < 99; i++){
        getline(file,loc);
        x = stoi(loc);
        getline(file,loc);
        y = stoi(loc);
        temp.setPosition(x,y);
        cityPts.push_back(temp);
    }

}

string MapScreen::getCityFromClick(sf::RenderWindow& window, int x, int y) {
    for(int i = 0; i < cityPts.size(); i++){
        sf::Sprite temp = cityPts[i];
        if(cityPts[i].getGlobalBounds().contains(x, y)){
            cout << "line " << (2*i) + 1 << endl;
            cout << "coordinates " << x << ", " << y << endl;
            return cityNames[i] + "\n";
        }
    }

    return "NA\n";
}

void MapScreen::writeCityLocations(int x, int y ) {
    ofstream file;
    file.open("cityCoordinates.csv", ios_base::app);
    file << x << endl << y << endl;
}

MapScreen::MapScreen() {
    map.setTexture(mapTexture);
    map.setOrigin(0,0);

    zoomInT.loadFromFile("images/zoom_in.jpg");
    zoomOutT.loadFromFile("images/zoom_out.jpg");

    upT.loadFromFile("images/up.png");
    dT.loadFromFile("images/down.png");
    RT.loadFromFile("images/right.png");
    LT.loadFromFile("images/left.png");

    pinT.loadFromFile("images/red_pin.png");

    zoomIn.setTexture(zoomInT);
    zoomIn.setPosition(40, 300);

    zoomOut.setTexture(zoomOutT);
    zoomOut.setPosition(40, 360);

    loadPins();


    up.setTexture(upT);
    up.setPosition(60, 550);
    down.setTexture(dT);
    down.setPosition(60, 620);
    right.setTexture(RT);
    right.setPosition(95, 585);
    left.setTexture(LT);
    left.setPosition(25, 585);

    ifstream file;
    file.open("cityCoordinates.csv");
    file.close();

}

void MapScreen::displayWindow() {
    sf::RenderWindow window(sf::VideoMode(1494,700), "testing", sf::Style::Close);

    mapView.setCenter(window.getSize().x/2,window.getSize().y/2);
    mapView.setSize(window.getSize().x, window.getSize().y);

    buttonView.setCenter(window.getSize().x/2,window.getSize().y/2);
    buttonView.setSize(window.getSize().x, window.getSize().y);
    int shiftL = 0, shiftR = 0, shiftU = 0, shiftD = 0, zIn = 0, zOut = 0;

    int track = 45;
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
                if(zoomIn.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    if(zIn < 12){
                        mapView.setSize(mapView.getSize().x - 100, mapView.getSize().y - 46.85);
                        zIn += 1;
                        zOut -= 1;
                    }
                }else if(zoomOut.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    if(zIn > 0){
                        mapView.setSize(mapView.getSize().x + 100, mapView.getSize().y + 46.85);
                        zIn -= 1;
                        zOut += 1;
                    }
                }else if(up.getGlobalBounds().contains(window.mapPixelToCoords(mouse)) && shiftU < zIn) {
                    mapView.move(0,-23.43);
                    shiftU += 1;
                    shiftD -= 1;
                }else if(down.getGlobalBounds().contains(window.mapPixelToCoords(mouse)) && shiftD < zIn) {
                    mapView.move(0,23.43);
                    shiftD += 1;
                    shiftU -= 1;
                }else if(left.getGlobalBounds().contains(window.mapPixelToCoords(mouse)) && shiftL < zIn) {
                    mapView.move(-50,0);
                    shiftL += 1;
                    shiftR -= 1;
                }else if(right.getGlobalBounds().contains(window.mapPixelToCoords(mouse)) && shiftR < zIn) {
                    mapView.move(50,0);
                    shiftL -= 1;
                    shiftR += 1;
                }

                else{

                    int totalClickX = window.mapPixelToCoords(mouse, mapView).x;
                    int totalClickY =  window.mapPixelToCoords(mouse, mapView).y;
                    cout << totalClickX << ", " << totalClickY << endl;
                    string chosenCity = getCityFromClick(window, totalClickX, totalClickY);
                    cout << chosenCity;

//                    cout << "Click on: " << cityNames[track + 1] << endl;
//                    sf::Sprite temp;
//                    temp.setTexture(pinT);
//                    temp.setPosition(totalClickX, totalClickY);
//                    temp.setOrigin(pinT.getSize().x/2, pinT.getSize().y-5);
//                    cityPts.push_back(temp);
//


                }
            }
        }
        window.clear(sf::Color::Red);

        window.setView(mapView);
        window.draw(map); // Draw the map
        for(auto pin : cityPts){
            window.draw(pin);
        }

        window.setView(window.getDefaultView()); // Switch to the default view (screen coordinates)
        window.draw(zoomIn);
        window.draw(zoomOut);
        window.draw(up);
        window.draw(down);
        window.draw(left);
        window.draw(right);


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

void Ticket::drawBoardingPass(const Flight flight) {
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

//void Ticket::run() {
//    std::vector<Flight> availableFlights = {
//            // Flight fetching logic
//    };
//    Flight selectedFlight;
//    while(window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//
//        handleUserInput(availableFlights, selectedFlight); // Allow the user to select a flight
//        drawBoardingPass(selectedFlight); // Draw the selected flight's boarding pass
//    }
//}

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