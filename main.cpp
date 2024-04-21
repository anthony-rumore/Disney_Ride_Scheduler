#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "processData.h"
#include "Scheduler.h"

using namespace std;

int main() {

    RideDatabase db;
    vector<string> rideNames = {"Astro Orbiter", "The Barnstormer", "Big Thunder Mountain Railroad",
                                "Dumbo the Flying Elephant", "Enchanted Tales with Belle", "Haunted Mansion",
                                "It's a Small World", "Jungle Cruise", "Under the Sea ~ Journey of The Little Mermaid",
                                "The Magic Carpets of Aladdin", "Seven Dwarfs Mine Train", "Mad Tea Party",
                                "Prince Charming Regal Carrousel", "Tomorrowland Transit Authority PeopleMover",
                                "Pirates of the Caribbean", "Peter Pan's Flight", "Space Mountain",
                                "Buzz Lightyear's Space Ranger Spin", "Tomorrowland Speedway", "The Many Adventures of Winnie the Pooh"};

    cout << endl;
    cout << "Welcome to MAKING YOUR DAY MAGICAL™ " << endl
         << "*The premier tool designed to help you craft the perfect Disney adventure!*" << endl << endl;

    cout << "Here's how it works: Below, you'll find a list of Magic Kingdom attractions, each assigned a unique number. " << endl
         << "To get started, simply type in the numbers corresponding to up to 6 attractions you're most excited about. " << endl << endl

         << "Our program will then generate a personalized schedule tailored to optimize your visit, " << endl
         << "helping you avoid long queues and will maximize your day." << endl << endl;


    for (int i = 0; i < rideNames.size(); i++) {
        cout << i + 1 << ". " << rideNames[i] << endl;
    }

    const int NUM_RIDES = 6;

    string promptOrder[NUM_RIDES] = {"first", "second", "third", "fourth", "fifth", "sixth"};
    int rideIDs[NUM_RIDES];

    int inputCount = 0; // This will track how many valid, unique inputs have been entered.

    while (inputCount < NUM_RIDES) {
        string input;
        cout << endl;
        cout << "Enter your " << promptOrder[inputCount] << " ride selection: ";
        cin >> input;

        int input_num = 0;
        try {
            input_num = stoi(input);
        }
        catch (const std::invalid_argument& e) {
            // Not an integer!
            cout << "! !  That is not a valid number  ! !" << endl;
            continue; // Skip to the next iteration of the loop.
        }

        if (input_num > 20 || input_num < 1) { // Out of bounds!
            cout << "! !  Please select a ride from the list given above  ! !" << endl;
            continue; // Skip to the next iteration of the loop.
        }

        // Check for duplicates.
        bool isDuplicate = false;
        for (int j = 0; j < inputCount; j++) {
            if (rideIDs[j] == input_num) {
                // Duplicate ride detected!
                cout << "! !  You've already selected that ride  ! !" << endl;
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            rideIDs[inputCount++] = input_num; // Store the valid input and increment the count.
        }
    }

   // Loop through rideIds to fill RideDatabase with user's choices
   for (int i = 0; i < 6; i++) {
       processData(db, rideIDs[i]);
   }

   db.fillRideNames();
   db.getTotalTime();
   db.AvgTimeofRide();

    Scheduler scheduler = Scheduler(&db);
    const vector<string> &output = scheduler.scheduleDay();

    for (const string &line : output) {
        cout << line << endl;
    }

   return 0;

}