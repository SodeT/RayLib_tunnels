#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <Utils.hpp>
#include <raylib.h>

struct MappedCorner;
struct Corner;

class Block 
{
public:
    Vector2 Middle;
    float Distance;
    MappedCorner* VisibleCorners[3];
    Corner* Corners;
    MappedCorner* MappedCorners; 
    Block(float x, float z);
    ~Block();


    void SortCorners();
    void GetVisible();

};

#endif

