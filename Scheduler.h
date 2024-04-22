#ifndef DISNEY_RIDE_SCHEDULER__SCHEDULER_H
#define DISNEY_RIDE_SCHEDULER__SCHEDULER_H

#include <utility>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>

#include "RideDatabase.h"
#include "theHeap.h"

using namespace std;

class Scheduler {
private:
    bool day[12][12] = {}; // All elements should be false
    RideDatabase* db;
    unordered_set<string> selectedRides;
    unordered_map<string, int> ridePopularityIndexes;
    unordered_map<string, minHeap>* lowestRideWaits;

    // 15-minute buffer between end of wait and next ride
    const int SCHEDULE_BUFFER = 15;

    void populateData();

public:
    pair<int, int> convertTimeToPair(int time);
    string convertTimeToString(int time);

    vector<string> scheduleDay();

    Scheduler(RideDatabase* db) {
        this->db = db;
        populateData();
    }
};

#endif //DISNEY_RIDE_SCHEDULER__SCHEDULER_H
