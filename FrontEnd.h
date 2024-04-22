//#include <SFML/Graphics.hpp>
//#include "TextureManager.h"
//#include <unordered_map>
//#include "Graph.h"
//#include <vector>
//#include <fstream>
//using namespace std;
//
//
//struct WelcomeScreen{
//    string showWelcomeScreen();
//};
//
//
//struct MapScreen{
//    sf::Texture mapTexture = TextureManager::getTexture("physical-world-map");
//    sf::Texture zoomInT, zoomOutT, pinT;
//    sf::Texture upT, dT, RT, LT;
//    sf::Texture yesT, noT;
//    sf::Texture promptT;
//
//    sf::Sprite map, zoomIn, zoomOut, pin, pin2, up, down, left, right, yes, no;
//
//    sf::View mapView, buttonView;
//
//    sf::Font font;
//    sf::Sprite promptBorder;
//
//    sf::Text select1;
//    sf::Text youSelected;
//    sf::Text optionList;
//    sf::Text selectAnother;
//    sf::Text select2;
//    sf::Text cheapDirect;
//    sf::Text cheapIntl;
//    sf::Text cheapInMonth;
//    sf::Text minWBudget;
//    sf::Text checkDirect;
//    sf::Text getPass;
//
//    string origin, dest, placeHold;
//
//    vector<sf::Sprite> cityPts;
//    vector<string> cityNames = {"Tampa", "Gainesville", "Paris", "London", "New York",
//                                "Miami", "Washington DC", "Seattle", "Las Vegas", "Los Angeles",
//                                "Houston", "Austin", "Dallas", "Atlanta", "Charleston",
//                                "Bonn", "Buenos Aires", "Lima", "Mar Del Plata", "Okinawa",
//                                "Madrid", "Valencia", "Sevilla", "Copenhagen", "Stockholm",
//                                "Oslo", "Shanghai", "Dubai", "Rome", "Milan",
//                                "Nice", "Frankfurt", "Berlin", "Moscow", "Sao Paulo",
//                                "Mexico City", "Chicago", "Toronto", "Quebec", "Kansas City",
//                                "Juneau", "Mumbai", "New Dehli", "Bangkok", "Hong Kong",
//                                "Sydney", "Melbourne", "Beijing", "Taipei", "Seoul",
//                                "Nagasaki", "Tokyo", "Baghdad", "Jerusalem", "Istanbul",
//                                "Athens", "Budapest", "Vienna", "Sofia", "Kyiv",
//                                "Warsaw", "Minsk", "Amsterdam", "Zurich", "Brussels",
//                                "St. Tropez", "Naples", "Ibiza", "Tunis", "Lisbon",
//                                "Dublin", "Glasgow", "Edinburgh", "Malmo", "Helsinki",
//                                "Bergen", "St. Petersburg", "Reykjavik", "Panama City", "Medellin",
//                                "Bogota", "Quito", "Caracas", "Brasilia", "Santiago",
//                                "Montevideo", "San Juan", "Havana", "Cairo", "Marrakesh",
//                                "Abuja", "Nairobi", "Zanzibar", "Cape Town", "Prague",
//                                "San Fransisco", "Honolulu", "Santorini", "Madeira", "Oporto"};
//
//
//    MapScreen();
//    void displayWindow();
//    string getCityFromClick(sf::RenderWindow& window, int x, int y);
//    void loadPins();
//    void writeCityLocations(int x, int y);
//    void setText(sf::Text &text, float x, float y){
//        sf::FloatRect textRect = text.getLocalBounds();
//        text.setOrigin(textRect.left + textRect.width/2.0f,
//                       textRect.top + textRect.height/2.0f);
//        text.setPosition(sf::Vector2f(x, y));
//    }
//    void setTextRight(sf::Text &text, float x, float y){
//        sf::FloatRect textRect = text.getLocalBounds();
//        text.setOrigin(textRect.width, textRect.height);
//        text.setPosition(sf::Vector2f(x, y));
//    }
//    void putPromptsToScreen(sf::RenderWindow& window, string interactionStatus);
//};
//
//struct TicketScreen{
//    sf::RenderWindow window;
//    sf::Font font;
//    sf::Color backgroundColor = sf::Color::White;
//    sf::Color textColor = sf::Color::Black;
//    sf::Color outlineColor = sf::Color::Black;
//
//    TicketScreen();
//    void loadFont(const std::string& fontPath);
//    void drawBoardingPass(const Flight flight);
//    void setText(sf::Text &text, float x, float y){
//        sf::FloatRect textRect = text.getLocalBounds();
//        text.setOrigin(textRect.left + textRect.width/2.0f,
//                       textRect.top + textRect.height/2.0f);
//        text.setPosition(sf::Vector2f(x, y));
//    }
//};





