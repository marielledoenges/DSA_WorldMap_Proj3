#include <iostream>
#include "Graph.h"
#include "FrontEnd.h"
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>


void Graph::createMap(string cityFrom, string countryFrom, string cityTo, string countryTo,
                      string price,string distance, string duration, string timeZoneDiff,
                      string month, string date, string departureTime, string international, string flightNum){

    int priceNum = stoi(price);     //change price to an int
    bool intl = true;

    if (international == "no") {
        intl = false;
    }

    cityCountry[cityFrom] = countryFrom;        //push back cities and corresponding countries into map
    cityCountry[cityTo] = countryTo;

    //create new flight
    this->current = new Flight(cityFrom, countryFrom, cityTo, countryTo, priceNum, distance, duration, timeZoneDiff, month, date, departureTime, intl, flightNum);

    g[n(cityFrom)][n(cityTo)] = current;    //inserting flight into matrix
}

Flight* Graph::cheapestDirect(string &origin) {
    Flight *cheapestPair = nullptr;     //initialize pointer to be null
    int price;
    int min = 100000000;

    for (int i = 0; i < 100; i++) {      //our grid is 100x100, we know at most there's 100 iterations to go over whole line
        if (g[n(origin)][i] != nullptr) {       //if a flight exists
            price = g[n(origin)][i]->price;     //get current price
            if (price < min) {      //if it's less than our current minimum price
                min = price;        //update our min price
                cheapestPair = g[n(origin)][i];     //set our cheapest pair to this flight
            }
        }
    }
    return cheapestPair;        //return the cheapest direct flight
}

Flight* Graph::cheapestIntl(string &origin) {
    Flight* final = nullptr;        //initialize to nullptr
    int price;
    int min = 100000000;

    for(int i = 0; i < 100; i++) {      //our grid is 100x100 so we know at most there's 100 iterations to go over whole line
        Flight* temp = g[n(origin)][i];     //set a current pointer to this specific flight in the matrix

        if (temp != nullptr) {
            price = temp->price;

            if(price < min && temp->intl) {     //if it's less than our current minimum price and is an international flight
                min = price;
                final = temp;       //set our final flight equal to our temp pointer
            }
        }
        delete temp;        //delete the temp pointer
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

            if(price < min && temp->month == month) {   //if it's less than our current minimum price and the month we want
                final = temp;
            }
        }
        delete temp;        //handling memory by deleting this temporary pointer
    }
    return final;       //return our final pointer
}

bool Graph::international(string &origin, string &dest) {
    string countryOne = getCountry(origin);
    string countryTwo = getCountry(dest);

    if (countryOne == countryTwo) {     //if the cities give different countries then it is international
        return true;
    }
    return false;
}

vector<string> Graph::minCity(string &origin, int &budget) {        //use a bfs to get the minimum number of cities we can visit with our budget
//returns a vector of string of cities
    queue<pair<string,int>> q;      //have a queue with cities and prices to visit that city
    unordered_set<string> visited;        //have an unordered set that keeps track of all the visited cities
    vector<string> final;           //final vector of cities we will return
    int totalPrice = 0;         //the total price spent so far

    visited.insert(origin);     //mark the origin as visited
    q.emplace(origin, 0);       //place back the origin with a price of zero

    while (!q.empty()) {
        pair<string, int> currCity = q.front();     //our current city is going to be the one at the front of the queue

        if (currCity.second + totalPrice > budget) {     //if the current price to travel to this city is greater than our max
            return final;       //we know we hit minimum number of cities to visit with that price and we return the current final vector
        }

        totalPrice += currCity.second;      //else we have room in budget so we add the price to travel to this city
        final.push_back(currCity.first);    //push back this city into the vector
        q.pop();    //pop the front

        for (int i = 0; i < 100; i++){      //we know our matrix is 100x100
            Flight* thisFlight = g[n(currCity.first)][i];       //set a temp flight pointer to this specific flight in our graph

            if(thisFlight!= nullptr && visited.count(thisFlight->destinationCity) == 0) {       //if our set doesn't have the destination city and this flight exists
                visited.insert(thisFlight->destinationCity);        //add it to our visited set
                q.emplace(thisFlight->destinationCity, thisFlight->price);      //push it into our queue
            }

            delete thisFlight;      //handling memory, so delete this temporary pointer
        }
    }
    return final;       //if we make it all the way here we could visit all cities with our budget
}

