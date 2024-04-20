#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <unordered_map>
#include "Graph.h"
using namespace std;

struct MapScreen{
    sf::Texture mapTexture = TextureManager::getTexture("physical-world-map");
    sf::Texture zoomInT;
    sf::Texture zoomOutT;
    sf::Texture pinT;
    sf::Texture upT;

    sf::Sprite map;
    sf::Sprite zoomIn;
    sf::Sprite zoomOut;
    sf::Sprite pin;

    sf::View view;
//
//    unordered_map<string, pair<int, int>> cityLocations = {{"Tampa", {122, 142}}, {"Gainesville", {}}, {"Paris", 2}, {"London", 3}, {"New York", 4},
//                                                           {"Miami", 5}, {"Washington DC", 6}, {"Seattle", 7}, {"Las Vegas", 8}, {"Los Angeles", 9},
//                                                           {"Houston", 10}, {"Austin", 11}, {"Dallas", 12}, {"Atlanta", 13}, {"Charleston", 14},
//                                                           {"Bonn", 15}, {"Buenos Aires", 16}, {"Lima", 17}, {"Mar Del Plata", 18}, {"Okinawa", 19},
//                                                           {"Madrid", 20}, {"Valencia", 21}, {"Sevilla", 22}, {"Copenhagen", 23}, {"Stockholm", 24},
//                                                           {"Oslo", 25}, {"Shanghai", 26}, {"Dubai", 27}, {"Rome", 28}, {"Milan", 29},
//                                                           {"Nice", 30}, {"Frankfurt", 31},  {"Berlin", 32}, {"Moscow", 33}, {"Sao Paulo", 34},
//                                                           {"Mexico City", 35}, {"Chicago", 36}, {"Toronto", 37}, {"Quebec", 38}, {"Kansas City", 39},
//                                                           {"Juneau", 40}, {"Mumbai", 41}, {"New Dehli", 42}, {"Bangkok", 43}, {"Hong Kong", 44},
//                                                           {"Sydney", 45}, {"Melbourne", 46}, {"Beijing", 47}, {"Taipei", 48}, {"Seoul", 49},
//                                                           {"Nagasaki", 50}, {"Tokyo", 51}, {"Baghdad", 52}, {"Jerusalem", 53}, {"Istanbul", 54},
//                                                           {"Athens", 55}, {"Budapest", 56}, {"Vienna", 57}, {"Sofia", 58}, {"Kyiv",59},
//                                                           {"Warsaw", 60}, {"Minsk", 61}, {"Amsterdam", 62}, {"Zurich", 63}, {"Brussels", 64},
//                                                           {"St. Tropez", 65}, {"Naples", 66}, {"Ibiza", 67},  {"Tunis", 68}, {"Lisbon", 69},
//                                                           {"Dublin", 70}, {"Glasgow", 71},  {"Edinburgh", 72}, {"Malmo", 73}, {"Helsinki", 74},
//                                                           {"Bergen", 75}, {"St. Petersburg", 76}, {"Reykjavik", 77}, {"Panama City", 78}, {"Medellin", 79},
//                                                           {"Bogota", 80}, {"Quito", 81}, {"Caracas", 82}, {"Brasilia", 83}, {"Santiago", 84},
//                                                           {"Montevideo", 85}, {"San Juan", 86}, {"Havana", 87}, {"Cairo", 88}, {"Marrakesh", 89},
//                                                           {"Abuja", 90}, {"Nairobi", 91}, {"Zanzibar", 92}, {"Cape Town", 93}, {"Prague",94},
//                                                           {"San Fransisco", 95}, {"Honolulu", 96}, {"Santorini", 97}, {"Madeira", 98}, {"Oporto", 99}};
//

    MapScreen();
    void displayWindow();
};

struct Ticket{
    sf::RenderWindow window;
    sf::Font font;
    sf::Color backgroundColor;
    sf::Color textColor;
    sf::Color outlineColor;

    Ticket(int width, int height, const std::string& title);
    void run();
    void loadFont(const std::string& fontPath);
    void drawBoardingPass(const Flight& flight);
    void handleUserInput(std::vector<Flight>& availableFlights, Flight& selectedFlight);
};