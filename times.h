#ifndef TIMES
#define TIMES
#include <ctime>
#include <string>

std::string promptTimeFetch() {
    char timeString[24];
    std::time_t currentTime;
    std::time(&currentTime);

    std::strftime(timeString,sizeof(timeString), "%a, %b %d",std::localtime(&currentTime));
    return std::string(timeString);

}

#endif // TIMES

