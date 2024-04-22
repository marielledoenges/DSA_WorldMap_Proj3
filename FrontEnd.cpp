#include <iostream>
#include "FrontEnd.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include "graph.h"
#include <vector>
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
                return "";
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
//            cout << "line " << (2*i) + 1 << endl;
//            cout << "coordinates " << x << ", " << y << endl;
            return cityNames[i];
        }
    }

    return "NA";
}

void MapScreen::writeCityLocations(int x, int y ) {
    ofstream file;
    file.open("cityCoordinates.csv", ios_base::app);
    file << x << endl << y << endl;
}

MapScreen::MapScreen() {
    map.setTexture(mapTexture);
    map.setOrigin(0,0);

    font.loadFromFile("arial.ttf");

    zoomInT.loadFromFile("images/zoom_in.jpg");
    zoomIn.setTexture(zoomInT);
    zoomIn.setPosition(40, 300);

    zoomOutT.loadFromFile("images/zoom_out.jpg");
    zoomOut.setTexture(zoomOutT);
    zoomOut.setPosition(40, 360);

    upT.loadFromFile("images/up.png");
    up.setTexture(upT);
    up.setPosition(60, 550);

    dT.loadFromFile("images/down.png");
    down.setTexture(dT);
    down.setPosition(60, 620);

    RT.loadFromFile("images/right.png");
    right.setTexture(RT);
    right.setPosition(95, 585);

    LT.loadFromFile("images/left.png");
    left.setTexture(LT);
    left.setPosition(25, 585);

    pinT.loadFromFile("images/red_pin.png");
    loadPins();

    promptT.loadFromFile("images/prompt.jpg");
    promptBorder.setTexture(promptT);
    promptBorder.setPosition(1250, 550);
    promptBorder.setScale(1.5, 0.8);


    yesT.loadFromFile("images/check.jpg");
    yes.setTexture(yesT);
    yes.setPosition(1250,640);

    noT.loadFromFile("images/X.jpg");
    no.setTexture(noT);
    no.setPosition(1300, 640);

    select1.setString("Click on a city (origin city).");
    select1.setFillColor(sf::Color::Black);
    select1.setStyle(sf::Text::Bold);
    select1.setFont(font);
    select1.setCharacterSize(25);
    setTextRight(select1, 1360, 590);

    youSelected.setString("Confirm your selection of: ");
    youSelected.setFillColor(sf::Color::Black);
    youSelected.setStyle(sf::Text::Bold);
    youSelected.setFont(font);
    youSelected.setCharacterSize(25);
    setTextRight(youSelected, 1250, 590);

    select2.setString("Click on a second city.");
    select2.setFillColor(sf::Color::Black);
    select2.setStyle(sf::Text::Bold);
    select2.setFont(font);
    select2.setCharacterSize(25);
    setTextRight(select2, 1360, 590);

    optionList.setString("Choose from one of the following options:");
    optionList.setFillColor(sf::Color::Black);
    optionList.setStyle(sf::Text::Bold);
    optionList.setFont(font);
    optionList.setCharacterSize(25);
    setTextRight(optionList, 1360, 530);

    selectAnother.setString("Select a destination");
    selectAnother.setFillColor(sf::Color::Black);
    selectAnother.setStyle(sf::Text::Bold);
    selectAnother.setFont(font);
    selectAnother.setCharacterSize(25);
    setTextRight(selectAnother, 1450, 540);

    cheapDirect.setString("Find the cheapest direct flight from here");
    cheapDirect.setFillColor(sf::Color::Black);
    cheapDirect.setStyle(sf::Text::Bold);
    cheapDirect.setFont(font);
    cheapDirect.setCharacterSize(25);
    setTextRight(cheapDirect, 1450, 570);

    cheapIntl.setString("Find the cheapest international flight from here");
    cheapIntl.setFillColor(sf::Color::Black);
    cheapIntl.setStyle(sf::Text::Bold);
    cheapIntl.setFont(font);
    cheapIntl.setCharacterSize(25);
    setTextRight(cheapIntl, 1450, 600);

    cheapInMonth.setString("Find the cheapest flight in a month of your choice from here");
    cheapInMonth.setFillColor(sf::Color::Black);
    cheapInMonth.setStyle(sf::Text::Bold);
    cheapInMonth.setFont(font);
    cheapInMonth.setCharacterSize(25);
    setTextRight(cheapInMonth, 1450, 630);

    minWBudget.setString("Find the minimum number of cities you can travel to within a certain budget from here.");
    minWBudget.setFillColor(sf::Color::Black);
    minWBudget.setStyle(sf::Text::Bold);
    minWBudget.setFont(font);
    minWBudget.setCharacterSize(25);
    setTextRight(minWBudget, 1450, 660);

    checkDirect.setString("Check for a direct flight between:");
    checkDirect.setFillColor(sf::Color::Black);
    checkDirect.setStyle(sf::Text::Bold);
    checkDirect.setFont(font);
    checkDirect.setCharacterSize(25);
    setTextRight(checkDirect, 1450, 540);

    getPass.setString("Print my boarding pass for: ");
    getPass.setFillColor(sf::Color::Black);
    getPass.setStyle(sf::Text::Bold);
    getPass.setFont(font);
    getPass.setCharacterSize(25);
    setTextRight(getPass, 1450, 570);


}

