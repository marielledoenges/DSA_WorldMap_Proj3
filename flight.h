#ifndef PROJECT3_FLIGHT_H
#define PROJECT3_FLIGHT_H


//IMPORTANT: Wants to make a struct for the cities, Want to optimize how to store things
#include <string>

// Represents an individual flight, holding all relevant details and providing methods for accessing these details.
class Flight {
private:
    string originCity;    // The departure city of the flight.
    string destinationCity;   // The destination city of the flight.
    int price;    // Cost of the flight in USD.
    int duration; // Duration of the flight in minutes.
    int stops;    // Number of stops the flight makes.
    std::string timeOfDay;     // Descriptive time of departure (e.g., "Morning", "Afternoon", "Evening").

public:
    // Constructor to initialize all properties of the flight.
    Flight(std::string origin, std::string destination, int cost, int dur, int numStops, std::string time);

    // Getter methods to expose private properties in a controlled manner.
    string getOriginCity() const;
    string getDestinationCity() const;
    int getPrice() const;
    int getDuration() const;
    int getStops() const;
    string getTimeOfDay() const;
};

#endif // PROJECT3_FLIGHT_H