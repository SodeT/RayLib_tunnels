#include <iostream>
#include <vector>
#include <raylib.h>
#include <unistd.h>

#include <Utils.hpp>
#include <Block.hpp>
#include <BasicCam.hpp>

Color bg = {0, 0, 0, 255};
Color fg = {255, 255, 255, 255};

int main() 
{
    InitWindow(Width, Height, "title");

    std::vector<Block> blocks;

    for (int y = 0; y < 8; y++) 
    {
        for (int x = 0; x < 8; x++) 
        {
            if (World[y][x] == 1)
            {
                blocks.emplace_back(x, y);
            }
        }
    }

    BasicCam cam(3, 3, 90);

    while (!WindowShouldClose())
    {

        cam.GetCorners(blocks);
        cam.MapToScreen(blocks);
        cam.GenerateLinebuffer();
        std::vector<Line> linebuffer = cam.GetLinebuffer(blocks);

        for (size_t i = 0; i < blocks.size(); i++)
        {
            for (int j = 0; j < 4; j++)
            {
                Line line = linebuffer[i];
                DrawLine(line.From.x, line.From.y, line.To.x, line.To.y, fg);
            }
        }
        cam.HandleInput();

        usleep((16.666 - GetFrameTime()) * 1000 * 1); // cap fps to 60
                                    //             ^  this is some slowmo

                                    
        DrawLine(HMid, VMid - 10, HMid, VMid - 1, RED); // debug line
        DrawLine(HMid, VMid + 10, HMid, VMid + 1, RED); // debug line
        DrawLine(HMid - 10, VMid, HMid - 1, VMid, RED); // debug line
        DrawLine(HMid + 10, VMid, HMid + 1, VMid, RED); // debug line

        BeginDrawing();
        ClearBackground(bg);
        EndDrawing();

    } 
}