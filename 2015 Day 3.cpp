// 2015 Day 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
* --- Day 3: Perfectly Spherical Houses in a Vacuum ---
Santa is delivering presents to an infinite two-dimensional grid of houses.

He begins by delivering a present to the house at his starting location, and then an elf at the North Pole calls him via radio and tells him where to move next. Moves are always exactly one house to the north (^), south (v), east (>), or west (<). After each move, he delivers another present to the house at his new location.

However, the elf back at the north pole has had a little too much eggnog, and so his directions are a little off, and Santa ends up visiting some houses more than once. How many houses receive at least one present?

For example:

> delivers presents to 2 houses: one at the starting location, and one to the east.
^>v< delivers presents to 4 houses in a square, including twice to the house at his starting/ending location.
^v^v^v^v^v delivers a bunch of presents to some very lucky children at only 2 houses.
*/
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::cout;
using std::cin;



int main()
{
	int xPos;
	int yPos;
	char newHeading;
	int presentsDelivered = 0;
	std::vector<std::string> posTracker; //tracks unique x,y coordinates
	std::vector<int> visitsTracker; //tracks number of visits to a coordinate

	/*
	* Open text file
	*/
	std::string filename = "Directions.txt";
	std::ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;

		exit(1);
	}

	/*
	* Set starting position to 0,0 and deliver first present
	*/
	xPos = 0;
	yPos = 0;
	presentsDelivered += 1;
	posTracker.push_back("0, 0");
	visitsTracker.push_back(1);

	/*
	* Pull directions from text file and store in a vector
	*/
	// Below line reads contents of the text file into a string variable
	//std::string fileContents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
	
	// While loop to get each character in the text file
	while (inputFile.get(newHeading)) {
		if (newHeading == '^') {
			// go North... y+=1
			yPos += 1;
		}
		else if (newHeading == '>') {
			// go East... x+=1
			xPos += 1;
		}
		else if (newHeading == 'v') {
			// go South... y-=1
			yPos -= 1;
		}
		else if (newHeading == '<') {
			// go West... x-=1
			xPos -= 1;
		}
		else {
			// Something has gone wrong...
			std::cerr << "Something has gone wrong pulling characters from the file... " << std::endl << "######## Bad char: " << newHeading << std::endl;
			exit(1);
		}

		presentsDelivered += 1;

		std::string xStr = std::to_string(xPos);
		std::string yStr = std::to_string(yPos);

		std::string currentCoords = xStr + ", " + yStr;
		//cout << "Current coordinates in vector: " << currentCoords << std::endl;

		// Reset coordsExist to false for next check
		bool coordsExist = false;
		
		// check posTracker vector to see if the x,y coords already exist
		for (int i = 0; i <= posTracker.size() - 1; i++) {
			// coordinates exist
			if (posTracker[i] == currentCoords) {
				coordsExist = true;
				visitsTracker[i] += 1;

				cout << "Existing coordinates: " << currentCoords << " ... Times visited: " << visitsTracker[i] << std::endl;

				break; // end the for loop as a matching coordinate has been found
			}
		}

		// add new coords if matching coords were not found
		if (!coordsExist) {
			// coordinates do not already exist in the vector... add new coordinates to vector tracking coordinates and visits
			posTracker.push_back(currentCoords); // add new coordinate to posTracker
			visitsTracker.push_back(1); // add new value to visistsTracker starting at 1 visit

			cout << "New coordinate: " << currentCoords << std::endl;
		}
	}

	// output unique houses delivered to
	cout << "Unique houses visited (houses that received at least 1 gift): " << posTracker.size() << std::endl;
	cout << "Total gifts delivered: " << presentsDelivered << std::endl;
}

/*
* Create a sorting class...
* 
* Tracking for X, Y pos
* Tracking for whether a location has been visited
* 
*/
class House {
	int xPos;
	int yPos;
	int timesVisited;

};