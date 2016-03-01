#include <ctime>
#include <iomanip>
#include "times.h"

std::string promptTimeFetch() {
    char timeString[24];
    std::time_t currentTime;
    std::time(&currentTime);

    std::strftime(timeString,sizeof(timeString), "%a, %b %d",std::localtime(&currentTime));
    return std::string(timeString);

}

unsigned int createTimestamp() {
    return std::time(NULL);
}


std::string getLocaltime(unsigned int timestamp) {
    char formattedTime[24];
    std::time_t timestamp_t = timestamp;
    std::strftime(formattedTime,sizeof(formattedTime), "%m/%d/%y %H:%M", std::localtime(&timestamp_t));
    return std::string(formattedTime);
}
