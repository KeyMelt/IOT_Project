#include "../TrackerCode/accident_logic.h"

#include <cassert>
#include <iostream>
#include <math.h>

int main() {
    assert(fabsf(mapPotentiometerToAccel(0) - (-10.0f)) < 0.01f);
    assert(fabsf(mapPotentiometerToAccel(1023) - 10.0f) < 0.01f);
    assert(fabsf(mapPotentiometerToAccel(512) - 0.0f) < 0.5f);

    assert(!isAccidentDetected(0.0f, 0.0f, 0.0f, 7.0f));
    assert(!isAccidentDetected(6.9f, -6.9f, 6.9f, 7.0f));
    assert(isAccidentDetected(7.1f, 0.0f, 0.0f, 7.0f));
    assert(isAccidentDetected(0.0f, -8.0f, 0.0f, 7.0f));
    assert(isAccidentDetected(0.0f, 0.0f, 7.01f, 7.0f));

    std::cout << "All accident_logic tests passed.\n";
    return 0;
}
