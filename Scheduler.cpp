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

vector<string> Scheduler::scheduleDay() {
    return vector<string>();
}
