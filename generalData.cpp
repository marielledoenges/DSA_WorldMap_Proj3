#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "generalData.h"
#include <set>
using namespace std;


//base min 50, base max 5000
string WorldInfo::makePrice(int min, int max){
    int price = min;
    price += (rand() % max);
    return to_string(price);
}

//base min 300 base max 10,000
string WorldInfo::makeDistance(int min, int max) {
    int dist = (rand() % max);
    if(dist < min){
        dist += min;
    }
    return to_string(dist);

}

string WorldInfo::makeDuration(int min, int max) {
    int dur = min;
    dur += (rand() % max);
    return to_string(dur);
}

string WorldInfo::makeTimeZoneDiff(std::string from, std::string to){
    int fromidx = cityNamesMap.at(from);
    string fromTZ = TZdiff[fromidx];

    int toidx = cityNamesMap.at(to);
    string toTZ = TZdiff[toidx];

    string TZdiff;
    if(fromTZ[0] == '+' && toTZ[0] == '+'){
        int ftz = stoi(fromTZ);
        int ttz = stoi(toTZ);
        int diff = abs(ftz - ttz);
        TZdiff = to_string(diff);
        return TZdiff;
    }else if(fromTZ[0] == '-' && toTZ[0] == '+'){
        int ftz = stoi(fromTZ);
        int ttz = stoi(toTZ);
        int diff =  (abs(ftz) + ttz) % 15;
        TZdiff = to_string(diff);
        return TZdiff;
    }else if(fromTZ[0] == '+' && toTZ[0] == '-'){
        int ftz = stoi(fromTZ);
        int ttz = stoi(toTZ);
        int diff =  (ftz + abs(ttz)) % 15;
        TZdiff = to_string(diff);
        return TZdiff;
    }else if(fromTZ[0] == '-' && toTZ[0] == '-') {
        int ftz = stoi(fromTZ);
        int ttz = stoi(toTZ);
        int diff = abs(ftz - ttz);
        TZdiff = to_string(diff);
        return TZdiff;
    }
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
        return "yes";
    }
}

string WorldInfo::makeDate(string month) {
    string date;
    int temp;
    if(month == "feb"){
        temp = rand() % 28;
    }else{
        temp = rand() % 30;
    }
    date = to_string(temp);
    return date;
}

string WorldInfo::makeFlightNum() {
    int flightNum = rand() % 10000;
    string toRet = to_string(flightNum);

    if(toRet.length() == 1){
        toRet = "0000" + toRet;
    }else if(toRet.length() == 2){
        toRet = "000" + toRet;
    }else if(toRet.length() == 3){
        toRet = "00" + toRet;
    }else if(toRet.length() == 4){
        toRet = "0" + toRet;
    }

    return toRet;
}

bool WorldInfo::writeLine(string filename, string cityFrom, string countryFrom, string cityTo, string countryTo,
                          string price,string distance, string duration, string timeZoneDiff,
                          string month, string date, string departureTime, string international, string flightNum){

    ofstream file;
    file.open(filename, ios_base::app);
    file << cityFrom << ","
         << countryFrom << ","
         << cityTo << ","
         << countryTo << ","
         << price << ","
         << distance << ","
         << duration << ","
         << timeZoneDiff << ","
         << month << ","
         << date << ","
         << departureTime << ","
         << international << ","
         << flightNum << ","
         << endl;

    file.close();
    return true;
}

bool WorldInfo::writeFile(string filename){
    vector<vector<int>> kindaMat(100,std::vector<int>(100,0));
    set<int> allFlightNums;
    string response, cityFrom, cityTo, countryFrom, countryTo, price, distance, dur, TZdiff, month, depTime, international, date, flightNum;
    int min, max;
    for(int i = 0; i < 7200; i++){
        //getting the cities to work with
        //get random starting city
        int randIdxFrom = rand() % 100;

        //get random ending city
        int randIdxTo = rand() % 100;

        kindaMat[randIdxFrom][randIdxFrom] = 1;
        kindaMat[randIdxTo][randIdxTo] = 1;
        //if they already have a flight between themselves, get a different pair
        while(kindaMat[randIdxFrom][randIdxTo] == 1){
            randIdxTo = rand() % 100;
            randIdxFrom = rand() % 100;
        }

        //if not flight between them, set to yes there is a flight
        kindaMat[randIdxFrom][randIdxTo] = 1;

        cityFrom = cityNames[randIdxFrom];
        countryFrom = correspondingCountries[randIdxFrom];

        cityTo = cityNames[randIdxTo];
        countryTo = correspondingCountries[randIdxTo];

        international = isInternational(randIdxFrom, randIdxTo);
        TZdiff = makeTimeZoneDiff(cityFrom, cityTo);
        flightNum = makeFlightNum();
        int temp = stoi(flightNum);
        while(allFlightNums.find(temp) != allFlightNums.end()){
            flightNum = makeFlightNum();
            temp = stoi(flightNum);
        }

        if(TZdiff == "0"){
            min = 50;
        }else{
            min = 50 + ((stoi(TZdiff) - 1) * 200);
        }
        if(international == "no"){
            max = 400;
        }else if(stoi(TZdiff) >= 6){
            max = min + 1000;
        }else if(stoi(TZdiff) >= 3){
            max = min + 700;
        }else{
            max = min + 300;
        }
        price = makePrice(min, max);


        if(countryFrom == "USA" && countryTo == "USA" && TZdiff == "3"){
            cout << "within usa, 3h\n";
            min = 2000;
            max = 3000;
        }else if(countryFrom == "USA" && countryTo == "USA" && TZdiff == "2"){
            cout << "within usa, 2h\n";
            min = 1000;
            max = 2000;
        }else if(countryFrom == "USA" && countryTo == "USA" && (TZdiff == "1" || TZdiff == "1")){
            cout << "within usa, 1h\n";
            min = 50;
            max = 1000;
        }else if(international == "no" || TZdiff == "0"){
            if(TZdiff == "0"){
                cout << "no tz diff\n";
            }else{
                cout << "same country\n";
            }

            min = 50;
            max = 500;
        }else if(stoi(TZdiff) <= 3){
            cout << "tz diff less than or eq to 3 h\n";
            min = 100;
            max = 2000;
        }else if(stoi(TZdiff) <= 5){
            cout << "tz diff less than or eq to 5 h\n";
            min = 2000;
            max = 6000;
        }else{
            cout << "tz diff larger than 5 h\n";
            min = 6000;
            max = 9000;
        }
        distance = makeDistance(min, max);


        if(TZdiff == "1" || TZdiff == "0"){
            min = 1;
            max = 3;
        }else if(stoi(TZdiff) < 3){
            min = 2;
            max = 4;
        }else if(stoi(TZdiff) < 5){
            min = 4;
            max = 6;
        }else if(stoi(TZdiff) < 7){
            min = 7;
            max = 10;
        }else{
            min = 11;
            max = 18;
        }
        dur = makeDuration(min, max);
        month = makeMonth();

        depTime = makeDepartureTime();
        date = makeDate(month);

        cout << cityFrom << ", " << countryFrom << " to " << cityTo << ", " << countryTo << " for $" << price << ", flying over " <<  distance << " miles , lasting " << dur << " hours, " << TZdiff << " hours apart" <<  endl;
        bool success = writeLine("proj3DataTEST.csv", cityFrom, countryFrom, cityTo, countryTo, price, distance, dur, TZdiff, month, date, depTime, international, flightNum);
        cout << endl;

    }
}





