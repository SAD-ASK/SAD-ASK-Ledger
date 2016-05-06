#ifndef TIMES
#define TIMES
#include <string>

/* std::string promptTimeFetch
 * fetches time and returns as formatted string for prompt
 */
std::string promptTimeFetch();


/* unsigned int createTimestamp
 * returns unix timestamp
 */
unsigned int createTimestamp();

/* std::string getLocaltime
 * returns localtime, included in header to avoid unnecessary includes in other files
 */
std::string getLocaltime(unsigned int timestamp);

/* unsigned int convertDateToTimestamp
 * Converts a date string to unix timestamp
 */
unsigned int convertDateToTimestamp(std::string date);

#endif // TIMES

