#include <iostream>
#include "graph.h"
#include <string>
#include <map>
#include <set>

int Graph::n(string city) {
    return cityNamesMap[city];
}

void Graph::createMap(string cityFrom, string countryFrom, string cityTo, string countryTo,
                      string price,string distance, string duration, string timeZoneDiff,
                      string month, string date, string departureTime, string international, string flightNum){

    float tz = stof(timeZoneDiff);
    int priceNum = stoi(price);
    int distanceNum = stoi(distance);
    int dur = stoi(duration);
    bool intl = true;

    if (international == "no") {
        intl = false;
    }

    this->current = new Flight(cityFrom, countryFrom, cityTo, countryTo, priceNum, distanceNum, dur, tz, month, date, departureTime, intl, flightNum);

    g[n(cityFrom)][n(cityTo)] = current;    //inserting flight into matrix
}

Flight* Graph::cheapestDirect(string &origin) {
    Flight *cheapestPair;
    int price;
    int min = 100000000;

    for (int i = 0; i < 100; i++) {      //our grid is 100x100, we know at most there's 100 iterations to go over whole line
        if (g[n(origin)][i] != nullptr) {
            price = g[n(origin)][i]->price;
            if (price < min) {
                min = price;
                cheapestPair = g[n(origin)][i];
            }
        }
        return cheapestPair;
    }
}

Flight* Graph::cheapestIntl(string &origin) {
    Flight* final = nullptr;
    int price;
    int min = 100000000;

    for(int i = 0; i < 100; i++) {      //our grid is 100x100 so we know at most there's 100 iterations to go over whole line
        Flight* temp = g[n(origin)][i];

        if (temp != nullptr) {
            price = temp->price;

            if(price < min && temp->intl) {
                final = temp;
            }
        }
        delete temp;
    }
    return final;
}

Flight* Graph::directExists(string &origin, string &dest) {
    if (g[n(origin)][n(dest)] == nullptr) {       //if there is not a graph number at this specific position then direct graph doesn't exist;
        cout << "Direct flight between " << origin << " and " << dest << " does not exist." << endl << endl;
    }
    return g[n(origin)][n(dest)]; //return the flight
}

Flight* Graph::flightMonth(string &origin, string &month) {
    Flight* final = nullptr;
    int price;
    int min = 100000000;

    for(int i = 0; i < 100; i++) {      //our grid is 100x100 so we know at most there's 100 iterations to go over whole line
         Flight* temp = g[n(origin)][i];

        if (temp != nullptr) {
            price = temp->price;

            if(price < min && temp->month == month) {
                final = temp;
            }
        }
        delete temp;
    }
    return final;
}

bool Graph::international(string &origin, string &dest) {
    return g[n(origin)][n(dest)]->intl;
}

vector<Flight*> Graph::cheapestPath(string &origin, string &dest) {        //want to use djikstra's or another algorithm to get shortest path
//returns a vector of flight numbers
}

void Graph::getBest(string &filter, string &origin, string &dest) {
    Flight* thisFlight = nullptr;

    if (filter == "Cheapest Direct Flight") {
        thisFlight = cheapestDirect(origin);     //if the filter is cheap then we call cheapest graph helper function
    }
    else if (filter == "Direct") {
        thisFlight = directExists(origin, dest);     //if filter is direct, set graph number equal to
    }
    else if (filter == "Cheapest International Flight") {
        thisFlight = cheapestIntl(origin); 
    }
    else if (filter == "International" || filter == "Domestic") {
        bool isIntl = international(origin, dest);
        if (isIntl) {
            cout << "Flight is international. Passport is needed." << endl;
        }
        else {
            cout << "Flight is domestic. No passport is needed." << endl;
        }
    }
    else if (filter == "Month") {
        string temp;
        cout << "What month are you looking at flying? " << endl;
        cin >> temp;
        thisFlight = flightMonth(origin, temp);
        
        if (thisFlight == nullptr) {
            cout << "No direct flight from " << origin << " in " << temp << " was found." << endl;
        }
    }
    else {
        filter = "";
    }
    
    printBoardingPass(filter, thisFlight);
    
    delete thisFlight;
}

void Graph::readCSVFile(string filename){
    ifstream file;
    file.open(filename);

    string line, cityFrom, cityTo, countryFrom, countryTo, month, depTime, date, flightNum, temp;
    int price, distance, duration, timeDiff;
    bool intl;
    while(getline(file, line)){
        stringstream ss(line);
        getline(ss, cityFrom,',');
        getline(ss, countryFrom,',');
        getline(ss, cityTo,',');
        getline(ss, countryTo,',');
        getline(ss, temp,',');
        price = stoi(temp);
        getline(ss, temp,',');
        distance = stoi(temp);
        getline(ss, temp,',');

        getline(ss, cityFrom,',');
        getline(ss, cityFrom,',');
        getline(ss, cityFrom,',');
        getline(ss, cityFrom,',');
        getline(ss, cityFrom,',');
        getline(ss, cityFrom,',');
        getline(ss, cityFrom);
    }
}

void Graph::printBoardingPass(string &filter, Flight* thisFlight) {
    if (filter.empty() || thisFlight == nullptr) {       //either invalid filter, or no boarding pass to print because they just wanted info
        cout << "Error. No Boarding Pass to Print." << endl << endl;
    }
    else {      //flight exists and a valid filter was passed in
        // print out all relevant graph info by accessing the graph from map
        //thinking sfml can print this out on ticket
        cout << "Based on " << filter << " flight filter, the best flight(s) for you is:" << endl;
        cout << "Flight number: " << thisFlight->flightNumber << endl;
        cout << "Origin City: " << thisFlight->originCity << endl;
        cout << "Destination City: " << thisFlight->destinationCity << endl << endl;
        cout << "Date: " << thisFlight->date << endl;
        cout << "Departure Time: " << thisFlight->time << endl;
        cout << "Time of Travel: " << thisFlight->duration << endl;
        cout << "Distance of Travel: " << thisFlight->distance << endl;
        cout << "Time Zone Difference: " << thisFlight->timeDiff << endl << endl;
        cout << "The Price for This Flight is: " << thisFlight->price << endl << endl;
    }
}
