#include <raylib.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include <vector> 
#include <Utils.hpp>
#include <Block.hpp>

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

void SelectionSort(std::vector<Block>& blocks)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        Block block = blocks[i];
        for (size_t j = i; j < blocks.size() - i; j++)
        {
            if (blocks[j].Distance < block.Distance)
            {
                blocks[i] = blocks[j];
                blocks[j] = block;
            }
        }
    }
    return;
}