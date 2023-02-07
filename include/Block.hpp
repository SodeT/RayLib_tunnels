#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <Utils.hpp>
#include <raylib.h>

class Block 
{
public:
    Vector2 Middle;
    float Distance;
    MappedCorner* VisibleCorners[3];
    Corner Corners[4];
    MappedCorner MappedCorners[4]; 
    Block(float x, float z);

    void SortCorners();

};

#endif