vector<string> Graph::path(string &origin, string &dest) {      //bfs to see if a path exists, firsts checks if a direct exists
    vector<string> final;
    vector<string> noPath;
    queue<string> q;      //have a queue with cities and prices to visit that city
    unordered_set<string> visited;        //have an unordered set that keeps track of all the visited cities

    q.push(origin);
    visited.insert(origin);

    if (g[n(origin)][n(dest)] != nullptr) {     //checks if there is a direct flight
        final.push_back(origin);        //if so push back origin and destination cities into final vector
        final.push_back(dest);
        return final;       //return two cities
    }

    while (!q.empty()) {        //while the queue is not empty
        string current = q.front();
        q.pop();
        final.push_back(current);

        for (int i = 0; i < 100; i++){      //we know our matrix is 100x100
            Flight* thisFlight = g[n(current)][i];       //set a temp flight pointer to this specific flight in our graph

            if (thisFlight == nullptr) {        //if it's null just go to next fljght
                continue;
            }

            if (thisFlight->destinationCity == dest) {      //if the destination matches the wanted destination
                final.push_back(dest);      //push back and return
                return final;
            }

            if(visited.count(thisFlight->destinationCity) == 0) {       //if our set doesn't have the destination city
                visited.insert(thisFlight->destinationCity);        //add it to our visited set
                q.push(thisFlight->destinationCity);      //push it into our queue
            }

            delete thisFlight;      //handling memory, so delete this temporary pointer
        }
    }

    return noPath;  //if we made it here that means we never reached our destination
}


