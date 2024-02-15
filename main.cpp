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

//Player Paddle
class Paddle1
{
public:
    float x, y;
    float width, height;
    int speed;

    //DRAW PADDLE
    void Draw() 
    {
        DrawRectangle(x, y, width, height, PINK);
    }

    //MOVE PADDLE
    void Update() 
    {
        if (IsKeyDown(KEY_W)) 
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_S))
        {
            y = y + speed;
        }
        //Boundaries
        if (y <= 0) 
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }
};

//Player Paddle
class Paddle2
{
public:
    float x, y;
    float width, height;
    int speed;

    //DRAW PADDLE
    void Draw()
    {
        DrawRectangle(x, y, width, height, PINK);
    }

    //MOVE PADDLE
    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }
        //Boundaries
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }
};

//Instances
Ball ball;
Paddle1 player1;
Paddle2 player2;

//INITIALIZE
int main() {
    
    //Window State
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "PONG");
    SetTargetFPS(60);

    //Font LIbrary
    Font ft = LoadFont("resources/fonts/pixantiqua.png");

    //Ball
    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = 7;
    ball.speedY = 7;

    //Paddle Player1
    player1.width = 25;
    player1.height = 120;
    player1.x = 20;
    player1.y = screenHeight / 2 - player1.height / 2;
    player1.speed = 6;

    //Paddle Player2
    player2.width = 25;
    player2.height = 120;
    player2.x = screenWidth - player2.width - 20;
    player2.y = screenHeight / 2 - player2.height / 2;
    player2.speed = 6;


    //Update Loop
    while (!WindowShouldClose()) 
    {
        //DRAWING LOOP
        BeginDrawing();

        //UPDATE LOOP
        ball.Update();
        player1.Update();
        player2.Update();

        ClearBackground(BLACK);//Clears Console Background between frames
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);//Middle Line
        ball.Draw();//Ball
        player1.Draw();//Player 1
        player2.Draw();//Player 2
        DrawTextEx(ft, "PONGO BONGO GOGO GIRL!", Vector2{ 500, 15 }, 20, 3, PINK);//Title


        //FINISH DRAWING
        EndDrawing();
    }

    //End program and Clear
    CloseWindow();
    return 0;
}