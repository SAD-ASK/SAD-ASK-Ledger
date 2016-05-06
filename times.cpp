#include "times.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <regex>

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

unsigned int convertDateToTimestamp(std::string date) {

  /* Regex matched
     Though the digits representing the year allow for 2-4 #s
     Should be 2 OR 4 numbers eg 16 or 2016 */

  std::string date_str =
    R"([\d]{1,2}[/-])" // Month and separator
    R"([\d]{1,2}[/-])" // Day and separator
    R"([\d]{2,4})"; // Year

  std::regex date_regex (date_str);

  if (std::regex_match(date, date_regex) )
    std::cout << "Regex matched!" << std::endl;
  else std::cout << "Nope! Shit..." << std::endl;

  return 0;
}
