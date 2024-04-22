#include <iostream>
#include "FrontEnd.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include <vector>
using namespace std;


/*
This function is responsible for displaying the welcome screen of the Travel App using the SFML library. 
It sets up a window, loads necessary fonts and images (specifically a background image and the Arial font), 
and configures text and button elements with appropriate styles and positions. The function includes an interactive 
environment where it handles events such as mouse movement and clicks, checking if the mouse is over specific buttons 
and reacting to button presses to navigate to other parts of the app or exit. It also includes an animation feature 
with a circle that grows and shrinks continuously, adding a dynamic visual element to the welcome screen.

*/


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
    sf::Text welcomeText("Welcome to DSA Project 3! By Eneida Escobar, Marielle Doenges, and Maggie Snead", font, 30);
    welcomeText.setFillColor(sf::Color::Black);
    welcomeText.setPosition(50, 50);

    // Style the buttons with a more geographical theme
    sf::RectangleShape mapButton(sf::Vector2f(250, 70));
    mapButton.setPosition(275, 150);
    mapButton.setFillColor(sf::Color(0, 102, 204, 150)); // Semi-transparent blue
    sf::Text mapButtonText("Explore the Map", font, 25);
    mapButtonText.setFillColor(sf::Color::White);
    mapButtonText.setPosition(285, 165);


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


/*
Populate the map with location pins from a CSV file containing city coordinates. 
It opens the file, reads coordinates line by line, and creates a sprite for each set of 
coordinates using a preloaded pin image. These sprites are then stored in the cityPts vector 
for later use in rendering on the map
*/
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

/* Detects if a user's mouse click on the map corresponds to a city by checking if the click's 
coordinates intersect with any of the city pin sprites' boundaries. If a match is found, it returns 
the city's name; otherwise, it returns "NA" to indicate no city was selected at the click location.

*/

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


/*
Allows for dynamically adding new city locations to the map. It appends the coordinates of a new city 
to the "cityCoordinates.csv" file, which can be used to update the map's data set and potentially add 
new pins during runtime or subsequent sessions.
*/

void MapScreen::writeCityLocations(int x, int y ) {
    ofstream file;
    file.open("cityCoordinates.csv", ios_base::app);
    file << x << endl << y << endl;
}

