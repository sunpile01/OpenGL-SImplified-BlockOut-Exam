/**
* Brief description of the program:
* - Always one active transparent cube that you can:
*    - Move with arrow keys within the x and y coordinates of the 5*5*10 grid
*    - Move on section down with the 'X' key
*    - Press space to move the active cube all the way down to right above the 
*      topmost cube in that x and y coordinate or all the way down to the  
*      endwall if there are no solid cubes located in that x and y coordinate.
* 
* - Cubes become solid and placed right above if they are about to collide
*   with the conditions given in the last bullet point and lose transparency.
* - Each solid cubes has a color depending on the section they reside in.
* - Pressing 'L' will toggle the light on and off, with a lightsource 
*   interpolating between the start and end of the tunnel.
* - Pressing 'T' will toggle textures on and off. 
* 
* @author 
*/
#include "BlockOutApplication.h"

int main(int argc, char* argv[])
{
    Assignment application("BlockOut", "1.0");

    application.ParseArguments(argc, argv);
    application.Init();

    return application.Run();
}