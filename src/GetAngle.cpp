#include <raylib.h>
#include <cmath>
#include <Utils.hpp>

float GetAngle(Vector2 from, Vector2 to)
{
    float xDiff = from.x - to.x;
    float zDiff = from.y - to.y;

    float radAngle = std::atan(zDiff/ xDiff);
    float degAngle = RadToDeg(radAngle);

    return degAngle;
}