MapScreen::MapScreen() {
    map.setTexture(mapTexture);
    map.setOrigin(0,0);

    font.loadFromFile("arial.ttf");

    //map movement buttons
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

    //pin set up
    pinT.loadFromFile("images/red_pin.png");
    loadPins();

    //input / selection validation
    yesT.loadFromFile("images/check.jpg");
    yes.setTexture(yesT);
    yes.setPosition(1250,640);

    noT.loadFromFile("images/X.jpg");
    no.setTexture(noT);
    no.setPosition(1300, 640);

    //interaction commands
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

    //otions if one flight selected
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
    setTextRight(cheapDirect, 0, 0);

    cheapIntl.setString("Find the cheapest international flight from here");
    cheapIntl.setFillColor(sf::Color::Black);
    cheapIntl.setStyle(sf::Text::Bold);
    cheapIntl.setFont(font);
    cheapIntl.setCharacterSize(25);


    cheapInMonth.setString("Find the cheapest flight in a month of your choice from here");
    cheapInMonth.setFillColor(sf::Color::Black);
    cheapInMonth.setStyle(sf::Text::Bold);
    cheapInMonth.setFont(font);
    cheapInMonth.setCharacterSize(25);


    minWBudget.setString("Find the minimum number of cities you can travel to within a certain budget from here.");
    minWBudget.setFillColor(sf::Color::Black);
    minWBudget.setStyle(sf::Text::Bold);
    minWBudget.setFont(font);
    minWBudget.setCharacterSize(25);


    //options if two flights selected
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

    //restart
    restart.setString("RESTART");
    restart.setFillColor(sf::Color::Red);
    restart.setStyle(sf::Text::Bold);
    restart.setFont(font);
    restart.setCharacterSize(25);
    setTextRight(restart, 155, 480);

    restartT.loadFromFile("images/prompt.jpg");
    restartBorder.setTexture(restartT);
    restartBorder.setPosition(30, 450);
    restartBorder.setScale(0.9, 0.6);

//    sf::Text plus100, plus500, plus1000, minus100, minus500, minus1000 budget, budgetPrompt;
//    sf::Text monthPrompt, potentialMonth, next, prev;

    //budget input
    plus100.setString("+100");
    plus100.setFont(font);
    plus100.setCharacterSize(25);
    plus100.setFillColor(sf::Color::Black);
    plus100.setStyle(sf::Text::Bold);

    plus500.setString("+500");
    plus500.setFont(font);
    plus500.setCharacterSize(25);
    plus500.setFillColor(sf::Color::Black);
    plus500.setStyle(sf::Text::Bold);

    plus1000.setString("+1000");
    plus1000.setFont(font);
    plus1000.setCharacterSize(25);
    plus1000.setFillColor(sf::Color::Black);
    plus1000.setStyle(sf::Text::Bold);

    minus100.setString("-100");
    minus100.setFont(font);
    minus100.setCharacterSize(25);
    minus100.setFillColor(sf::Color::Black);
    minus100.setStyle(sf::Text::Bold);

    minus500.setString("-500");
    minus500.setFont(font);
    minus500.setCharacterSize(25);
    minus500.setFillColor(sf::Color::Black);
    minus500.setStyle(sf::Text::Bold);

    minus1000.setString("-1000");
    minus1000.setFont(font);
    minus1000.setCharacterSize(25);
    minus1000.setFillColor(sf::Color::Black);
    minus1000.setStyle(sf::Text::Bold);

    budget.setString("1500");
    budget.setFont(font);
    budget.setCharacterSize(25);
    budget.setFillColor(sf::Color::Black);
    budget.setStyle(sf::Text::Bold);

    budgetPrompt.setString("Select your budget:  $");
    budgetPrompt.setFont(font);
    budgetPrompt.setCharacterSize(25);
    budgetPrompt.setFillColor(sf::Color::Black);
    budgetPrompt.setStyle(sf::Text::Bold);

    monthPrompt.setString("Select your month to travel in: ");
    monthPrompt.setFont(font);
    monthPrompt.setCharacterSize(25);
    monthPrompt.setFillColor(sf::Color::Black);
    monthPrompt.setStyle(sf::Text::Bold);

    potentialMonth.setString(months[0]);
    potentialMonth.setFont(font);
    potentialMonth.setCharacterSize(25);
    potentialMonth.setFillColor(sf::Color::Black);
    potentialMonth.setStyle(sf::Text::Bold);

    next.setString("next month");
    next.setFont(font);
    next.setCharacterSize(25);
    next.setFillColor(sf::Color::Black);
    next.setStyle(sf::Text::Bold);

    prev.setString("previous month");
    prev.setFont(font);
    prev.setCharacterSize(25);
    prev.setFillColor(sf::Color::Black);
    prev.setStyle(sf::Text::Bold);

}
void MapScreen::moveAllPrompts() {
    setTextRight(select1, 0,0);
    setTextRight(youSelected, 0,0);
    setTextRight(optionList, 0,0);
    setTextRight(selectAnother, 0,0);
    setTextRight(select2, 0,0);
    setTextRight(cheapDirect, 0,0);
    setTextRight(cheapIntl, 0,0);
    setTextRight(cheapInMonth, 0,0);
    setTextRight(minWBudget, 0,0);
    setTextRight(checkDirect, 0,0);
    setTextRight(getPass, 0,0);
    setTextRight(plus100, 0,0);
    setTextRight(plus500, 0,0);
    setTextRight(plus1000, 0,0);
    setTextRight(minus100, 0,0);
    setTextRight(minus500, 0,0);
    setTextRight(minus1000, 0,0);
    setTextRight(budget, 0,0);
    setTextRight(budgetPrompt, 0,0);
    setTextRight(monthPrompt, 0,0);
    setTextRight(potentialMonth, 0,0);
    setTextRight(next, 0,0);
    setTextRight(prev, 0,0);
}



