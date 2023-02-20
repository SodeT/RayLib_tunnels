#include <Block.hpp>
#include <BasicCam.hpp>
#include <Utils.hpp>

#include <raylib.h>

#include <vector>
#include <iostream>

#include <unistd.h>

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
        cam.OccludeCorners(blocks);
        cam.GenerateLineBuffer(blocks);
        cam.DrawCall();
        cam.HandleInput();

        usleep((16.666 - GetFrameTime()) * 1000 * 1); // cap fps to 60
                                    //             ^  this is some slowmo
                                    
        DrawLine(HMid, VMid - 10, HMid, VMid + 10, RED); // debug line
        DrawLine(HMid - 10, VMid, HMid + 10, VMid, RED); // debug line


        BeginDrawing();
        ClearBackground(bg);
        EndDrawing();

    }

    return 0;
}

