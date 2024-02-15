#include "raylib.h"
#include <iostream>

using namespace std;
//BALL
class Ball 
{
public:
    float x, y;
    int speedX, speedY;
    int radius;

    //DRAW BALL
    void Draw() 
    {
        DrawCircle(x, y, radius, WHITE);
    }
    //MOVE BALL
    void Update() 
    {
        x += speedX;
        y += speedY;

        //Check Collisions
        if (y + radius >= GetScreenHeight() || y - radius <= 0) 
        {
            speedY *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speedX *= -1;
        }
    }
};

//Ball Instance
Ball ball;

//INITIALIZE
int main() {
    
    //Window State
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "PONG");
    SetTargetFPS(60);

    //Font LIbrary
    Font ft = LoadFont("resources/fonts/pixantiqua.png");

    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = 7;
    ball.speedY = 7;

    //Update Loop
    while (!WindowShouldClose()) 
    {
        //DRAWING LOOP
        BeginDrawing();

        //UPDATE LOOP
        ball.Update();

        ClearBackground(BLACK);//Clears Console Background between frames
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);//Middle Line
        ball.Draw();//Ball
        DrawRectangle(20, screenHeight/2 - 60, 25, 120, PINK); //Left Paddle
        DrawRectangle(screenWidth - 45, screenHeight / 2 - 60, 25, 120, PINK); //Right Paddle
        DrawTextEx(ft, "PONGO BONGO GOGO GIRL!", Vector2{ 500, 15 }, 20, 3, PINK);//Title


        //FINISH DRAWING
        EndDrawing();
    }

    //End program and Clear
    CloseWindow();
    return 0;
}