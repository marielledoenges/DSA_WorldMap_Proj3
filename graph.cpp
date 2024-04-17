// Created by Maggie Snead on 4/11/24.
#include <iostream>
#include "graph.h"
#include <string>

void Graph::getBest(string &filter, string &origin, string &dest) {
   string flightNum;

    if (filter == "cheapest") {
        flightNum = cheapestFlight(origin);     //if the filter is cheap then we call cheapest graph helper function
    }
    else if (filter == "direct") {
        flightNum = directExists(origin, dest);     //if filter is direct, set graph number equal to
    }
    else if (filter == "international") {

    }
    else if (filter == "filter 2") {        //FIXME

    }
    else {
        cout << "Error: Filter is invalid " << endl<< endl;
    }

    if (flightNum != " ") {
        print(filter, flightNum);
    }
}

string Graph::cheapestFlight(string &origin) {
    string flightNum;
    return flightNum;
}

string Graph::directExists(string &origin, string &dest) {
    if (graph[origin][dest] == " ") {       //if there is not a graph number at this specific position then direct graph doesn't exist;
        cout << "Direct graph between " << origin << " and " << dest << " does not exist." << endl << endl;
        return "";
    }
    return graph[origin][dest];        //else it exists return true
}
bool Graph::international(string &flightNum) {
    return false;
}

void Graph::print(string &filter, string &flightNum) {
    cout << "Based on " << filter << " graph filter, the best graph for you is:" << endl;
    cout << "Flight number: " << flightNum << endl;
    // print out all relevant graph info by accessing the graph from map
    flightPair[flightNum][].price
}




