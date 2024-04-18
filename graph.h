#pragma once
#include <string>
#include <map>
#include <set>

using namespace std;

struct city{    //FIXME not sure if needed
    string name, country;
    city(string &cityName, string &countryName) : name(cityName), country(countryName){}
};

// Represents an individual graph, holding all relevant details and providing methods for accessing these details.
struct flight {
    string originCity;    // The departure city of the graph.
    string destinationCity;   // The destination city of the graph.
    string time;     // Descriptive time of departure (e.g., "Morning", "Afternoon", "Evening").
    string month;
    string date;
    string flightNumber;       //how we will distinguish different flights
    int distance;
    int price;    // Cost of the graph in USD.
    int duration; // Duration of the graph in hours
    float timeDiff;   //time difference between two cities
    bool intl;

    //constructor of our flight object
    flight(string &cityFrom, string &cityTo, int &priceGiven, int &distanceGiven,
            int &durationGiven, float &timeZoneDiff, string &monthGiven, string &dateGiven, string &departureTime,
            bool &international, string &number):

            originCity(cityFrom), destinationCity(cityTo), price(priceGiven), distance(distanceGiven),
            duration(durationGiven), time(departureTime), month(monthGiven), date(dateGiven),
            timeDiff(timeZoneDiff), flightNumber(number), intl(international)
            {}

};

class MarGraph{

    vector<string> cityNames = {"Tampa", "Gainesville", "Paris", "London", "New York",
                                "Miami", "Washington DC", "Seattle", "Las Vegas", "Los Angeles",
                                "Houston", "Austin", "Dallas", "Atlanta", "Charleston",
                                "Bonn", "Buenos Aires", "Lima", "Mar Del Plata", "Okinawa",
                                "Madrid", "Valencia", "Sevilla", "Copenhagen", "Stockholm",
                                "Oslo", "Shanghai", "Dubai", "Rome", "Milan",
                                "Nice", "Frankfurt", "Berlin", "Moscow", "Sao Paolo",
                                "Mexico City", "Chicago", "Toronto", "Quebec", "Kansas City",
                                "Juneau", "Mumbai", "New Dehli", "Bangkok", "Hong Kong",
                                "Sydney", "Melbourne", "Beijing", "Taipei", "Seoul",
                                "Nagasaki", "Tokyo", "Baghdad", "Jerusalem", "Istanbul",
                                "Athens", "Budapest", "Vienna", "Sofia", "Kyiv", "Warsaw",
                                "Minsk", "Amsterdam", "Zurich", "Brussels", "St. Tropez",
                                "Naples", "Ibiza", "Tunis", "Lisbon", "Dublin",
                                "Glasgow", "Edinburgh", "Malmo", "Helsinki", "Bergen",
                                "St. Petersburg", "Reykjavik", "Panama City", "Medellin",
                                "Bogota", "Quito", "Caracas", "Brasilia", "Santiago",
                                "Montevideo", "San Juan", "Havana", "Cairo", "Marrakesh",
                                "Abuja", "Nairobi", "Zanzibar", "Cape Town", "Prague",
                                "San Fransisco", "Honolulu", "Santorini", "Madeira", "Oporto"};
    vector<vector<flight>> matrix;

public:
    int& operator[](string cityName){

    }

};

class Graph{
private:
    set<string> cities;     //FIXME not necessarily needed
    map<string, flight*> flightPair;        //maps a specific flight number with a specific flight
    string g[100][100] = {};     //graph representation of matrix FIXME initialize all matrix entries with " " our graph map will store graph numbers

    string cheapestDirect(string &origin);     //given a starting city, returns cheapest direct flight number
    string directExists(string &origin, string &dest);        //returns flightNum if a direct graph exists between two cities
    string flightMonth();        //returns the graph between two places in a certain month if it exists, else just returns null

    bool international(string& flightNum);    //returns if the graph is international or not
    city* createCityHelper(string &cityName, string &countryName);
    flight* createFlightHelper(string &cityFrom, string &cityTo, string &price,string &distance, string &duration, string &timeZoneDiff,
                         string &month, string &date, string &departureTime, string &international, string &flightNum);    //create map helper

public:
    flight* current;
    city* myCity;

    // Getter methods to expose private properties in a controlled manner.
    string getOriginCity() const;
    string getDestinationCity() const;
    int getPrice() const;
    int getDuration() const;
    int getStops() const;
    string getTimeOfDay() const;

    void createMap(string cityFrom, string countryFrom, string cityTo, string countryTo,
                   string price,string distance, string duration, string timeZoneDiff,
                   string month, string date, string departureTime, string international, string flightNum); //creating actual map

    void getBest(string& filter, string& origin, string& dest);        //returns the best flight based on the filter passed in
    void print(string& filter, string& flightNum); //prints the graph based off of filter and the best graph
};