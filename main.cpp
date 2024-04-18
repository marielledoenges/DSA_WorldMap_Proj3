#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "generalData.h"
#include "flight.h"
#include <algorithm>
#include <map>
using namespace std;


int main() {

    WorldInfo test;
    test.writeFile("proj3DataTest.csv");

    return 0;
}
