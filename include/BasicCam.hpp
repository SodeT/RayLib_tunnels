#ifndef BASICCAM_HPP
#define BASICCAM_HPP

#include <vector>
#include <raylib.h>
#include <Block.hpp>

class BasicCam 
{

    std::vector<Block> _visibleCorners;
    std::vector<Vector2> _lineBuffer;

public:
    float Fov;
    float Direction = 0;

    Vector2 Position;

    BasicCam(float x, float z, float Fov);
    void GetVisibleCorners(std::vector<Block> blocks);
    
};

#endif