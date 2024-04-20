#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "generalData.h"
#include <algorithm>
#include <map>
#include "FrontEnd.h"
using namespace std;


int main() {

    WorldInfo test;
    test.writeFile("proj3DataTest.csv");

    // Initialize your application interface
    FrontEnd app(800, 600, "Boarding Pass Viewer");
    // Load the Roboto font
    app.loadFont("fonts/Roboto-Regular.ttf");  // Ensure the path is correct
    // Run the application
    app.run();

    return 0;
}
