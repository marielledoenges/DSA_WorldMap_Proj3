#pragma once
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
//#include "FrontEnd.h"

using namespace std;

// Represents an individual graph, holding all relevant details and providing methods for accessing these details.
struct Flight {
    string originCity;    // The departure city of the graph.
    string originCountry;
    string destinationCity;   // The destination city of the graph.
    string destCountry;
    string time;     // Descriptive time of departure (e.g., "Morning", "Afternoon", "Evening").
    string month;
    string date;
    string flightNumber;       //how we will distinguish different flights
    string distance;
    int price;    // Cost of the graph in USD.
    string duration; // Duration of the graph in hours
    string timeDiff;   //time difference between two cities
    bool intl;

    //constructor of our flight object
    Flight(){};
    Flight(string &cityFrom, string &countryFrom,string &cityTo, string &countryTo,int &priceGiven, string &distanceGiven,
           string &durationGiven, string &timeZoneDiff, string &monthGiven, string &dateGiven, string &departureTime,
           bool &international, string &number):

            originCity(cityFrom), originCountry(countryFrom), destinationCity(cityTo), destCountry(countryTo), price(priceGiven), distance(distanceGiven),
            duration(durationGiven), time(departureTime), month(monthGiven), date(dateGiven),
            timeDiff(timeZoneDiff), flightNumber(number), intl(international)
    {}

};

class Graph{
private:
    unordered_map<string, int> cityNamesMap = {{"Tampa", 0}, {"Gainesville", 1}, {"Paris", 2}, {"London", 3}, {"New York", 4},
                                               {"Miami", 5}, {"Washington DC", 6}, {"Seattle", 7}, {"Las Vegas", 8}, {"Los Angeles", 9},
                                               {"Houston", 10}, {"Austin", 11}, {"Dallas", 12}, {"Atlanta", 13}, {"Charleston", 14},
                                               {"Bonn", 15}, {"Buenos Aires", 16}, {"Lima", 17}, {"Mar Del Plata", 18}, {"Okinawa", 19},
                                               {"Madrid", 20}, {"Valencia", 21}, {"Sevilla", 22}, {"Copenhagen", 23}, {"Stockholm", 24},
                                               {"Oslo", 25}, {"Shanghai", 26}, {"Dubai", 27}, {"Rome", 28}, {"Milan", 29},
                                               {"Nice", 30}, {"Frankfurt", 31},  {"Berlin", 32}, {"Moscow", 33}, {"Sao Paulo", 34},
                                               {"Mexico City", 35}, {"Chicago", 36}, {"Toronto", 37}, {"Quebec", 38}, {"Kansas City", 39},
                                               {"Juneau", 40}, {"Mumbai", 41}, {"New Dehli", 42}, {"Bangkok", 43}, {"Hong Kong", 44},
                                               {"Sydney", 45}, {"Melbourne", 46}, {"Beijing", 47}, {"Taipei", 48}, {"Seoul", 49},
                                               {"Nagasaki", 50}, {"Tokyo", 51}, {"Baghdad", 52}, {"Jerusalem", 53}, {"Istanbul", 54},
                                               {"Athens", 55}, {"Budapest", 56}, {"Vienna", 57}, {"Sofia", 58}, {"Kyiv",59},
                                               {"Warsaw", 60}, {"Minsk", 61}, {"Amsterdam", 62}, {"Zurich", 63}, {"Brussels", 64},
                                               {"St. Tropez", 65}, {"Naples", 66}, {"Ibiza", 67},  {"Tunis", 68}, {"Lisbon", 69},
                                               {"Dublin", 70}, {"Glasgow", 71},  {"Edinburgh", 72}, {"Malmo", 73}, {"Helsinki", 74},
                                               {"Bergen", 75}, {"St. Petersburg", 76}, {"Reykjavik", 77}, {"Panama City", 78}, {"Medellin", 79},
                                               {"Bogota", 80}, {"Quito", 81}, {"Caracas", 82}, {"Brasilia", 83}, {"Santiago", 84},
                                               {"Montevideo", 85}, {"San Juan", 86}, {"Havana", 87}, {"Cairo", 88}, {"Marrakesh", 89},
                                               {"Abuja", 90}, {"Nairobi", 91}, {"Zanzibar", 92}, {"Cape Town", 93}, {"Prague",94},
                                               {"San Fransisco", 95}, {"Honolulu", 96}, {"Santorini", 97}, {"Madeira", 98}, {"Oporto", 99}}; //unordered map of cities and their corresponding position of

    unordered_set<string> globalCities;     //keeps track of what cities have already been added
    unordered_map<string, string> cityCountry;  //keeps track of a city and it's country
    Flight* g[100][100];     //graph representation of matrix

    Flight* priceTwoCites(string &origin, string &dest);    //given a starting and destination city return the price of a direct flight if applicable
    Flight* cheapestDirect(string &origin);     //given a starting city, returns cheapest direct flight number
    Flight* directExists(string &origin, string &dest);        //returns flightNum if a direct graph exists between two cities
    Flight* flightMonth(string &origin, string  &month);        //returns the flight number of cheapest flight in a given month, returns empty if no flight exists
    Flight* cheapestIntl(string &origin);           //finds the cheapest international flight
    vector<string> minCity(string &origin, int &budget);        //cheapest way to get between two places if possible, returns a vector of flight numbers. should be generalized
    vector<string> path(string &origin, string &dest);      //returns a vector of cities to get between two cities if possible
    bool international(string &origin, string &dest);    //returns if the graph is international or not

public:
    Flight* current;

    Graph(){ //constructor of a graph object to make everything nullptr
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j ++){
                g[i][j] = nullptr;
            }
        }
    }
    void createMap(string cityFrom, string countryFrom, string cityTo, string countryTo,
                   string price,string distance, string duration, string timeZoneDiff,
                   string month, string date, string departureTime, string international, string flightNum); //creating actual map

    vector<string> getBest(string filter, string origin, string dest, string month);        //returns the best flight based on the filter passed in
    vector<string> printBoardingPass(string &filter, Flight* thisFlight); //prints the graph based off of filter and the best graph
    void readCSVFile(string filename);    //reads the csv file of data given and passes data to createmap function
    int n(string city);        //returns the number/position of a city in a map
    string getCountry(string &city);        //returns the country of a city
    string monthNum(string month);     //returns a number corresponding to a month
};
