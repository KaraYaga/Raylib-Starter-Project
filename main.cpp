#include "raylib.h"
#include <iostream>

using namespace std;

//Initialize
int main() {

    //Create Height, Width, Title of Window
    InitWindow(400, 300, "My first Raylib window!");
    SetTargetFPS(60);

    //Ball Stats
    int ballX = 150;
    int ballY = 150;
    int radius = 10;
    int ballspeedX = 2;
    int ballspeedY = 2;

    //Update Loop
    while (!WindowShouldClose()) 
    {
        ballX += ballspeedX;
        ballY += ballspeedY;

        if ((ballX + radius >= GetScreenWidth()) || (ballX - radius <= 0))
        {
            ballspeedX = -ballspeedX;
        }
        if ((ballY + radius >= GetScreenHeight()) || (ballY - radius <= 0))
        {
            ballspeedY = -ballspeedY;
        }

        //Drawing Loop
        BeginDrawing();
        ClearBackground(DARKGREEN);
        //Draw Here
        DrawCircle(ballX, ballY, 10, WHITE);
        DrawText("Let's Play PONG!", 120, 20, 20, WHITE);

        EndDrawing();
    }

    //End program and Clear
    CloseWindow();
    return 0;
}