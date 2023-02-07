#include <raylib.h>
#include <stdlib.h>
#include <cmath>

#include <BasicCam.hpp>
#include <Utils.hpp>
#include <Block.hpp>

BasicCam::BasicCam(float x, float z, float Fov) 
    : Position({x * Scale, z * Scale}), Fov(Fov) 
{
    _fovPixels = Width / Fov;
}

void BasicCam::GetCorners(std::vector<Block>& blocks)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        blocks[i].Distance = GetDistance(blocks[i].Middle, Position);
        for (size_t j = 0; j < 4; j++)
        {
            Vector2 cornerPos = blocks[i].Corners[j].Position;
            float cornerAngle = GetAngle(cornerPos, Position);
            float relativeAngle = cornerAngle + Direction;

            blocks[i].Corners[j].Direction = relativeAngle;

            float distance = GetDistance(cornerPos, Position);
            blocks[i].Corners[j].Distance = distance;
        }
    }
    return;
}

void BasicCam::MapToScreen(std::vector<Block>& blocks)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            MappedCorner mCorner;
            mCorner.Distance = blocks[i].Corners[j].Distance;
            float dir = blocks[i].Corners[j].Direction;
            if (dir > 180)
                dir -= 360;

            mCorner.XOffset = HMid + dir * _fovPixels;

            blocks[i].MappedCorners[j] = mCorner;
        }
        blocks[i].SortCorners();
    }
    return;
}

void BasicCam::OccludeCorners(std::vector<Block>& blocks)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        blocks[i].VisibleCorners[0] = &blocks[i].MappedCorners[0];
        blocks[i].VisibleCorners[2] = &blocks[i].MappedCorners[3];
        if (blocks[i].MappedCorners[1].Distance > blocks[i].MappedCorners[0].Distance)
        {
            blocks[i].VisibleCorners[1] = &blocks[i].MappedCorners[1];
        }
        else if (blocks[i].MappedCorners[2].Distance > blocks[i].MappedCorners[0].Distance)
        {
            blocks[i].VisibleCorners[1] = &blocks[i].MappedCorners[2];   
        }
    }

    SelectionSort(blocks);

    return;
}

void BasicCam::GenerateLineBuffer(std::vector<Block>& blocks)
{
    _lineBuffer.clear();
    for (size_t i = 0; i < blocks.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float height = _depthEffect / blocks[i].MappedCorners[j].Distance;
            float offset = blocks[i].MappedCorners[j].XOffset;
            if (offset > HMid)
            {
                offset -= Width;
            }

            Line line;
            line.From = {blocks[i].MappedCorners[j].XOffset, VMid - height};
            line.To = {blocks[i].MappedCorners[j].XOffset, VMid + height};
            _lineBuffer.push_back(line);
        }
    }

    return;
}


void BasicCam::DrawCall()
{
    for (size_t i = 0; i < _lineBuffer.size(); i++)
    {
        Line line = _lineBuffer[i];
        if ((line.From.x > Width && line.To.x < 0) || (line.From.x < 0 && line.To.x > Width))
        {
            continue;
        }

        DrawLine(line.From.x, 
                line.From.y, 
                line.To.x, 
                line.To.y, fg);
    }
    return;
}

void BasicCam::HandleInput()
{

    if (IsKeyDown(KEY_UP))
    {
        _velocity.x = -cos(DegToRad(Direction)) * _speed;
        _velocity.y = sin(DegToRad(Direction)) * _speed;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        _velocity.x = -cos(DegToRad(Direction)) * -_speed;
        _velocity.y = sin(DegToRad(Direction)) * -_speed;
    }
    else
    {
        _velocity.x *= _friction;
        _velocity.y *= _friction;

        if (abs(_velocity.x) < 0.001)
            _velocity.x = 0;
        if (abs(_velocity.y) < 0.001)
            _velocity.y = 0;
    }

    Vector2 tempPos = Position;
    tempPos.x += _velocity.x;
    tempPos.y += _velocity.y;

    int gridX = (int)tempPos.x / Scale;
    int gridY = (int)tempPos.y / Scale;

    // Collision detection in world map
    if (gridX >= 0 && gridX < WorldSize && gridY >= 0 && gridY < WorldSize)
    {
        if (World[gridY][gridX] != 1)
        {
            Position = tempPos;
        }
        else
        {
            _velocity = {0, 0};
        }
    }
    else 
    {
        Position = tempPos;   
    }

    // Rotation
    if (IsKeyDown(KEY_LEFT))
    {
        Direction += _rotationSpeed;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        Direction -= _rotationSpeed;
    }

    if (Direction > 360)
    {
        Direction -= 360;
    }
    else if (Direction < 0)
    {
        Direction += 360;
    }

    return;
}