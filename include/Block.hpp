#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <Utils.hpp>
#include <raylib.h>

class Block 
{

public:
    Corner Corners[4];
    MappedCorner MappedCorners[4]; 
    Block(float x, float z);
};

#endif