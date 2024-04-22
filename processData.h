#include <iostream>
#include <fstream>
#include <sstream>
#include "RideDatabase.h"

using namespace std;

// Returns true if inputTime is between 9:00 and 21:00
bool validateTime(string inputTime) {
    stringstream stream(inputTime);
    string data;
    int timeToValidate;

    getline(stream, data, ':');
    timeToValidate = stoi(data);

    if (timeToValidate > 8 && timeToValidate < 21) {
        return true;
    }

    return false;
}

// Converts inputTime from "09:01:00" format to an int representation in minutes
int convertTime(string inputTime) {
    stringstream stream(inputTime);
    string data;
    int minutes = 0;

    getline(stream, data, ':');
    minutes += (stoi(data) * 60);
    getline(stream, data, ':');
    minutes += stoi(data);

    return minutes;
}

// Reads one data file and enters each row of data into RideDatabase
void readFile(RideDatabase& rides, string fileName) {
    ifstream file(fileName);
    string data;
    int convertedTime;

    struct RideData rideData;
    struct DatabaseEntry entry;

    if (!file.is_open()) {
        throw runtime_error("File failed to open.");
    }

    file.ignore(500,'\n' );

    while (getline(file, data, ',')) {
        entry.rideName = data;
        getline(file, data, ' ');
        getline(file, data, ',');

        // If the timeOfDay is not between 9:00AM-9:00PM, do not add to database
        if (!validateTime(data)) {
            getline(file, data, '\n');
            continue;
        }

        // If the time is valid, convert it to an int in minutes
        convertedTime = convertTime(data);
        rideData.timeOfDay = convertedTime;
        getline(file, data, '\n');
        rideData.waitTime = stoi(data);
        entry.rideData[0] = rideData;
        rides.insert(entry);
    }
}

// Based on user's rideChoice, inserts the data from that file into RideDatabase
void processData (RideDatabase& rides, int rideChoice) {
    switch(rideChoice) {
        case 1:  // AO
            readFile(rides, "../Data/Feb-AO.csv");
            readFile(rides, "../Data/Jan-AO.csv");
            break;
        case 2:  // BS
            readFile(rides, "../Data/Feb-BS.csv");
            readFile(rides, "../Data/Jan-BS.csv");
            break;
        case 3:  // BTM
            readFile(rides, "../Data/Feb-BTM.csv");
            readFile(rides, "../Data/Jan-BTM.csv");
            break;
        case 4:  // DFE
            readFile(rides, "../Data/Feb-DFE.csv");
            readFile(rides, "../Data/Jan-DFE.csv");
            break;
        case 5:  // ETB
            readFile(rides, "../Data/Feb-ETB.csv");
            readFile(rides, "../Data/Jan-ETB.csv");
            break;
        case 6:  // HM
            readFile(rides, "../Data/Feb-HM.csv");
            readFile(rides, "../Data/Jan-HM.csv");
            break;
        case 7:  // ISM
            readFile(rides, "../Data/Feb-ISM.csv");
            readFile(rides, "../Data/Jan-ISM.csv");
            break;
        case 8:  // JC
            readFile(rides, "../Data/Feb-JC.csv");
            readFile(rides, "../Data/Jan-JC.csv");
            break;
        case 9:  // LM
            readFile(rides, "../Data/Feb-LM.csv");
            readFile(rides, "../Data/Jan-LM.csv");
            break;
        case 10:  // MCA
            readFile(rides, "../Data/Feb-MCA.csv");
            readFile(rides, "../Data/Jan-MCA.csv");
            break;
        case 11:  // MT
            readFile(rides, "../Data/Feb-MT.csv");
            readFile(rides, "../Data/Jan-MT.csv");
            break;
        case 12:  // MTP
            readFile(rides, "../Data/Feb-MTP.csv");
            readFile(rides, "../Data/Jan-MTP.csv");
            break;
        case 13:  // PCC
            readFile(rides, "../Data/Feb-PCC.csv");
            readFile(rides, "../Data/Jan-PCC.csv");
            break;
        case 14:  // PM
            readFile(rides, "../Data/Feb-PM.csv");
            readFile(rides, "../Data/Jan-PM.csv");
            break;
        case 15:  // POC
            readFile(rides, "../Data/Feb-POC.csv");
            readFile(rides, "../Data/Jan-POC.csv");
            break;
        case 16:  // PPF
            readFile(rides, "../Data/Feb-PPF.csv");
            readFile(rides, "../Data/Jan-PPF.csv");
            break;
        case 17:  // SM
            readFile(rides, "../Data/Feb-SM.csv");
            readFile(rides, "../Data/Jan-SM.csv");
            break;
        case 18:  // SRS
            readFile(rides, "../Data/Feb-SRS.csv");
            readFile(rides, "../Data/Jan-SRS.csv");
            break;
        case 19:  // TSW
            readFile(rides, "../Data/Feb-TSW.csv");
            readFile(rides, "../Data/Jan-TSW.csv");
            break;
        case 20:  // WTP
            readFile(rides, "../Data/Feb-WTP.csv");
            readFile(rides, "../Data/Jan-WTP.csv");
            break;
    }
}
