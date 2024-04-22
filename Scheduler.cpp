#include "Scheduler.h"

pair<int, int> Scheduler::convertTimeToPair(int time) {
    if (time < 540 || time > 1260) {// Invalid time
        cout << "[Scheduler Error] ! !  INVALID TIME DETECTED  ! !" << endl;
        return {-1, -1};
    }

    // Converts time to hours after 9am and 5-minute intervals in the hour
    int hour, minuteInterval;
    int timeAfterNine = time - 540;

    hour = timeAfterNine / 60;
    minuteInterval = (timeAfterNine % 60) / 5;

    return {hour, minuteInterval};
}

string Scheduler::convertTimeToString(int time) {
    if (time < 540 || time > 1260) // Invalid time
        return "Invalid Time";

    int hour, minute;
    string dayHalf = "am";

    // Converts integer time to hours and minutes
    hour = time / 60;
    minute = time % 60;

    // Handles pm conversion
    if (hour > 11) {
        hour = hour % 12;
        if (hour == 0)
            hour = 12;
        dayHalf = "pm";
    }

    // Makes sure single digit minutes lead with 0
    string minuteOffset = "";
    if (minute < 10)
        minuteOffset = "0";

    // Formats output string
    stringstream output;
    output << hour << ":" << minuteOffset << minute << dayHalf;
    return output.str();
}

void Scheduler::populateData() {
    // Get all the data for:
    // - SelectedRides
    selectedRides = db->rideNames;

    // - ridePopularityIndexes
    for (const string& ride : selectedRides)
        ridePopularityIndexes[ride] = db->getPopularityIndex(ride);

    // - lowestRideWaits
    lowestRideWaits = &db->AvgMap;
}

vector<string> Scheduler::scheduleDay() {
    queue<string> scheduleQueue; // Rides in-order of popularity to schedule
    vector<string> outputText; // Text to return and print later
    map<int, string> rideSchedule; // Sorts text to go into outputText

    unordered_set<string> ridesToQueue = selectedRides; // copy rides

    // Queue all the rides in order of popularity
    while (!ridesToQueue.empty()) {
        int largestRPI = -1;
        string selectedRide;

        // Select ride w/ the largest popularity index
        for (string ride : ridesToQueue) {
            int rpi = ridePopularityIndexes[ride];
            if (rpi > largestRPI) {
                largestRPI = rpi;
                selectedRide = ride;
            }
        }

        // Adds ride to queue and removes it from rides to add to the queue
        scheduleQueue.push(selectedRide);
        ridesToQueue.erase(selectedRide);
    }

    // Schedule the rides
    while (!scheduleQueue.empty()) {
        string ride = scheduleQueue.front();
        minHeap &lowestWaits = lowestRideWaits->operator[](ride);

        bool scheduling = true;
        while (scheduling) {
            // Get time variables
            int startTime = lowestWaits.getMin().first;

            int lowestWait = (int) round(lowestWaits.getMin().second);
            if (lowestWait % 5 != 0) // Round to nearest 5-minute interval
                lowestWait += 5 - (lowestWait % 5);

            int endTime = startTime + lowestWait + SCHEDULE_BUFFER;
            if (endTime > 1260) // Does not account past 9pm
                endTime = 1260;

            bool overlap = false;

            // Checks to see if the day is clear at those times
            for (int i = startTime; i < endTime; i += 5) {
                pair<int, int> arrayTime = convertTimeToPair(i);
                bool timeAvailable = !day[arrayTime.first][arrayTime.second];

                // Checks for an overlap
                if (!timeAvailable) {
                    overlap = true;
                    break;
                }
            }

            // Resolve time conflict
            if (overlap) {
                // Removes the min wait time because that time doesn't work
                lowestWaits.extractMin();

                // Check to make sure it's not empty
                if (lowestWaits.theheap.empty()) {
                    outputText.push_back("COULD NOT SCHEDULE: " + ride);
                    scheduleQueue.pop();
                }

                // Re-run the loop to find next best time in queue
                // or next ride if no more in wait queue
                continue;
            }

            // Blocks off the times
            for (int i = startTime; i < endTime; i += 5) {
                pair<int, int> arrayTime = convertTimeToPair(i);
                day[arrayTime.first][arrayTime.second] = true;
            }

            // Add ride to schedule text for the output
            rideSchedule[startTime] = (convertTimeToString(startTime) + " - " + ride + " - ~" + to_string(lowestWait) + " minute wait");
            scheduling = false;
        }

        // Move on to the next ride to schedule
        scheduleQueue.pop();
    }

    // Return output; one line per string
    for (auto &ride : rideSchedule)
        outputText.push_back(ride.second);

    return outputText;
}