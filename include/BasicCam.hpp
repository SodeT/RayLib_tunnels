#ifndef BASICCAM_HPP
#define BASICCAM_HPP

#include <vector>
#include <raylib.h>
#include <Block.hpp>
#include <Utils.hpp>

class BasicCam 
{
    std::vector<MappedCorner> _mappedCorners;
    std::vector<Line> _linebuffer;
    float _fovPixels;
    int _depthEffect = 700; // lower value => increase shrinking at distance
    float _speed = 0.4;
    float _rotationSpeed = 2;

public:
    Vector2 Position;
    float Fov;
    float Direction = 180;

    std::vector<Line> GetLinebuffer();

    BasicCam(float x, float z, float Fov);
    void GetCorners(std::vector<Block>& blocks);
    void MapToScreen(std::vector<Block>& blocks);
    void GenerateLinebuffer();
    void OccludeCorners();
    void HandleInput();

};

#endif