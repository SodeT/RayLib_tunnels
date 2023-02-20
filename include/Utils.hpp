#ifndef UTILS_HPP
#define UTILS_HPP

#include <Block.hpp> 
#include <raylib.h>
#include <iostream>
#include <vector>

#define pi 3.14159

class Block;

const Color bg = {0, 0, 0, 255};
const Color fg = {255, 255, 255, 255};

const int Width = 640;
const int Height = 340;
const int HMid = Width / 2;
const int VMid = Height / 2;
const int Scale = 10;
const int WorldSize = 8;
const int World[WorldSize][WorldSize] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0} 
};

float RadToDeg(float rad);
float DegToRad(float deg);
float GetAngle(Vector2 from, Vector2 to);
float GetDistance(Vector2 from, Vector2 to);
void SelectionSort(std::vector<Block>& blocks);
//bool InsideSpan(ViewportSpan span, float x);

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

/*
struct ViewportSpan
{
    float From;
    float To;
};
*/

struct Packet
{
    char State : 2; // 0 = await, 1 = playing, 2 = I won, 3 = you won
    char Damage : 6;
    float x;
    float y;
};


#endif

