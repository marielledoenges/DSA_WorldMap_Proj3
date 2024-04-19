#include <iostream>
#include "graph.h"
#include <string>
#include <map>
#include <set>



void Graph::createMap(string cityFrom, string countryFrom, string cityTo, string countryTo,
                      string price,string distance, string duration, string timeZoneDiff,
                      string month, string date, string departureTime, string international, string flightNum){

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

City* Graph::createCityHelper(string &cityName, string &countryName) {
    City* cityToCreate = new City(cityName, countryName);
    return cityToCreate;
}


Flight* Graph::createFlightHelper(string &cityFrom, string &cityTo, string &price, string &distance,
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
    Flight* current = new Flight(cityFrom, cityTo, priceNum, distanceNum, dur, tz, month, date, departureTime, intl, flightNum);

    flightPair[flightNum] = current;   //insert the flight number and flight pair into map
    g[i(cityFrom)][i(cityTo)] = current;    //inserting flight number into matrix

    return current;
}

string Graph::cheapestDirect(string &origin) {
    string flightNum;
    Flight *cheapestPair;
    int price;
    int min = 100000000;

    for (int j = 0;
         j < 100; j++) {      //our grid is 100x100, we know at most there's 100 iterations to go over whole line
        if (g[i(origin)][j] != nullptr) {
            price = g[i(origin)][j]->price;
            if (price < min) {
                min = price;
                cheapestPair = g[i(origin)][j];
            }
        }

        return cheapestPair->flightNumber;
    }
}

string Graph::directExists(string &origin, string &dest) {
    if (g[i(origin)][i(dest)] == nullptr) {       //if there is not a graph number at this specific position then direct graph doesn't exist;
        cout << "Direct flight between " << origin << " and " << dest << " does not exist." << endl << endl;
    }
    return g[i(origin)][i(dest)]->flightNumber;        //else it exists return true FIXME i think youre trying to return the flight number? idk
}

string Graph::flightMonth(string &origin, string &month) {      //FIXME might be better way to do this without copying so much code
    string flightNum;
    int price;
    int min = 100000000;

    for(int i = 0; i < 100; i++) {      //our grid is 100x100 so we know at most there's 100 iterations to go over whole line
        string temp = g[origin][i];

        if (!temp.empty()) {
            price = flightPair[temp]->price;

            if(price < min && flightPair[temp]->month == month) {
                flightNum = temp;
            }
        }
    }
    return flightNum;
}

bool Graph::international(string &origin, string &dest) {
    return g[i(origin)][i(dest)]->intl;
}

vector<string> Graph::cheapestPath(string &origin, string &dest) {        //want to use djikstra's or another algorithm to get shortest path
//returns a vector of flight numbers
}

void Graph::getBest(string &filter, string &origin, string &dest) {
    string flightNum;

    if (filter == "Cheapest Direct Flight") {
        flightNum = cheapestDirect(origin);     //if the filter is cheap then we call cheapest graph helper function
    }
    else if (filter == "Direct") {
        flightNum = directExists(origin, dest);     //if filter is direct, set graph number equal to
    }
    else if (filter == "Cheapest International Flight") {

    }
    else if (filter == "International" || filter == "Domestic") {
        bool international = international(origin, dest);
        if (international) {
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
        flightNum = flightMonth(origin, temp);
    }
    else {
        filter = "";
    }

    printBoardingPass(filter, flightNum);

}

void Graph::printBoardingPass(string &filter, string &flightNum) {
    if (filter.empty() || flightNum.empty()) {       //either invalid filter, or no boarding pass to print because they just wanted info
        cout << "Error. No Boarding Pass to Print." << endl << endl;
    }
    else {      //flight exists and a valid filter was passed in
        // print out all relevant graph info by accessing the graph from map
        cout << "Based on " << filter << " flight filter, the best flight(s) for you is:" << endl;
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

int Graph::i(string city) {
    return cityNamesMap[city];
}

