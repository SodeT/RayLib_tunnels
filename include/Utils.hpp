#ifndef UTILS_HPP
#define UTILS_HPP

#include <raylib.h>
#include <iostream>

#define pi 3.14159

const int Width = 649;
const int Height = 340;
const int HMid = Width / 2;
const int VMid = Height / 2;
const int Scale = 10;

float RadToDeg(float rad);
float DegToRad(float deg);
float GetAngle(Vector2 from, Vector2 to);
float GetDistance(Vector2 from, Vector2 to);

struct Line
{
    Vector2 From;
    Vector2 To;
};

struct MappedCorner
{
    float XOffset;
    float Distance;
};

struct Corner
{
    Vector2 Position;
    float Direction;
    float Distance;
};

struct Packet
{
    char state : 2; // 0 = await, 1 = playing, 2 = I won, 3 = you won
    char damage : 6;
    float x;
    float y;
}

#endif