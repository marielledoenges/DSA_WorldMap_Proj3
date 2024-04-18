#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
using namespace std;

class WorldInfo{
private:
    unordered_map<string, int> cityNamesMap = {{"Tampa", 0}, {"Gainesville", 1}, {"Paris", 2}, {"London", 3}, {"New York", 4},
                                               {"Miami", 5}, {"Washington DC", 6}, {"Seattle", 7}, {"Las Vegas", 8}, {"Los Angeles", 9},
                                               {"Houston", 10}, {"Austin", 11}, {"Dallas", 12}, {"Atlanta", 13}, {"Charleston", 14},
                                               {"Bonn", 15}, {"Buenos Aires", 16}, {"Lima", 17}, {"Mar Del Plata", 18}, {"Okinawa", 19},
                                               {"Madrid", 20}, {"Valencia", 21}, {"Sevilla", 22}, {"Copenhagen", 23}, {"Stockholm", 24},
                                               {"Oslo", 25}, {"Shanghai", 26}, {"Dubai", 27}, {"Rome", 28}, {"Milan", 29},
                                               {"Nice", 30}, {"Frankfurt", 31},  {"Berlin", 32}, {"Moscow", 33}, {"Sao Paulo", 34},
                                               {"Mexico City", 35}, {"Chicago", 36}, {"Toronto", 37}, {"Quebec", 38}, {"Kansas City", 39},
                                               {"Juneau", 40}, {"Mumbai", 41}, {"New Dehli", 42}, {"Bangkok", 43}, {"Hong Kong", 44},
                                               {"Sydney", 45}, {"Melbourne", 46}, {"Beijing", 47}, {"Taipei", 48}, {"Seoul", 49},
                                               {"Nagasaki", 50}, {"Tokyo", 51}, {"Baghdad", 52}, {"Jerusalem", 53}, {"Istanbul", 54},
                                               {"Athens", 55}, {"Budapest", 56}, {"Vienna", 57}, {"Sofia", 58}, {"Kyiv",59},
                                               {"Warsaw", 60}, {"Minsk", 61}, {"Amsterdam", 62}, {"Zurich", 63}, {"Brussels", 64},
                                               {"St. Tropez", 65}, {"Naples", 66}, {"Ibiza", 67},  {"Tunis", 68}, {"Lisbon", 69},
                                               {"Dublin", 70}, {"Glasgow", 71},  {"Edinburgh", 72}, {"Malmo", 73}, {"Helsinki", 74},
                                               {"Bergen", 75}, {"St. Petersburg", 76}, {"Reykjavik", 77}, {"Panama City", 78}, {"Medellin", 79},
                                               {"Bogota", 80}, {"Quito", 81}, {"Caracas", 82}, {"Brasilia", 83}, {"Santiago", 84},
                                               {"Montevideo", 85}, {"San Juan", 86}, {"Havana", 87}, {"Cairo", 88}, {"Marrakesh", 89},
                                               {"Abuja", 90}, {"Nairobi", 91}, {"Zanzibar", 92}, {"Cape Town", 93}, {"Prague",94},
                                               {"San Fransisco", 95}, {"Honolulu", 96}, {"Santorini", 97}, {"Madeira", 98}, {"Oporto", 99}};

    vector<string> cityNames = {"Tampa", "Gainesville", "Paris", "London", "New York",
                                "Miami", "Washington DC", "Seattle", "Las Vegas", "Los Angeles",
                                "Houston", "Austin", "Dallas", "Atlanta", "Charleston",
                                "Bonn", "Buenos Aires", "Lima", "Mar Del Plata", "Okinawa",
                                "Madrid", "Valencia", "Sevilla", "Copenhagen", "Stockholm",
                                "Oslo", "Shanghai", "Dubai", "Rome", "Milan",
                                "Nice", "Frankfurt", "Berlin", "Moscow", "Sao Paulo",
                                "Mexico City", "Chicago", "Toronto", "Quebec", "Kansas City",
                                "Juneau", "Mumbai", "New Dehli", "Bangkok", "Hong Kong",
                                "Sydney", "Melbourne", "Beijing", "Taipei", "Seoul",
                                "Nagasaki", "Tokyo", "Baghdad", "Jerusalem", "Istanbul",
                                "Athens", "Budapest", "Vienna", "Sofia", "Kyiv",
                                "Warsaw", "Minsk", "Amsterdam", "Zurich", "Brussels",
                                "St. Tropez", "Naples", "Ibiza", "Tunis", "Lisbon",
                                "Dublin", "Glasgow", "Edinburgh", "Malmo", "Helsinki",
                                "Bergen", "St. Petersburg", "Reykjavik", "Panama City", "Medellin",
                                "Bogota", "Quito", "Caracas", "Brasilia", "Santiago",
                                "Montevideo", "San Juan", "Havana", "Cairo", "Marrakesh",
                                "Abuja", "Nairobi", "Zanzibar", "Cape Town", "Prague",
                                "San Fransisco", "Honolulu", "Santorini", "Madeira", "Oporto"};

