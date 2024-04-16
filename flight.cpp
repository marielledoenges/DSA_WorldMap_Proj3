//
// Created by Maggie Snead on 4/11/24.
//

#include "flight.h"

// Constructor implementation initializing class members from the provided parameters.
Flight::Flight(std::string origin, std::string destination, int cost, int dur, int numStops, std::string time)
        : originCity(origin), destinationCity(destination), price(cost), duration(dur), stops(numStops), timeOfDay(time) {}

// Implementation of getter methods.
std::string Flight::getOriginCity() const { return originCity; }
std::string Flight::getDestinationCity() const { return destinationCity; }
int Flight::getPrice() const { return price; }
int Flight::getDuration() const { return duration; }
int Flight::getStops() const { return stops; }
std::string Flight::getTimeOfDay() const { return timeOfDay; }