void MapScreen::putPromptsToScreen(sf::RenderWindow &window, string interactionStatus) {
    string toWrite = "";
    if(interactionStatus == "0"){
        setTextRight(select1, 1450, 600);
        window.draw(select1);

    } else if(interactionStatus == "confirm1" || interactionStatus == "confirm2"){
        toWrite = "Confirm your selection of: " + placeHold;
        youSelected.setString(toWrite);
        setTextRight(youSelected, 1450, 600);
        window.draw(youSelected);
        window.draw(yes);
        window.draw(no);

    }else if(interactionStatus == "1"){
        setTextRight(optionList, 1450, 500);
        window.draw(optionList);
        window.draw(selectAnother);
        window.draw(cheapDirect);
        window.draw(cheapIntl);
        window.draw(cheapInMonth);
        window.draw(minWBudget);

    }else if(interactionStatus == "2"){
        setTextRight(optionList, 1450, 500);
        window.draw(optionList);
        checkDirect.setString("Check for a direct flight between: " + origin + " and " + dest);
        setTextRight(checkDirect, 1450, 540);
        window.draw(checkDirect);

        getPass.setString("Print my boarding pass for: " + origin + " to " + dest);
        setTextRight(getPass, 1450, 570);
        window.draw(getPass);
    }else if(interactionStatus == "click second"){
        setTextRight(select2, 1450, 600);
        window.draw(select2);

    }
}

void MapScreen::displayWindow() {
    sf::RenderWindow window(sf::VideoMode(1494,700), "testing", sf::Style::Close);

    mapView.setCenter(window.getSize().x/2,window.getSize().y/2);
    mapView.setSize(window.getSize().x, window.getSize().y);

    buttonView.setCenter(window.getSize().x/2,window.getSize().y/2);
    buttonView.setSize(window.getSize().x, window.getSize().y);
    int shiftL = 0, shiftR = 0, shiftU = 0, shiftD = 0, zIn = 0, zOut = 0;


    string interaction = "0";

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
                }else if(yes.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    if(interaction == "confirm1"){
                        origin = placeHold;
                        interaction = "1";
                    }else if(interaction == "confirm2"){
                        interaction = "2";
                        dest = placeHold;
                    }
                }else if(no.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    if(interaction == "confirm1"){
                        interaction = "0";
                    }else if(interaction == "confirm2"){
                        interaction = "click second";
                    }
                }else if(selectAnother.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    interaction = "click second";
                }else if(cheapDirect.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    filter = "Cheapest Direct Flight";
                    dest = "";
                    otherInfo = "";
                    vector<string> final = getBest(filter, origin, dest, otherInfo);

                }else if(cheapIntl.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    filter = "Cheapest International Flight";
                    dest = "";
                    otherInfo = "";
                    vector<string> final = getBest(filter, origin, dest, otherInfo);

                }else if(cheapInMonth.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    filter = "Month";
                    dest = "";
                    otherInfo = ""; //FIXME and change to month input
                    vector<string> final = getBest(filter, origin, dest, otherInfo);

                }else if(minWBudget.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    //something else for budget input
                    filter = "Minimum Num Cities";
                    dest = "";
                    otherInfo = ""; //FIXME and put budget
                    vector<string> final = getBest(filter, origin, dest, otherInfo);

                }else if(checkDirect.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    filter = "Direct";
                    otherInfo = "";
                    vector<string> final = getBest(filter, origin, dest, otherInfo);

                }else if(getPass.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    filter = "Flight path";
                    otherInfo = "";
                    vector<string> final = getBest(filter, origin, dest, otherInfo);
                    //FIXME AND PASS FINAL VECTOR INTO BOARDING PASS WINDOW

                }


                else{

                    int totalClickX = window.mapPixelToCoords(mouse, mapView).x;
                    int totalClickY =  window.mapPixelToCoords(mouse, mapView).y;
                    //cout << totalClickX << ", " << totalClickY << endl;
                    placeHold = getCityFromClick(window, totalClickX, totalClickY);
                    //cout << placeHold << endl;
                    if(placeHold != "NA" && (interaction == "0")){
                        interaction = "confirm1";
                    }else if(placeHold != "NA" && interaction == "click second"){
                        interaction = "confirm2";
                    }


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
        //window.draw(promptBorder);
        putPromptsToScreen(window, interaction);
        //window.draw(select1);


        window.display();

    }
}



