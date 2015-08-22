#include "angles.hxx"

float deg2rad(float deg) { return deg * M_PI / 180; }
float rad2deg(float rad) { return 180 * rad / M_PI; }

FPoint angle2dir(float degrees) {
    const float rad = deg2rad(degrees);
    return FPoint(cos(rad), sin(rad));
}

