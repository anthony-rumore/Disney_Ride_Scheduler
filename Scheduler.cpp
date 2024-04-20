//
// Created by AJ Rumore on 4/20/24.
//

#include "Scheduler.h"

pair<int, int> Scheduler::convertTimeToPair(int time) {
    if (time < 540 || time > 1260) // Invalid time
        return {-1, -1};

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

    hour = time / 60;
    minute = time % 60;

    if (hour > 11) {
        hour = hour % 12;
        if (hour == 0)
            hour = 12;
        dayHalf = "pm";
    }

    string minuteOffset = "";
    if (minute < 10)
        minuteOffset = "0";

    stringstream output;
    output << hour << ":" << minuteOffset << minute << dayHalf;
    return output.str();
}

void Scheduler::populateData() {

    // Get all the data for:
    // - SelectedRides
    // - ridePopularityIndexes
    // - lowestRideWaits
}

vector<string> Scheduler::scheduleDay() {
    queue<string> scheduleQueue;
    vector<string> outputText;

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

        scheduleQueue.emplace(selectedRide);
        ridesToQueue.erase(selectedRide);
    }

    // Schedule the rides
    while (!scheduleQueue.empty()) {
        string ride = scheduleQueue.front();
        minHeap &lowestWaits = lowestRideWaits[ride];

        bool scheduling = true;
        while (scheduling) {
            // Get time variables
            int startTime = lowestWaits.getMin().first;
            int lowestWait = (int) round(lowestWaits.getMin().second);
            int endTime = startTime + lowestWait + SCHEDULE_BUFFER;

            bool overlap = false;

            // Checks to see if the day is clear at those times
            for (int i = startTime; i < endTime; i += 5) {
                pair<int, int> arrayTime = convertTimeToPair(i);
                bool timeAvailable = !day[arrayTime.first][arrayTime.second];

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
            outputText.push_back(convertTimeToString(startTime) + " - " + ride); // TO-DO Wait time ETA? (~30 min wait)
            scheduling = false;
        }

        // Move on to the next ride to schedule
        scheduleQueue.pop();
    }

    return outputText;
}
