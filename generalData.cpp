#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "generalData.h"
using namespace std;


//base min 50, base max 5000
string WorldInfo::makePrice(int min, int max){
    int price = min;
    price += (rand() % max);
    return to_string(price);
}

//base min 300 base max 10,000
string WorldInfo::makeDistance(int min, int max) {
    int dist = min;
    dist += (rand() % max);
    return to_string(dist);

}

string WorldInfo::makeDuration(int min, int max) {
    int dur = min;
    dur += (rand() % max);
    return to_string(dur);
}

string WorldInfo::makeTimeZoneDiff(std::string fromTZ, std::string toTZ){
    float diff = stof(fromTZ) - stof(toTZ);
    if(diff > 12){
        diff -= 12;
    }
    return to_string(diff);
}

string WorldInfo::makeMonth() {
    int monthIdx = rand() % 12;
    string month = months[monthIdx];
    return month;
}

string WorldInfo::makeDepartureTime() {
    int hours = rand() % 13;
    int minutes = rand() % 61;
    int AMvPM = rand() % 2;
    string time = "";

    time += to_string(hours);
    time += ":";

    if(minutes < 10){
        time += "0" + to_string(minutes);
    }else{
        time+= to_string(minutes);
    }

    if(AMvPM == 0){
        time += " AM";
    }else{
        time += " PM";
    }

    return time;

}

string WorldInfo::isInternational(int idxFrom, int idxTo) {
    if(correspondingCountries[idxFrom] == correspondingCountries[idxTo]){
        return "no";
    }else{
        return "no";
    }
}

bool WorldInfo::writeLine(string filename, string cityFrom, string countryFrom, string cityTo, string countryTo,
                          string price,string distance, string duration, string timeZoneDiff,
                          string month, string departureTime, string international){

    ofstream file;
    file.open(filename, ios_base::app);
    file << cityFrom << ","
         << countryFrom << ","
         << cityTo << ",'"
         << countryTo << ","
         << price << ","
         << distance << ","
         << duration << ","
         << timeZoneDiff << ","
         << month << ","
         << departureTime << ","
         << international
         << endl;

    file.close();
    return true;
}

bool WorldInfo::writeFile(string filename){
    string response, TZF, TZT, cityFrom, cityTo, countryFrom, countryTo, price, distance, dur, TZdiff, month, depTime, international;
    int min, max;
    for(int i = 0; i < 5000; i++){
        int randIdxFrom = rand() % 100;
        cityFrom = cityNames[randIdxFrom];
        countryFrom = correspondingCountries[randIdxFrom];
        int randIdxTo = rand() % 100;
        while(randIdxFrom == randIdxTo){
            randIdxTo = rand() % 100;
        }
        cityTo = cityNames[randIdxTo];
        countryTo = correspondingCountries[randIdxTo];
        international = isInternational(randIdxFrom, randIdxTo);

        cout << "City from: " << cityFrom << ", " << countryFrom << endl
        << "Please enter the TZ difference from Greenwich as +/- the hours" << endl;
        cin >> TZF;
        cout << "City to: " << cityTo << ", " << countryTo << endl
                << "Please enter the TZ difference from Greenwich as +/- the hours" << endl;;
        cin >> TZT;

        response = "n";
        min = 50;
        max = 5000;
        while(response != "y"){
            price = makePrice(min, max);
            cout << "Is a price of: $" << price << " okay? Enter h, l, or y.\n";
            cin >> response;
            if(response == "h"){
                min += 250;
            }else{
                max = stoi(price) - 250;
            }
        }

        response = "n";
        min = 300;
        max = 10000;
        while(response != "y"){
            distance = makeDistance(min, max);
            cout << "Is a distance of " << distance << " miles okay? Enter h, l, or y.\n";
            cin >> response;
            if(response == "h"){
                min += 150;
            }else{
                max = stoi(distance) - 150;
            }
        }

        response = "n";
        min = 1;
        max = 30;
        while(response != "y"){
            dur = makeDuration(min, max);
            cout << "Is a duration of " << dur << " hours okay? Enter h, l, or y.\n";
            cin >> response;
            if(response == "h"){
                min += 2;
            }else{
                max = stoi(dur) - 2;
            }
        }

        TZdiff = makeTimeZoneDiff(TZF, TZT);

        response = "n";
        while(response != "y"){
            month = makeMonth();
            cout << "Is the month of " << month << " okay? Enter y or n.\n";
            cin >> response;
        }

        response = "n";
        while(response != "y"){
            depTime = makeDepartureTime();
            cout << "Is a departure time of " << depTime << " okay? Enter y or n.\n";
            cin >> response;
        }

        cout << "\nOkay. Adding line:\n";
        cout << cityFrom << "," << countryFrom << "," << cityTo << "," << countryTo << "," << price << distance << "," << dur << "," << TZdiff << month << depTime << international;

        cout << endl << endl;

    }
}


