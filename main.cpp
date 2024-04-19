#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "generalData.h"
#include "flight.h"
#include <algorithm>
#include <map>
#include "FrontEnd.h"
using namespace std;


int main() {

    WorldInfo test;
    test.writeFile("proj3DataTest.csv");

    FrontEnd app(800, 600, "Boarding Pass Viewer");
    app.loadFont(".ttf");  
    app.run();

    return 0;
}
