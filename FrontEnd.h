#include <SFML/Graphics.hpp>
using namespace std;

struct Screen{

    //Screen();
    sf::RenderWindow createWindow(int width, int height, string title);
    void displayWindow(sf::RenderWindow& window);
};