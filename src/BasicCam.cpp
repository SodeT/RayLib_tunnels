#include <raylib.h>
#include <BasicCam.hpp>
#include <stdlib.h>
#include <Utils.hpp>

BasicCam::BasicCam(float x, float z, float Fov) 
    :Position({x, z}), Fov(Fov) 
{

}

void BasicCam::GetVisibleCorners(std::vector<Block> blocks)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            Vector2 blockPos = blocks[i].Positions[j];
            float cornerAngle = GetAngle(blockPos, Position);
            float relativeAngle = cornerAngle - Direction - Fov/2;
            
            if (relativeAngle < 0 && relativeAngle > Fov)
            {
                continue;
            }

            _visibleCorners.push_back(blocks[i]);
        }
    }
    return;
}
/*
void BasicCam::Get
*/