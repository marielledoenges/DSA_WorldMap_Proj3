#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "generalData.h"
#include "TextureManager.h"
#include <algorithm>
#include "FrontEnd.h"
#include <map>
using namespace std;


int main() {

    WelcomeScreen welcome;
    MapScreen map;
    //Flight testFlight((string &) "Tampa", (string &)"USA", (string &)"Paris", (string &)"France", 1200, 800, 6, 6.5, (string &)"April",(string &) "25", (string &)"8:30 AM", true, (string &)"12345");

    //uh.displayWindow();
    string command = welcome.showWelcomeScreen();
    vector<string> flightInfo;
    if(command == "map"){
       flightInfo =  map.displayWindow();
    }
    if(flightInfo.size() == 0){
        return 0;
    }else{
        Ticket toPrint(flightInfo);
        toPrint.draw();
    }


    return 0;
}
