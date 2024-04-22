# DSA_WorldMap_Proj3
100 cities around the world with various flight information available to manipulate.


#Flight and Travel Optimizers
Welcome to the Flight and Travel Optimizers application! This tool allows users to visually compare and explore flight options from various cities, displaying flight paths and details in an interactive graphical interface powered by SFML.

#Prerequisites
Before you can run the application, ensure you have the following installed on your system:
C++ Compiler (GCC or Clang recommended)
CMake (version 3.10 or higher)
SFML (version 2.5 or higher)

#Installation
Follow these steps to get the application up and running on your local machine:

#Clone the Repository:
Clone this repository to your local machine using git:
git clone https://github.com/FlightOptimizers/FlightApp.git cd FlightApp

#Install SFML:
On Ubuntu:
sudo apt-get install libsfml-dev

On macOS: Using Homebrew:
brew install sfml

On Windows:
Download the SFML binaries from SFML Downloads and extract them. Set up your environment variables to include the SFML lib directory or specify the path in your project settings.


#Build the Project
From the root directory of the project, create a build directory and navigate into it:
mkdir build && cd build

Run CMake to configure the project and generate a Makefile:
cmake ..

Now, build the project:
make

Running the Application
After building the project, you can run the application by executing:
./FlightApp

This command launches the application's main window, where you can interact with the map and view flight details.

#Usage
Interact with the Map: Click on any city node to display all outgoing flights.

View Flight Details: Select a flight path for detailed information such as price, duration, and stops.

Filter Options: Use the filter options to display only the flights that meet specific criteria like price range or number of stops.

#Troubleshooting
If you encounter issues with SFML not being found or library linking errors, ensure that SFML is installed correctly and paths are appropriately configured in the CMakeLists.txt file.
