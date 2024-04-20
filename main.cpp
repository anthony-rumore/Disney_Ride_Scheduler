#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "processData.h"

using namespace std;

vector<string> rideNames; // basic placeholder to help print the rides for the UI

void populateRideData() {
    // Data process goes here

    // Temporary list of rides:
    rideNames.push_back("Haunted Mansion");
    rideNames.push_back("Space Mountain");
    rideNames.push_back("Thunder Mountain");
    rideNames.push_back("it's a small world");
    rideNames.push_back("Jungle Cruise");
    rideNames.push_back("Pirates of the Caribbean");
    rideNames.push_back("Tomorrowland Speedway");
    rideNames.push_back("Tea Cups");
    rideNames.push_back("PeopleMover");
    rideNames.push_back("Mine Train");

    sort(rideNames.begin(), rideNames.end());
    // etc.
    // note this list is incomplete and this data will be populated from the data files later
}

int main() {

    cout << "Initializing data..." << endl;
    populateRideData();

    cout << "Welcome to MAKING YOUR DAY MAGICAL™ " << endl
         << "*The premier tool designed to help you craft the perfect Disney adventure!*" << endl << endl;

    cout << "Here's how it works: Below, you'll find a list of Magic Kingdom attractions, each assigned a unique number. " << endl
         << "To get started, simply type in the numbers corresponding to up to 6 attractions you're most excited about. " << endl << endl

         << "Our program will then generate a personalized schedule tailored to optimize your visit, " << endl
         << "helping you avoid long queues and will maximize your day." << endl << endl;

    for (int i = 0; i < rideNames.size(); i++) {
        cout << i + 1 << ". " << rideNames[i] << endl;
    }


    return 0;
}