void MapScreen::moveTextLocation(string interaction){
    if(interaction == "0"){
        setTextRight(select1, 1450, 600);
    }else if(interaction == "confirm1" || interaction == "confirm2"){
        setTextRight(youSelected, 1450, 600);
        yes.setPosition(1250,640);
        no.setPosition(1300, 640);
    }else if(interaction == "1"){
        setTextRight(optionList, 1450, 500);
        setTextRight(selectAnother, 1450, 540);
        setTextRight(cheapDirect, 1450, 570);
        setTextRight(cheapIntl, 1450, 600);
        setTextRight(cheapInMonth, 1450, 630);
        setTextRight(minWBudget, 1450, 660);
    }
    else if(interaction == "2"){
        setTextRight(optionList, 1450, 500);
        setTextRight(checkDirect, 1450, 540);
        setTextRight(getPass, 1450, 570);

    }else if(interaction == "click second"){
        setTextRight(select2, 1450, 600);
    }else if(interaction == "create budget"){
        plus100.setPosition(1200, 600);
        plus500.setPosition(1300, 600);
        plus1000.setPosition(1400, 600);
        minus100.setPosition(1200, 650);
        minus500.setPosition(1300, 650);
        minus1000.setPosition(1400, 650);
        budget.setPosition(1300, 550);
        budgetPrompt.setPosition(1240, 555);
        yes.setPosition(1350,530);
    }else if(interaction == "select month"){
        monthPrompt.setPosition(1200, 555);
        potentialMonth.setPosition(1350, 555);
        next.setPosition(1380, 590);
        prev.setPosition(1380, 630);
        yes.setPosition(1400,530);
    }
}


/*

This constructor sets up the map screen, initializing the map view with various control buttons for navigation 
(zoom in/out, directional movement), and loads the textures for these controls from files. It also sets up 
interface elements for user interactions such as confirming city selections and options for planning travel, 
including budgets and selecting travel months.*/

void MapScreen::putPromptsToScreen(sf::RenderWindow &window, string interactionStatus) {
    moveAllPrompts();
    moveTextLocation(interactionStatus);

    if(interactionStatus == "0"){
        window.draw(select1);

    }else if(interactionStatus == "confirm1" || interactionStatus == "confirm2"){
        youSelected.setString("Confirm your selection of: " + placeHold);
        window.draw(youSelected);
        window.draw(yes);
        window.draw(no);

    }else if(interactionStatus == "1"){
        window.draw(optionList);
        window.draw(selectAnother);
        window.draw(cheapDirect);
        window.draw(cheapIntl);
        window.draw(cheapInMonth);
        window.draw(minWBudget);

    }else if(interactionStatus == "2"){
        checkDirect.setString("Check for a direct flight between: " + origin + " and " + dest);
        getPass.setString("Print my boarding pass for: " + origin + " to " + dest);

        window.draw(optionList);
        window.draw(checkDirect);
        window.draw(getPass);

    }else if(interactionStatus == "click second"){
        window.draw(select2);

    }else if(interactionStatus == "create budget"){
        window.draw(plus100);
        window.draw(plus500);
        window.draw(plus1000);
        window.draw(minus100);
        window.draw(minus500);
        window.draw(minus1000);
        window.draw(budget);
        window.draw(budgetPrompt);
        window.draw(yes);

    }else if(interactionStatus == "select month"){
        window.draw(monthPrompt);
        window.draw(potentialMonth);
        window.draw(next);
        window.draw(prev);
        window.draw(yes);
    }
}

