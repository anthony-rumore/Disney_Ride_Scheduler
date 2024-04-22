#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
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

    int databaseSize = 6;
    vector<unordered_map<int, pair<int, int>>> TimeCount; // vector of RideName, map with key is the interval, value is the total waiting time and count

public:
    vector<DatabaseEntry> rideDatabase;
    unordered_map<string, minHeap> AvgMap;
    unordered_set<string> rideNames;

    // Constructor
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
        for(int i = 0; i < rideDatabase.size(); i++) { // loop through 6 RideNames
            for(auto RideData: rideDatabase[i].rideData) {
                // if the interval of time does not exist
                if(TimeCount[i].find((RideData.timeOfDay/5) * 5) == TimeCount[i].end()) {
                    TimeCount[i][(RideData.timeOfDay/5)*5] = make_pair(RideData.waitTime, 1);
                }
                // if it exists, add up to total of waiting time and increment count (for avg later)
                else {
                    TimeCount[i][(RideData.timeOfDay/5)*5].first += RideData.waitTime;
                    TimeCount[i][(RideData.timeOfDay/5)*5].second++;
                }
            }
        }
    }

    void AvgTimeofRide() {
        for(int i = 0; i < rideDatabase.size(); i++) { // loop through 6 rides
            minHeap theheap;
            // loop through each ride, calculate the average waiting time
            for (auto intervaltime = TimeCount[i].begin(); intervaltime != TimeCount[i].end(); intervaltime++) {
                theheap.InsertHeap(make_pair(intervaltime->first, (intervaltime->second.first / intervaltime->second.second)));
            }
            // add the average waiting time of each interval and store in a min heap
            AvgMap[rideDatabase[i].rideName] = theheap;
        }
    }

    // Returns the average wait times
    int getPopularityIndex(string rideName) {
        int sum = 0;
        int index = find(rideName);

        for (RideData rd : rideDatabase[index].rideData) {
            sum += rd.waitTime;
        }
        return sum / rideDatabase[index].rideData.size();
    }

    // Fills rideNames set with the name of each ride in RideDatabase
    void fillRideNames() {
        for (DatabaseEntry entry : rideDatabase) {
            rideNames.insert(entry.rideName);
        }
    }
};
