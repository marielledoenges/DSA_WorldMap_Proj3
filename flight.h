#pragma once
#include <string>
#include <map>

using namespace std;

struct city{    //FIXME not sure if needed
    string name, country, TZ;
    //keep track of flight objects that leave this city to go to another city
    //thinking a vector
    //keep track of flight objects that come into this city from another city
    //thinking a vector
};

// Represents an individual flight, holding all relevant details and providing methods for accessing these details.
struct flight {
    string originCity;    // The departure city of the flight.
    string destinationCity;   // The destination city of the flight.
    int price;    // Cost of the flight in USD.     //FIXME not sure if just whole number or double
    int duration; // Duration of the flight in minutes.
    int stops;    // Number of stops the flight makes.
    string timeOfDay;     // Descriptive time of departure (e.g., "Morning", "Afternoon", "Evening").
    string month;
    int timeDiff;   //FIXME not sure if whole number
    int flightNumber;       //how we will distinguish different flights

    //constructor of our flight object
    flight(int& number) : originCity(""), destinationCity(""), price(0), duration(0), stops(0), timeOfDay(""), month(""), timeDiff(0), flightNumber(number){}

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
    //map corresponding keys with specific cities ... could make it "easier" to implement graph but might make it longer
    //for example 1 would correspond with city miami
    map<int, string> cityNumber;        //maps a city with a specific number so we can easily understand which city we are dealing with in the graph
    city graph [100][100] = {};     //the integer indexes correspond to the value city

public:
    // Constructor to initialize all properties of the flight.

    // Getter methods to expose private properties in a controlled manner.
//Work on returning flight object, get lowest price between two cities
    string getOriginCity() const;
    string getDestinationCity() const;
    int getPrice() const;
    int getDuration() const;
    int getStops() const;
    string getTimeOfDay() const;

    flight getBest(string& filter);        //returns the best flight based on the filter passed in

    flight cheapestFlight();     //FiXME parameters inputted should be two starting cities
    bool flightExists();        //returns if the flight exists between two cities these cities should be the parameter
    flight flightMonth();        //returns the flight between two places in a certain month if it exists, else just returns null
    bool international();    //returns if the flight is international or not

    void print(string& filter, int& flightNum); //prints the flight based off of filter and the best flight
};


//we should have a container for each "cell" in the matrix
//graph implemented with a matrix representation
//