vector<string> MapScreen::displayWindow() {
    Graph backEnd;
    backEnd.readCSVFile("proj3DataTest.csv");
    sf::RenderWindow window(sf::VideoMode(1494,700), "testing", sf::Style::Close);

    mapView.setCenter(window.getSize().x/2,window.getSize().y/2);
    mapView.setSize(window.getSize().x, window.getSize().y);

    buttonView.setCenter(window.getSize().x/2,window.getSize().y/2);
    buttonView.setSize(window.getSize().x, window.getSize().y);
    int shiftL = 0, shiftR = 0, shiftU = 0, shiftD = 0, zIn = 0, zOut = 0;

    vector<string> toReturn;

    string interaction = "0";
    int monthIdx = 0;

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return toReturn;
            }
            if(event.type == sf::Event::MouseButtonReleased){
                sf::Vector2i mouse;
                mouse = sf::Mouse::getPosition(window);
                int clickX = mouse.x;
                int clickY = mouse.y;

                //cout << clickX << ", " << clickY << endl;
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
                    }else if(interaction == "select month"){
                        filter = "Month";
                        dest = "";
                        otherInfo = potentialMonth.getString();
                        vector<string> final = backEnd.getBest(filter, origin, dest, otherInfo);
                    }else if(interaction == "create budget"){
                        filter = "Minimum Num Cities";
                        dest = "";
                        otherInfo = budget.getString();
                        vector<string> final = backEnd.getBest(filter, origin, dest, otherInfo);
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
                    vector<string> final = backEnd.getBest(filter, origin, dest, otherInfo);

                }else if(cheapIntl.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    filter = "Cheapest International Flight";
                    dest = "";
                    otherInfo = "";
                    vector<string> final = backEnd.getBest(filter, origin, dest, otherInfo);

                }else if(cheapInMonth.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    interaction = "select month";
                }else if(minWBudget.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    //something else for budget input
                    interaction = "create budget";
                }else if(checkDirect.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    filter = "Direct";
                    otherInfo = "";
                    vector<string> final = backEnd.getBest(filter, origin, dest, otherInfo);

                }else if(getPass.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    filter = "Flight path";
                    otherInfo = "";
                    vector<string> final = backEnd.getBest(filter, origin, dest, otherInfo);

                    for(auto item : final){
                        cout << item << endl;
                    }
                    //FIXME AND PASS FINAL VECTOR INTO BOARDING PASS WINDOW
                    window.close();
                    return final;

                }else if(restartBorder.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    interaction = "0";
                    origin = "";
                    dest = "";
                    budget.setString("1500");
                }else if(next.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    monthIdx += 1;
                    if(monthIdx == 12){
                        monthIdx = 0;
                    }
                    potentialMonth.setString(months[monthIdx]);
                }else if(prev.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    monthIdx -= 1;
                    if(monthIdx == -1){
                        monthIdx = 11;
                    }
                    potentialMonth.setString(months[monthIdx]);
                }else if(plus100.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    string temp = budget.getString();
                    int newBud = stoi(temp) + 100;
                    budget.setString(to_string(newBud));
                }else if(plus500.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    string temp = budget.getString();
                    int newBud = stoi(temp) + 500;
                    budget.setString(to_string(newBud));
                }else if(plus1000.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    string temp = budget.getString();
                    int newBud = stoi(temp) + 1000;
                    budget.setString(to_string(newBud));
                }else if(minus100.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    string temp = budget.getString();
                    int newBud = stoi(temp) - 100;
                    budget.setString(to_string(newBud));
                }else if(minus500.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    string temp = budget.getString();
                    int newBud = stoi(temp) - 500;
                    budget.setString(to_string(newBud));
                }else if(minus1000.getGlobalBounds().contains(window.mapPixelToCoords(mouse))){
                    string temp = budget.getString();
                    int newBud = stoi(temp) - 1000;
                    budget.setString(to_string(newBud));
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
        window.draw(restartBorder);
        window.draw(restart);
        putPromptsToScreen(window, interaction);

        window.display();

    }
}


/*
The constructor for the Ticket class initializes an instance with detailed information about a flight or a 
route when direct flights are unavailable. It configures text objects for displaying all relevant flight information 
or alternative routes, setting up the initial display state for showing a flight ticket or alternative travel options.
*/