#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <unordered_map>
#include "Graph.h"
#include <vector>
#include <fstream>
using namespace std;


struct WelcomeScreen{
    string showWelcomeScreen();
};


struct MapScreen{
    sf::Texture mapTexture = TextureManager::getTexture("physical-world-map");
    sf::Texture zoomInT, zoomOutT, pinT;
    sf::Texture upT, dT, RT, LT;
    sf::Texture yesT, noT;
    sf::Texture restartT;

    sf::Sprite map, zoomIn, zoomOut, pin, pin2, up, down, left, right, yes, no;

    sf::View mapView, buttonView;

    sf::Font font;
    sf::Sprite restartBorder;

    sf::Text select1;
    sf::Text youSelected;
    sf::Text optionList;
    sf::Text selectAnother;
    sf::Text select2;
    sf::Text cheapDirect;
    sf::Text cheapIntl;
    sf::Text cheapInMonth;
    sf::Text minWBudget;
    sf::Text checkDirect;
    sf::Text getPass;
    sf::Text restart;
    sf::Text plus100, plus500, plus1000, minus100, minus500, minus1000, budget, budgetPrompt;
    sf::Text monthPrompt, potentialMonth, next, prev;
    sf::Text output;

    string origin, dest, placeHold, otherInfo, filter;

    vector<sf::Sprite> cityPts;
    vector<string> cityNames = {"Tampa", "Gainesville", "Paris", "London", "New York",
                                "Miami", "Washington DC", "Seattle", "Las Vegas", "Los Angeles",
                                "Houston", "Austin", "Dallas", "Atlanta", "Charleston",
                                "Bonn", "Buenos Aires", "Lima", "Mar Del Plata", "Okinawa",
                                "Madrid", "Valencia", "Sevilla", "Copenhagen", "Stockholm",
                                "Oslo", "Shanghai", "Dubai", "Rome", "Milan",
                                "Nice", "Frankfurt", "Berlin", "Moscow", "Sao Paulo",
                                "Mexico City", "Chicago", "Toronto", "Quebec", "Kansas City",
                                "Juneau", "Mumbai", "New Dehli", "Bangkok", "Hong Kong",
                                "Sydney", "Melbourne", "Beijing", "Taipei", "Seoul",
                                "Nagasaki", "Tokyo", "Baghdad", "Jerusalem", "Istanbul",
                                "Athens", "Budapest", "Vienna", "Sofia", "Kyiv",
                                "Warsaw", "Minsk", "Amsterdam", "Zurich", "Brussels",
                                "St. Tropez", "Naples", "Ibiza", "Tunis", "Lisbon",
                                "Dublin", "Glasgow", "Edinburgh", "Malmo", "Helsinki",
                                "Bergen", "St. Petersburg", "Reykjavik", "Panama City", "Medellin",
                                "Bogota", "Quito", "Caracas", "Brasilia", "Santiago",
                                "Montevideo", "San Juan", "Havana", "Cairo", "Marrakesh",
                                "Abuja", "Nairobi", "Zanzibar", "Cape Town", "Prague",
                                "San Fransisco", "Honolulu", "Santorini", "Madeira", "Oporto"};
    vector<string> months = {"January", "Febuary", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December"};


    MapScreen();
    void displayWindow();
    string getCityFromClick(sf::RenderWindow& window, int x, int y);
    void loadPins();
    void writeCityLocations(int x, int y);
    void setText(sf::Text &text, float x, float y){
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(x, y));
    }
    void setTextRight(sf::Text &text, float x, float y){
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.width, textRect.height);
        text.setPosition(sf::Vector2f(x, y));
    }
    void moveAllPrompts();
    void moveTextLocation(string interaction);
    void putPromptsToScreen(sf::RenderWindow& window, string interactionStatus);
};


struct Ticket{
    sf::RenderWindow window;
    sf::Font font;
    sf::Color backgroundColor = sf::Color::White;
    sf::Color textColor = sf::Color::Black;
    sf::Color outlineColor = sf::Color::Black;

    sf::Texture barCodeT;
    sf::Sprite barCode;

    sf::Text name;
    sf::Text originCity;
    sf::Text originCountry;
    sf::Text destCity;
    sf::Text destCountry;

    Ticket(vector<string> yourInformation);
    void loadFont(const std::string& fontPath);
    void drawBoardingPass(const Flight flight);
    void setText(sf::Text &text, float x, float y){
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(x, y));
    }
    void run();
};