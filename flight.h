// Created by Maggie Snead on 4/11/24.
#pragma once
#include <string>
#include <map>

using namespace std;

struct city{    //FIXME not sure if needed
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

class twoCityTravel {
private:
    //map corresponding keys with specific cities ... could make it "easier" to implement graph but might make it longer
    //for example 1 would correspond with city miami
    map<int, string> cityNumber;        //maps a city with a specific number so we can easily understand which city we are dealing with in the graph
    vector<flights> graph [100][100] = {};     //the integer indexes correspond to the value city

public:
    // Constructor to initialize all properties of the flight.

    // Getter methods to expose private properties in a controlled manner.
    string getOriginCity() const;
    string getDestinationCity() const;
    int getPrice() const;
    int getDuration() const;
    int getStops() const;
    string getTimeOfDay() const;


};


//we should have a container for each "cell" in the matrix
//graph implemented with a matrix representation
//

