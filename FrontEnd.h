#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <unordered_map>
#include "Graph.h"
#include <vector>
#include <fstream>
using namespace std;

struct MapScreen{
    sf::Texture mapTexture = TextureManager::getTexture("physical-world-map");
    sf::Texture zoomInT, zoomOutT, pinT;
    sf::Texture upT, dT, RT, LT;

    sf::Sprite map, zoomIn, zoomOut, pin, pin2, up, down, left, right;

    sf::View mapView, buttonView;

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


    MapScreen();
    void displayWindow();
    string getCityFromClick(sf::RenderWindow& window, int x, int y);
    void loadPins();
    void writeCityLocations(int x, int y);
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