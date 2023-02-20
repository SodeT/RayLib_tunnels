#include <Utils.hpp>

#include <Block.hpp>

#include <raylib.h>

#include <vector> 
#include <iostream>
#include <cmath>
#include <stdlib.h>

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
    Vector2 diff;
    diff.x = from.x - to.x;
    diff.y = from.y - to.y; 

    float c2 = pow(diff.x, 2) + pow(diff.y, 2);
    return std::sqrt(c2);
}

void prblk(std::vector<Block>& blocks)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        std::cout << "Distance " << blocks[i].Distance << "\n";
    }
    return;
}

void SelectionSort(std::vector<Block>& blocks) 
{ 
    size_t index; 
    for (size_t i = 0; i < blocks.size() -1; i++)
    {

        index = i; 
        for (size_t j = i+1; j < blocks.size(); j++)
        {
            if (blocks[j].Distance < blocks[index].Distance)
            {
                index = j;
            }
        }

        if (index!=i)
        {
            Block b = blocks[i];
            blocks[i] = blocks[index];
            blocks[index] = b;
        }
    }
    return;
} 

/*
bool InsideSpan(ViewportSpan span, float x)
{
    if (x > span.From && x < span.To)
    {
        return true;
    }
    return false;
}
*/