vector<string> Graph::getBest(string filter, string origin, string dest, string otherInfo) {
    Flight* thisFlight = nullptr;
    string newFilter = "Info";

    if (filter == "Cheapest Direct Flight") {
        thisFlight = cheapestDirect(origin);     //if the filter is cheap then we call cheapest graph helper function

        if (thisFlight == nullptr) {
            cout << "No direct flight from " << origin << " was found." << endl;
        }
    }
    else if (filter == "Direct") {
        thisFlight = directExists(origin, dest);     //if filter is direct, set graph number equal to

        if (thisFlight == nullptr) {
            cout << "No direct flight from " << origin << " to " << dest << " was found." << endl;
        }
    }
    else if (filter == "Cheapest International Flight") {
        thisFlight = cheapestIntl(origin);

        if (thisFlight == nullptr) {
            cout << "No international flight from " << origin << " was found." << endl;
        }
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
    else if(filter == "Flight path") {
        vector<string> cities = path(origin,dest);
        vector<string> nbp;

        if (cities.size() == 0) {
            cout << "No path exists between " << origin << " and " << dest << ". " << endl;
            return cities;
        }
        else if (cities.size() == 2) {
            cout << "A direct flight exists between " << origin << " and " << dest << ". " << endl;
            thisFlight = g[n(origin)][n(dest)];
            newFilter = "Boarding Pass";
        }
        else {
            cout << "No boarding pass to print. " << endl;
            cout << "One suggested path found between " << origin << " and " << dest << " is: " << endl;
            nbp.push_back("NA");

            for (int i = 0; i < cities.size(); i++) {
                cout << i+1 << ". " << cities.at(i) << endl;
                nbp.push_back(cities.at(i));
            }
            return nbp;
        }
    }
    else if (filter == "Month") {
        thisFlight = flightMonth(origin, otherInfo);

        if (thisFlight == nullptr) {
            cout << "No direct flight from " << origin << " in " << otherInfo << " was found." << endl;
        }
    }
    else if (filter == "Minimum Num Cities") {
        int budget = stoi(otherInfo);
        vector<string> destinations = minCity(origin, budget);
        vector<string> toReturn;
        string temp;

        if (destinations.size() == 1) {
            cout << "You cannot travel to any destination from " << origin << " with this budget. " << endl;
        }

        else {
            cout << "Starting at " << origin << " the minimum number of cities \nyou can consecutively fly to for ";
            cout << otherInfo << " is: " << endl;
            temp.append("Starting at ");
            temp.append(origin);
            temp.append("\n");
            temp.append("the minimum number of cities you can fly to is:\n");
            for (int i = 1; i < destinations.size(); i++) {
                cout << "\t" << i << ". " << destinations.at(i) << endl;
                temp.append(to_string(i));
                temp.append(". ");
                temp.append(destinations.at(i));
                temp.append("\n");
            }
            toReturn.push_back(temp);
            return toReturn;
        }
    }
    else {
        newFilter = "";
    }

    cout << endl;
    vector<string> info = printBoardingPass(newFilter, thisFlight);
    delete thisFlight;

    return info;
}

string Graph::monthNum(string month) {
    string num = "1";
    if (month == "February") {
        num = "2";
    }
    else if (month == "March") {
        num = "3";
    }
    else if (month == "April") {
        num = "4";
    }
    else if (month == "May") {
        num = "5";
    }
    else if (month == "June") {
        num = "6";
    }
    else if (month == "July") {
        num = "7";
    }
    else if (month == "August") {
        num = "8";
    }
    else if (month == "September") {
        num = "9";
    }
    else if (month == "October") {
        num = "10";
    }
    else if (month == "November") {
        num = "11";
    }
    else if (month == "December") {
        num = "12";
    }
    else {
        return "1";
    }
    return num;
}

int Graph::n(string city) {
    return cityNamesMap[city];
}

string Graph::getCountry(string &city) {
    return cityCountry[city];
}

vector<string> Graph::printBoardingPass(string &filter, Flight* thisFlight) {
    vector<string> final;
    if (filter == " " || thisFlight == nullptr) {
        final.emplace_back("No info available \n");
        return final;
    }
    else if (filter == "Info") {       //either invalid filter, or no boarding pass to print because they just wanted info
        string flightNum = "Flight number:";
        flightNum.append(thisFlight->flightNumber);

        string longString = "The best flight for you is: \n";
        longString.append("Origin:");
        longString.append(thisFlight->originCity);
        longString.append(", ");
        longString.append(thisFlight->originCountry);
        longString.append("\n");

        longString.append("Dest.:");
        longString.append(thisFlight->destinationCity);
        longString.append(", ");
        longString.append(thisFlight->destCountry);
        longString.append("\n");

        longString.append("Date:");
        longString.append(thisFlight->month);
        longString.append(", ");
        longString.append(thisFlight->date);
        longString.append("\n");

        longString.append("Departure Time:");
        longString.append(thisFlight->month);
        longString.append(", ");
        longString.append(thisFlight->date);
        longString.append("\n");

        longString.append("Duration:");
        longString.append(thisFlight->duration);
        longString.append(" hours\n");

        longString.append("Distance:");
        longString.append(thisFlight->distance);
        longString.append(" miles\n");

        longString.append("Time Zone Difference:");
        longString.append(thisFlight->timeDiff);
        longString.append(" hours \n");

        longString.append("Price:$");
        longString.append(to_string(thisFlight->price));
        longString.append("\n");

        final.push_back(longString);

        return final;       //nothing to print
    }
    else {      //flight exists and a valid filter was passed in
        // print out all relevant graph info by accessing the graph from map
        //thinking sfml can print this out on ticket

        string numMonth = monthNum(thisFlight->month);

        final.push_back(thisFlight->flightNumber);      //push back all flight info into a vector so window of printing boarding pass can be easily achieved
        final.push_back(thisFlight->originCity);
        final.push_back(thisFlight->originCountry);
        final.push_back(thisFlight->destinationCity);
        final.push_back(thisFlight->destCountry);
        final.push_back(numMonth);
        final.push_back(thisFlight->date);
        final.push_back(thisFlight->time);
        final.push_back(thisFlight->duration);
        final.push_back(thisFlight->distance);
        final.push_back(thisFlight->timeDiff);
        final.push_back(to_string(thisFlight->price));
    }
    return final;
}

void Graph::readCSVFile(string filename){
    ifstream file;
    file.open(filename);

    string line, cityFrom, cityTo, countryFrom, countryTo, month, depTime, date, flightNum, temp , price, distance, duration, timeDiff, intl;

    while(getline(file, line)){
        //fill out all the variables to create a flight object
        stringstream ss(line);
        getline(ss, cityFrom,',');
        getline(ss, countryFrom,',');
        getline(ss, cityTo,',');
        getline(ss, countryTo,',');
        getline(ss, price,',');
        getline(ss, distance,',');
        getline(ss, duration,',');
        getline(ss, timeDiff,',');
        getline(ss, month,',');
        getline(ss, date,',');
        getline(ss, depTime,',');
        getline(ss, intl,',');
        getline(ss, flightNum);

        //create a flight object with these details
        createMap(cityFrom, countryFrom, cityTo, countryTo, price, distance, duration, timeDiff, month, date, depTime, intl, flightNum);
    }
}