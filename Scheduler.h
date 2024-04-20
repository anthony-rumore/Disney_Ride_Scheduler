//
// Created by AJ Rumore on 4/20/24.
//

#ifndef DISNEY_RIDE_SCHEDULER__SCHEDULER_H
#define DISNEY_RIDE_SCHEDULER__SCHEDULER_H

#include <utility>
#include <vector>
#include <sstream>

using namespace std;

class Scheduler {
private:
    bool day[12][12];
public:
    pair<int, int> convertTimeToPair(int time);
    string convertTimeToString(int time);

    vector<string> scheduleDay();
};


#endif //DISNEY_RIDE_SCHEDULER__SCHEDULER_H
