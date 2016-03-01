#ifndef TIMES
#define TIMES
#include <string>

/* std::string promptTimeFetch
 * fetches time and returns as formatted string for prompt
 */
std::string promptTimeFetch();


/* std::size_t createTimestamp
 * returns unix timestamp
 */
unsigned int createTimestamp();

/* std::string getLocaltime
 * returns localtime, included in header to avoid unnecessary includes in other files
 */
std::string getLocaltime(unsigned int timestamp);

#endif // TIMES

