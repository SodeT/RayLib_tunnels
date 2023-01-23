#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <Utils.hpp>
#include <raylib.h>

class Block 
{
    float width = 1; // must be 1
public:
    Corner corners[4];
    Block(float x, float z);
};

#endif