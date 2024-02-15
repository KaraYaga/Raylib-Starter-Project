#include "raylib.h"
#include <iostream>

using namespace std;

//Initialize
int main() {

    //Font LIbrary
    Font ft = LoadFont("resources/fonts/pixantiqua.png");

    //Ball Stats
    int ballX = 100;
    int ballY = 100;
    int ballspeedX = 5;
    int ballspeedY = 5;
    int radius = 15;

    //Window State
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "PONG");
    SetTargetFPS(60);

    //Update Loop
    while (!WindowShouldClose()) 
    {
        //Drawing Loop
        BeginDrawing();
        ClearBackground(BLACK);
        //Title
        DrawTextEx(ft, "PONGO BONGO GOGO GIRL!", Vector2{75, 15}, 20, 3, PINK);

        //Ball
        ballX += ballspeedX;
        ballY += ballspeedY;

        if (ballX + radius >= screenWidth  || ballX - radius <= screenHeight)
        {
            ballspeedX *= -1;
        }
        if ((ballY + radius >= GetScreenHeight()) || (ballY - radius <= 0))
        {
            ballspeedY *= -1;
        }
        DrawCircle(ballX, ballY, radius, PINK);
 

        EndDrawing();
    }

    //End program and Clear
    CloseWindow();
    return 0;
}