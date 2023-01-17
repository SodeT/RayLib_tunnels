#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <raylib.h>

class Block 
{
    float width = 10;
public:
    Vector2 Positions[4];
    Block(float x, float z);
};

#endif