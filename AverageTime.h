#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "RideDatabase.h"
#include "theHeap.h"
using namespace std;

class AverageTime {
    RideDatabase db;
    vector<map<int, pair<int, int>>> TimeCount; // vector of RideName, map with key is the interval, value is the total waiting time and count
    map<string, minHeap> AvgMap;

public:
    void getTotalTime() {
        for(int i = 0; i < db.rideDatabase.size(); i++) { // each RideName
            for(auto RideData: db.rideDatabase[i].rideData) {
                if(TimeCount[i].find(RideData.timeOfDay/5) == TimeCount[i].end()) {
                    TimeCount[i][RideData.timeOfDay/5] = make_pair(RideData.waitTime, 1);
                }
                else {
                    TimeCount[i][RideData.timeOfDay/5].first += RideData.waitTime;
                    TimeCount[i][RideData.timeOfDay/5].second++;
                }
            }
        }
    }

    map<string, vector<pair<int, float>>> AvgTimeofRide() {
        for(int i = 0; i < db.rideDatabase.size(); i++) {
            minHeap theheap;
            for (auto intervaltime = TimeCount[i].begin(); intervaltime != TimeCount[i].end(); intervaltime++) {
                theheap.InsertHeap(make_pair(intervaltime->first, (intervaltime->second.first / intervaltime->second.second)));
            }
            AvgMap[db.rideDatabase[i].rideName] = theheap;
        }
    };

};


