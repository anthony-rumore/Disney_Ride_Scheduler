#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#pragma once
#include "theHeap.h"
using namespace std;

// Struct to hold each row of a ride's data (timeOfDay, waitTime)
struct RideData {
    int timeOfDay;
    int waitTime;

    RideData() {
        this->timeOfDay = 0;
        this->waitTime = 0;
    }

    RideData(int& timeOfDay, int& waitTime) {
        this->timeOfDay = timeOfDay;
        this->waitTime = waitTime;
    }
};

// Struct to hold key-value pairs that will be inserted into RideDatabase
struct DatabaseEntry {
    string rideName;  // rideName = key
    vector<RideData> rideData;  // vector of RideData structs = value

    DatabaseEntry() {
        this->rideName = "";
        this->rideData = vector<RideData>(1);
    }

    DatabaseEntry(string& rideName, int& timeOfDay, int& waitTime) {
        this->rideName = rideName;
        this->rideData = {RideData(timeOfDay, waitTime)};
    }
};

// Hash table will be implemented as a vector of DatabaseEntry structs
class RideDatabase {

    int databaseSize = 8;
    double loadFactor = 0.75;

    vector<map<int, pair<int, int>>> TimeCount; // vector of RideName, map with key is the interval, value is the total waiting time and count

    // Hash function
    //int hash() {}

    // Rehash function to increase database size
    void rehash() {}

public:
    vector<DatabaseEntry> rideDatabase;
    map<string, minHeap> AvgMap;
    unordered_set<string> rideNames;
    RideDatabase() {
        TimeCount.resize(6);
    }

    // Returns true if rideDatabase contains an entry with key = rideName
    bool contains(string& rideName) {
        for (int i = 0; i < rideDatabase.size(); i++) {
            if (rideDatabase[i].rideName == rideName) {
                return true;
            }
        }
        return false;
    }

    // Returns the index of key = rideName
    int find(string& rideName) {
        for (int i = 0; i < rideDatabase.size(); i++) {
            if (rideDatabase[i].rideName == rideName) {
                return i;
            }
        }
    }

    // Inserts one row of data from a .csv file
    void insert(DatabaseEntry entry) {
        // If ride is not already in rideDatabase, add entire entry
        if (!contains(entry.rideName)) {
            rideDatabase.push_back(entry);
        }
        // If ride is already in rideDatabase, add entry's RideData struct to vector
        else {
            int index = find(entry.rideName);
            rideDatabase[index].rideData.push_back(entry.rideData[0]);
        }
    }

    void getTotalTime() {
        for(int i = 0; i < rideDatabase.size(); i++) { // each RideName
            for(auto RideData: rideDatabase[i].rideData) {
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

    void AvgTimeofRide() {
        for(int i = 0; i < rideDatabase.size(); i++) {
            minHeap theheap;
            for (auto intervaltime = TimeCount[i].begin(); intervaltime != TimeCount[i].end(); intervaltime++) {
                theheap.InsertHeap(make_pair(intervaltime->first, (intervaltime->second.first / intervaltime->second.second)));
            }
            AvgMap[rideDatabase[i].rideName] = theheap;
        }
    }

    int getPopularityIndex(string& rideName) {
        // Traverse each Entry in database
        // Add up all of the waitTimes and divide by the total number of
        return 0;
    }

    void fillRideNames() {
        for (DatabaseEntry entry : rideDatabase) {
            rideNames.emplace(entry.rideName);
        }
    }

};
