#ifndef CORE_H
#define CORE_H
#include "profile.h"

/* class Core
 * Testing: Merging core functionality into a main class
 */
class Core {
public:

    // Constructer only calls menuLoop
    Core();
    ~Core();

    // Starts main menu
    void menuLoop();

private:
    Profile loadedProfile;

};
#endif // CORE_H
