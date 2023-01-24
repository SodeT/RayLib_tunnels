#include <Utils.hpp>
#include <raylib.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

float RadToDeg(float rad)
{
    return rad * (180/pi);
}

float DegToRad(float deg)
{
    return deg / (180/pi);
}

float GetAngle(Vector2 from, Vector2 to)
{
    float xDiff = to.x - from.x;
    float zDiff = to.y - from.y;

    float radAngle = std::atan2(zDiff, xDiff);
    float degAngle = RadToDeg(radAngle);

    return degAngle;
}

float GetDistance(Vector2 from, Vector2 to)
{
    float xDiff = from.x - to.x;
    float zDiff = from.y - to.y; 

    float c2 = xDiff * xDiff + zDiff * zDiff;
    return std::sqrt(c2);
}