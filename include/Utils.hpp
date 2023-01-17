#ifndef UTILS_HPP
#define UTILS_HPP

#include <raylib.h>
#include <iostream>

#define pi 3.14159
#define log(x) std::cout << x << "\n";

float RadToDeg(float rad);
float GetAngle(Vector2 from, Vector2 to);
float DegToRad(float deg);

#endif