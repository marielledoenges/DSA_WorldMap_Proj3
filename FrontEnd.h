#include <SFML/Graphics.hpp>
#include "Flight.h"
using namespace std;

struct Screen {
    sf::RenderWindow createWindow(int width, int height, string title);
    void displayWindow(sf::RenderWindow& window);
    void drawBoardingPass(sf::RenderWindow& window, Flight& flight); // Method to draw a boarding pass
};