Ticket::Ticket(vector<std::string> yourInformation) {
    font.loadFromFile("arial.ttf");
    if(yourInformation[0] == "NA"){

        name.setString("No direct flight available. No boarding pass to create.");
        name.setFont(font);
        name.setFillColor(sf::Color::Black);
        setText(name, 600, 100);

        NAmessage.setString("However, you can fly from " + yourInformation[1]);
        NAmessage.setFont(font);
        NAmessage.setFillColor(sf::Color::Black);
        setText(NAmessage, 600, 150);
        for(int i = 2; i < yourInformation.size(); i++){
            otherCities.push_back(yourInformation[i]);
        }

    }else {
        name.setString("Marielle, Maggie and Enedia");
        name.setFont(font);
        name.setFillColor(sf::Color::Black);

        flightNum.setString(yourInformation[0]);
        flightNum.setFont(font);
        flightNum.setFillColor(sf::Color::Black);

        originCity.setString(yourInformation[1]);
        originCity.setFont(font);
        originCity.setFillColor(sf::Color::Black);

        originCountry.setString(yourInformation[2]);
        originCountry.setFont(font);
        originCountry.setFillColor(sf::Color::Black);

        destCity.setString(yourInformation[3]);
        destCity.setFont(font);
        destCity.setFillColor(sf::Color::Black);

        destCountry.setString(yourInformation[4]);
        destCountry.setFont(font);
        destCountry.setFillColor(sf::Color::Black);

        month.setString(yourInformation[5]);
        month.setFont(font);
        month.setFillColor(sf::Color::Black);

        date.setString(yourInformation[6]);
        date.setFont(font);
        date.setFillColor(sf::Color::Black);

        depTime.setString(yourInformation[7]);
        depTime.setFont(font);
        depTime.setFillColor(sf::Color::Black);

        dur.setString(yourInformation[8]);
        dur.setFont(font);
        dur.setFillColor(sf::Color::Black);

        dist.setString(yourInformation[9]);
        dist.setFont(font);
        dist.setFillColor(sf::Color::Black);

        TZdiff.setString(yourInformation[10]);
        TZdiff.setFont(font);
        TZdiff.setFillColor(sf::Color::Black);

        price.setString(yourInformation[11]);
        price.setFont(font);
        price.setFillColor(sf::Color::Black);

    }

}

/*Handles the display of alternative route information when a direct flight is not available. 
It sequentially displays cities that can be traveled through as part of an alternative route, 
updating the position of each text element dynamically to ensure clarity and readability.*/


void Ticket::printAltRoute(sf::RenderWindow& window) {
    int begin = 180;
    originCity.setFillColor(sf::Color::Black);
    originCity.setFont(font);
    for(int i = 0; i < otherCities.size(); i++){
        originCity.setString("to " + otherCities[i]);
        setText(originCity, 600, begin);
        begin += 40;
        window.draw(originCity);
    }
}


/*
This function is the main loop for displaying the ticket information in a window. It manages the window's event handling 
and updates the display to show either direct flight details or alternative route options, refreshing the window contents 
continuously until the window is closed.
*/
void Ticket::draw() {
    // Initialize the main window of the application with a specific size and title.
    sf::RenderWindow window(sf::VideoMode(1200, 500), "Flight Ticket Booking", sf::Style::Close);

    // Main event loop that runs as long as the window is open.
    while (window.isOpen()) {
        sf::Event event;
        // Poll for and process events.
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

//        originCity, originCountry, destCity, destCountry, price, dist,
//                dur, TZdiff, month, date, depTime, intl, flightNum, NAmessage;
        // Clear the window and draw all components.
        window.clear(sf::Color::White);
        window.draw(name);

        if(otherCities.size() != 0){
            printAltRoute(window);
            window.draw(NAmessage);
        }else {
            window.draw(originCity);
            window.draw(originCountry);
            window.draw(destCity);
            window.draw(destCountry);
            window.draw(price);
            window.draw(dist);
            window.draw(dur);
            window.draw(TZdiff);
            window.draw(month);
            window.draw(date);
            window.draw(depTime);
            window.draw(flightNum);
        }

        window.display();
    }
}

