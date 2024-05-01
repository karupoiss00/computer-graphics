#include <chrono>
#include <functional>
#include "GetFPS.h"

unsigned GetFPS()
{
    using namespace std::chrono;
    static int count = 0;
    static auto last = high_resolution_clock::now();
    auto now = high_resolution_clock::now();
    static unsigned fps = 0;

    count++;

    if (duration_cast<milliseconds>(now - last).count() > 1000) {
        fps = count;
        count = 0;
        last = now;
    }

    return fps;
}
