#pragma once
#include <string>
#include <map>

using namespace std;

struct city{    //FIXME not sure if needed
    string name, country, TZ;
    //keep track of graph objects that leave this city to go to another city
    //thinking a vector
    //keep track of graph objects that come into this city from another city
    //thinking a vector
};

// Represents an individual graph, holding all relevant details and providing methods for accessing these details.
struct flight {
    string originCity;    // The departure city of the graph.
    string destinationCity;   // The destination city of the graph.
    int price;    // Cost of the graph in USD.
    int duration; // Duration of the graph in hours
    int stops;    // Number of stops the graph makes.
    string timeOfDay;     // Descriptive time of departure (e.g., "Morning", "Afternoon", "Evening").
    string month;
    float timeDiff;   //time difference between two cities
    string flightNumber;       //how we will distinguish different flights

    //constructor of our graph object
    flight(string& number) : originCity(""), destinationCity(""), price(0), duration(0), stops(0), timeOfDay(""), month(""), timeDiff(0), flightNumber(number){}

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
    map<string, flight> flightPair;        //maps a specific graph number with a specific graph
    string graph [100][100] = {};     //graph representation of matrix FIXME initialize all matrix entries with " " our graph map will store graph numbers

public:
    flight current;
    // Getter methods to expose private properties in a controlled manner.
    string getOriginCity() const;
    string getDestinationCity() const;
    int getPrice() const;
    int getDuration() const;
    int getStops() const;
    string getTimeOfDay() const;

    void getBest(string& filter, string& origin, string& dest);        //returns the best graph based on the filter passed in
    string cheapestFlight(string &origin);     //given a starting city, returns cheapest graph
    string directExists(string &origin, string &dest);        //returns flightNum if a direct graph exists between two cities
    string flightMonth();        //returns the graph between two places in a certain month if it exists, else just returns null
    bool international(string& flightNum);    //returns if the graph is international or not
    void print(string& filter, string& flightNum); //prints the graph based off of filter and the best graph
};