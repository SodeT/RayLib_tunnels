#include <Block.hpp>
#include <raylib.h>

Block::Block(float x, float z) 
{

        /* #region cube corners */

        Positions[0].x = x;
        Positions[0].y = z;

        Positions[1].x = x + width;
        Positions[1].y = z;

        Positions[2].x = x;
        Positions[2].y = z + width;

        Positions[3].x = x + width;
        Positions[4].y = z + width;

        /* #endregion */
}