    vector<string> TZdiff = {"-4", "-4", "+2", "+1", "-4",
                             "-4", "-4", "-7", "-7", "-7",
                             "-5", "-5", "-5", "-4", "-4",
                             "+2", "-3", "-5", "-3", "+9",
                             "+2", "+2", "+2", "+2", "+2",
                             "+2", "+8", "+4", "+2", "+2",
                             "+2", "+2", "+2", "+3", "-3",
                             "-6", "-5", "-4", "-4", "-5",
                             "-8", "+5", "+5", "+7", "+8",
                             "+10", "+10", "+8", "+8", "+9",
                             "+9", "+9", "+3", "+3", "+3",
                             "+3", "+2", "+2", "+3", "+3",
                             "+2", "+3", "+2", "+2", "+2",
                             "+2", "+2", "+2", "+1", "+1",
                             "+1", "+1", "+1", "+2", "+3",
                             "+2", "+3", "+0", "-5", "-5",
                             "-5", "-5", "-4", "-3", "-4",
                             "-3", "-4", "-4", "+2", "+1",
                             "+1", "+3", "+3", "+2", "+2",
                             "-7", "-10", "+3", "+1", "+1"};
    vector<string> correspondingCountries = {"USA", "USA", "France", "England", "USA",
                                             "USA", "USA", "USA", "USA", "USA",
                                             "USA", "USA", "USA", "USA", "USA",
                                             "Germany", "Argentina", "Peru", "Argentina", "Japan",
                                             "Spain", "Spain", "Spain", "Denmark", "Sweden",
                                             "Norway", "China", "United Arab Emirates", "Italy", "Italy",
                                             "France", "Germany", "Germany", "Russia", "Brazil",
                                             "Mexico", "USA", "Canada", "Canada", "USA",
                                             "USA", "India", "India", "Thailand", "China",
                                             "Australia", "Australia", "China", "Taiwan", "South Korea",
                                             "Japan", "Japan", "Iraq", "Israel", "Turkyie",
                                             "Greece", "Hungary", "Austria", "Bulgaria", "Ukraine",
                                             "Poland", "Belarus", "Netherlands", "Switzerland", "Belgium",
                                             "France", "Italy", "Spain", "Tunisia", "Portugal",
                                             "Ireland", "Scotland", "Scotland", "Sweden", "Finland",
                                             "Norway", "Russia", "Iceland", "Panama", "Colombia",
                                             "Colombia", "Ecuador", "Venezuela", "Brazil", "Chile",
                                             "Uruguay", "Puerto Rico", "Cuba", "Egypt", "Morocco",
                                             "Nigeria", "Kenya", "Tanzania", "South Africa", "Chzechia",
                                             "USA", "USA", "Greece", "Portugal", "Portugal"};

    vector<string> months = {"January", "February", "March", "April",
                             "May", "June", "July", "August",
                             "September", "October", "November", "December"};

public:
    bool writeLine(string filename, string cityFrom, string countryFrom, string cityTo, string countryTo,
                   string price,string distance, string duration, string timeZoneDiff,
                   string month, string date, string departureTime, string international);

    bool writeFile(string filename);
    bool readFile(string filename);
    string makePrice(int min, int max);
    string makeDistance(int min, int max);
    string makeDuration(int min, int max);
    string makeTimeZoneDiff(string fromTZ, string toTZ);
    string makeMonth();
    string makeDepartureTime();
    string isInternational(int idxFrom, int idxTo);
    string makeDate(string month);
    void print(){

    }

};