void TicketScreen::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Could not load font at: " << fontPath << std::endl;
        exit(EXIT_FAILURE);
    }
}

void TicketScreen::drawBoardingPass(const Flight flight) {
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


/*


// Entry point for the ticket booking system's main functionality.
void Ticket::run() {
    // Initialize the main window of the application with a specific size and title.
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flight Ticket Booking", sf::Style::Close);

    // Load the font from a file to ensure that all text rendered in the application uses this font.
    loadFont("arial.ttf");

    // Retrieve a list of available flights from data source.
    std::vector<Flight> availableFlights = ();

    // Check if the flight data is available. If not, log an error message and exit the function.
    if (availableFlights.empty()) {
        std::cerr << "No flights available at this time." << std::endl;
        return; // Early exit if no flights are available to display
    }

    // Variables for managing the state of selected flight.
    Flight selectedFlight;  // This variable will hold the details of the selected flight.
    int selectedIndex = -1; // This variable tracks the index of the selected flight in the vector.

    // Setup the header text at the top of the window to instruct the user.
    sf::Text header("Select a Flight:", font, 24);
    header.setPosition(50, 20);
    header.setFillColor(sf::Color::Black);

    // Create a vector to store the text elements for flight options displayed on the screen.
    std::vector<sf::Text> flightOptions;
    for (size_t i = 0; i < availableFlights.size(); i++) {
        
        //need helo w  formatted flight info string
        sf::Text option(availableFlights[i].(), font, 20); 
        option.setPosition(50, 70 + i * 30);
        option.setFillColor(sf::Color::Blue); // Initial color for unselected options.
        flightOptions.push_back(option);
    }

    // Set up a back button that allows the user to exit or go back to the previous menu.
    sf::Text backButton("Back", font, 20);
    backButton.setPosition(700, 550);
    backButton.setFillColor(sf::Color::Red);

    // Main event loop that runs as long as the window is open.
    while (window.isOpen()) {
        sf::Event event;
        // Poll for and process events.
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Close the window if the close event is triggered.
            }

            // Check for mouse movements to update hover effects on the flight options.
            if (event.type == sf::Event::MouseMoved) {
                for (auto& option : flightOptions) {
                    // Change color to a lighter shade when the mouse hovers over an option.
                    if (option.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                        option.setFillColor(sf::Color(100, 100, 255));
                    } else {
                        option.setFillColor(sf::Color::Blue); // Reset color when not hovered.
                    }
                }
            }

            // Handle mouse button presses to select a flight option.
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // Check if the back button is pressed.
                if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close(); // Close the window on back button click.
                    return;
                }

                // Determine which flight option was clicked.
                for (int i = 0; i < flightOptions.size(); i++) {
                    if (flightOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedIndex = i; // Update the selected index.
                        selectedFlight = availableFlights[i]; // Update the selected flight.
                        // Highlight the selected option by changing its color to green.
                        flightOptions[i].setFillColor(sf::Color::Green);
                        break;
                    }
                }
            }
        }

        // Clear the window and redraw all components.
        window.clear(sf::Color::White);
        window.draw(header);
        for (auto& option : flightOptions) {
            window.draw(option);
        }
        window.draw(backButton);

        // If a flight is selected, display its boarding pass.
        if (selectedIndex != -1) {
            drawBoardingPass(selectedFlight);
        }

        // Display the updated window contents.
        window.display();
    }
}

*/
