// Created by Maggie Snead on 4/11/24.
#include <iostream>
#include "graph.h"
#include <string>
#include <map>
#include <set>


void
Graph::createMap(string cityFrom, string countryFrom, string cityTo, string countryTo, string price, string distance,
                 string duration, string timeZoneDiff, string month, string date, string departureTime,
                 string international, string flightNum) {

    //FIXME not sure if we really need to keep track of the cities and have a city struct
    if (cities.count(cityFrom) == 0) {      //if the from city isn't in our city set
        cities.insert(cityFrom);
        this->myCity = createCityHelper(cityFrom, countryFrom); //create city
    }
    if (cities.count(cityTo) == 0) {     //if the to city isn't in our city set
        cities.insert(cityTo);
        this->myCity = createCityHelper(cityTo, countryTo);
    }

    this->current = createFlightHelper(cityFrom, cityTo, price, distance, duration, timeZoneDiff, month, date, departureTime,
            international, flightNum);  //create a new flight
}

city* Graph::createCityHelper(string &cityName, string &countryName) {
    city* cityToCreate = new city(cityName, countryName);
   return cityToCreate;
}


flight* Graph::createFlightHelper(string &cityFrom, string &cityTo, string &price, string &distance,
                 string &duration, string &timeZoneDiff, string &month, string &date, string &departureTime,
                 string &international, string &flightNum) {

    float tz = stof(timeZoneDiff);
    int priceNum = stoi(price);
    int distanceNum = stoi(distance);
    int dur = stoi(duration);
    bool intl = true;

    if (international == "no") {
        intl = false;
    }
    //FIXME not sure this is right
    flight* current = new flight(cityFrom, cityTo, priceNum, distanceNum, dur, tz, month, date, departureTime, intl, flightNum);

    flightPair[flightNum] = current;   //insert the flight number and flight pair into map
    g[cityFrom][cityTo] = flightNum;    //inserting flight number into matrix

    return current;
}




string Graph::cheapestDirect(string &origin) {
    string flightNum;
    int price;
    int min = 100000000;

    for(int i = 0; i < 100; i++) {      //our grid is 100x100 so we know at most there's 100 iterations to go over whole line
        string temp = g[origin][i];

        if (!temp.empty()) {
            price = flightPair[temp]->price;

            if(price < min) {
                flightNum = temp;
            }
        }
    }
    return flightNum;
}
string Graph::directExists(string &origin, string &dest) {
    if (g[origin][dest].empty) {       //if there is not a graph number at this specific position then direct graph doesn't exist;
        cout << "Direct graph between " << origin << " and " << dest << " does not exist." << endl << endl;
    }
    return g[origin][dest];        //else it exists return true
}

bool Graph::international(string &flightNum) {
    return flightPair[flightNum]->intl;
}

void Graph::getBest(string &filter, string &origin, string &dest) {
    string flightNum;
    bool goodFilter = true;

    if (filter == "cheapest") {
        flightNum = cheapestDirect(origin);     //if the filter is cheap then we call cheapest graph helper function
    }
    else if (filter == "direct") {
        flightNum = directExists(origin, dest);     //if filter is direct, set graph number equal to
    }
    else if (filter == "international") {

    }
    else if (filter == "filter 2") {        //FIXME

    }
    else {
        filter.empty();
    }

    print(filter, flightNum);

}
void Graph::print(string &filter, string &flightNum) {
    if (filter.empty()) {       //invalid filter was passed in
        cout << "Error. Invalid Filter." << endl << endl;
    }
    else if (flightNum.empty()) {   //this type of flight does not exist
        cout << "Flight does not exist." << endl << endl;
    }
    else {      //flight exists and a valid filter was passed in
        // print out all relevant graph info by accessing the graph from map
        cout << "Based on " << filter << " flight filter, the best flight for you is:" << endl;
        cout << "Flight number: " << flightNum << endl;
        cout << "Origin City: " << flightPair[flightNum]->originCity << endl;
        cout << "Destination City: " << flightPair[flightNum]->destinationCity << endl << endl;
        cout << "Date: " << flightPair[flightNum]->date << endl;
        cout << "Departure Time: " << flightPair[flightNum]->time << endl;
        cout << "Time of Travel: " << flightPair[flightNum]->duration << endl;
        cout << "Distance of Travel: " << flightPair[flightNum]->distance << endl;
        cout << "Time Zone Difference: " << flightPair[flightNum]->timeDiff << endl << endl;
        cout << "The Price for This Flight is: " << flightPair[flightNum]->price << endl << endl;
    }
}









