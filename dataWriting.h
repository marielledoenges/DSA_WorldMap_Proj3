#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

bool writeLine(string filename, string cityFrom, string cityTo, string price,
               string distance, string numStops, string duration, string timeZoneDiff,
               string month, string departureTime){

    ofstream file;
    file.open(filename, ios_base::app);
    file << cityFrom << ","
        << cityTo << ",'"
        << price << ","
        << distance << ","
        << numStops << ","
        << duration << ","
        << timeZoneDiff << ","
        << month << ","
        << departureTime << ","
        << endl;

    file.close();
    return true;
}