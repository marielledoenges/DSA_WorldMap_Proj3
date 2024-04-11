#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class WorldInfo{
private:
    vector<string> cityNames = {"Tampa", "Gainesville", "Paris", "London", "New York",
                                "Miami", "Washington DC", "Seattle", "Las Vegas", "Los Angeles",
                                "Houston", "Austin", "Dallas", "Atlanta", "Charleston",
                                "Bonn", "Buenos Aires", "Lima", "Mar Del Plata", "Okinawa",
                                "Madrid", "Valencia", "Sevilla", "Copenhagen", "Stockholm",
                                "Oslo", "Shanghai", "Dubai", "Rome", "Milan",
                                "Nice", "Frankfurt", "Berlin", "Moscow", "Sao Paolo",
                                "Mexico City", "Chicago", "Toronto", "Quebec", "Kansas City",
                                "Juneau", "Mumbai", "New Dehli", "Bangkok", "Hong Kong",
                                "Sydney", "Melbourne", "Beijing", "Taipei", "Seoul",
                                "Nagasaki", "Tokyo", "Baghdad", "Jerusalem", "Istanbul",
                                "Athens", "Budapest", "Vienna", "Sofia", "Kyiv", "Warsaw",
                                "Minsk", "Amsterdam", "Zurich", "Brussels", "St. Tropez",
                                "Naples", "Ibiza", "Tunis", "Lisbon", "Dublin",
                                "Glasgow", "Edinburgh", "Malmo", "Helsinki", "Bergen",
                                "St. Petersburg", "Reykjavik", "Panama City", "Medellin",
                                "Bogota", "Quito", "Caracas", "Brasilia", "Santiago",
                                "Montevideo", "San Juan", "Havana", "Cairo", "Marrakesh",
                                "Abuja", "Nairobi", "Zanzibar", "Cape Town", "Prague",
                                "San Fransisco", "Honolulu", "Santorini", "Madeira", "Oporto"};


    vector<string> correspondingCountries = {"USA", "USA", "France", "England", "USA",
                                             "USA", "USA", "USA", "USA", "USA",
                                             "USA", "USA", "USA", "USA", "USA",
                                             "Germany", "Argentina", "Peru", "Argentina", "Japan",
                                             "Spain", "Spain", "Spain", "Denmark", "Sweden",
                                             "Norway", "China", "Unied Arab Emirates", "Italy", "Italy",
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
                                             "USA", "USA", "Greece", "Portugal", "Oporto"};

    vector<string> months = {"January", "February", "March", "April",
                             "May", "June", "July", "August",
                             "September", "October", "November", "December"};

public:
    bool writeLine(string filename, string cityFrom, string countryFrom, string cityTo, string countryTo,
                   string price,string distance, string duration, string timeZoneDiff,
                   string month, string departureTime, string international);

    bool writeFile(string filename);
    bool readFile(string filename);
    string makePrice(int min, int max);
    string makeDistance(int min, int max);
    string makeDuration(int min, int max);
    string makeTimeZoneDiff(string fromTZ, string toTZ);
    string makeMonth();
    string makeDepartureTime();
    string isInternational(int idxFrom, int idxTo);
    void print(){

    }

};

