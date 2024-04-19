#include <fstream>
#include <sstream>
#include "RideDatabase.h"

using namespace std;

bool validateTime(string inputTime) {
    // Only want to insert times between 9:00 and 21:00
    // String input format = "07:32:27"
    stringstream stream(inputTime);
    string data;
    int timeToValidate;

    getline(stream, data, ':');
    timeToValidate = stoi(data);

    if (timeToValidate > 8 && timeToValidate < 22) {
        return true;
    }
    return false;
}

// Reads one data file and enters each row of data into RideDatabase
void readFile(RideDatabase& rides, string& fileName) {

    ifstream file(fileName);
    string data;

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
        rideData.timeOfDay = data;
        getline(file, data, '\n');
        rideData.waitTime = stoi(data);
        entry.rideData[0] = rideData;

        // Validate timeOfDay before inserting
        if (validateTime(rideData.timeOfDay)) {
            rides.insert(entry);
        }
    }
}

// Input: 6 ints to represent user's ride choices
// Only process data files that correspond to the user's choices
void processData(RideDatabase& rides, int& rideChoice) {
    //int choice = 1;
    switch(rideChoice) {
        case 1:  // AO
            readFile(rides, (string &) "Data/Feb-AO.csv");
            readFile(rides, (string &) "Data/Jan-AO.csv");
            break;
        case 2:  // BS
            readFile(rides, (string &) "Data/Feb-BS.csv");
            readFile(rides, (string &) "Data/Jan-BS.csv");
            break;
        case 3:  // BTM
            readFile(rides, (string &) "Data/Feb-BTM.csv");
            readFile(rides, (string &) "Data/Jan-BTM.csv");
            break;
        case 4:  // DFE
            readFile(rides, (string &) "Data/Feb-DFE.csv");
            readFile(rides, (string &) "Data/Jan-DFE.csv");
            break;
        case 5:  // ETB
            readFile(rides, (string &) "Data/Feb-ETB.csv");
            readFile(rides, (string &) "Data/Jan-ETB.csv");
            break;
        case 6:  // HM
            readFile(rides, (string &) "Data/Feb-HM.csv");
            readFile(rides, (string &) "Data/Jan-HM.csv");
            break;
        case 7:  // ISM
            readFile(rides, (string &) "Data/Feb-ISM.csv");
            readFile(rides, (string &) "Data/Jan-ISM.csv");
            break;
        case 8:  // JC
            readFile(rides, (string &) "Data/Feb-JC.csv");
            readFile(rides, (string &) "Data/Jan-JC.csv");
            break;
        case 9:  // LM
            readFile(rides, (string &) "Data/Feb-LM.csv");
            readFile(rides, (string &) "Data/Jan-LM.csv");
            break;
        case 10:  // MCA
            readFile(rides, (string &) "Data/Feb-MCA.csv");
            readFile(rides, (string &) "Data/Jan-MCA.csv");
            break;
        case 11:  // MT
            readFile(rides, (string &) "Data/Feb-MT.csv");
            readFile(rides, (string &) "Data/Jan-MT.csv");
            break;
        case 12:  // MTP
            readFile(rides, (string &) "Data/Feb-MTP.csv");
            readFile(rides, (string &) "Data/Jan-MTP.csv");
            break;
        case 13:  // PCC
            readFile(rides, (string &) "Data/Feb-PCC.csv");
            readFile(rides, (string &) "Data/Jan-PCC.csv");
            break;
        case 14:  // PM
            readFile(rides, (string &) "Data/Feb-PM.csv");
            readFile(rides, (string &) "Data/Jan-PM.csv");
            break;
        case 15:  // POC
            readFile(rides, (string &) "Data/Feb-POC.csv");
            readFile(rides, (string &) "Data/Jan-POC.csv");
            break;
        case 16:  // PPF
            readFile(rides, (string &) "Data/Feb-PPF.csv");
            readFile(rides, (string &) "Data/Jan-PPF.csv");
            break;
        case 17:  // SM
            readFile(rides, (string &) "Data/Feb-SM.csv");
            readFile(rides, (string &) "Data/Jan-SM.csv");
            break;
        case 18:  // SRS
            readFile(rides, (string &) "Data/Feb-SRS.csv");
            readFile(rides, (string &) "Data/Jan-SRS.csv");
            break;
        case 19:  // TSW
            readFile(rides, (string &) "Data/Feb-TSW.csv");
            readFile(rides, (string &) "Data/Jan-TSW.csv");
            break;
        case 20:  // WTP
            readFile(rides, (string &) "Data/Feb-WTP.csv");
            readFile(rides, (string &) "Data/Jan-WTP.csv");
            break;
    }
}
