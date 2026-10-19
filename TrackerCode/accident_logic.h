#ifndef ASSET_TRACKER_ACCIDENT_LOGIC_H
#define ASSET_TRACKER_ACCIDENT_LOGIC_H

#include <math.h>

/** Map a 10-bit ADC reading to an accelerometer value in [outputMin, outputMax]. */
inline float mapPotentiometerToAccel(int raw, int rawMin = 0, int rawMax = 1023,
                                     int outputMin = -10, int outputMax = 10) {
    const float ratio = static_cast<float>(raw - rawMin) / static_cast<float>(rawMax - rawMin);
    return static_cast<float>(outputMin) + ratio * static_cast<float>(outputMax - outputMin);
}

/** Returns true when any axis exceeds the accident threshold. */
inline bool isAccidentDetected(float accelX, float accelY, float accelZ, float threshold) {
    return fabsf(accelX) > threshold || fabsf(accelY) > threshold || fabsf(accelZ) > threshold;
}

#endif
