#include "Pong.h"
#include <iostream>
#include "raylib.h"
#include "Settings.h"
#include "Ball.h"
#include "Paddle.h"
#include "ComputerPaddle.h"

void Pong::Run()
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Pong.Kuntay");
    SetTargetFPS(Settings::targetFPS);
    Ball mainBall{ Settings::screenWidth / 2,Settings::screenHeight / 2,5,5,25.f };
    Paddle playerPaddle{ Settings::screenWidth - 25,Settings::screenHeight / 2 - 100, 25, 200, 5 };
    ComputerPaddle computerPaddle{ 0, Settings::screenHeight / 2 - 100, 25, 200 ,6 };

    while (WindowShouldClose() == false)
    {
        //UPDATING
        mainBall.Update();
        playerPaddle.Update();
        computerPaddle.Update(mainBall.GetPosY());

        //CHECKING FOR COLLISION WITH PLAYER
        if (CheckCollisionCircleRec(Vector2{ mainBall.GetPosX(),mainBall.GetPosY() },
            mainBall.GetRadius(),
            Rectangle{ playerPaddle.GetPosX(),playerPaddle.GetPosY(),playerPaddle.GetWidth(),playerPaddle.GetHeight() }))
        {
            mainBall.BounceBallOnX();
        }
        //CHECKING FOR COLLISION WITH COMPUTER
        else if (CheckCollisionCircleRec(Vector2{ mainBall.GetPosX(),mainBall.GetPosY() },
            mainBall.GetRadius(),
            Rectangle{ computerPaddle.GetPosX(),computerPaddle.GetPosY(),computerPaddle.GetWidth(),computerPaddle.GetHeight() }))
        {
            mainBall.BounceBallOnX();
        }


        //DRAWING

        BeginDrawing();

        ClearBackground(BLACK);
        DrawLine(Settings::screenWidth / 2, 0, Settings::screenWidth / 2, Settings::screenHeight, WHITE);

        mainBall.Draw();
        playerPaddle.Draw();
        computerPaddle.Draw();

        DrawText(TextFormat("%i", Settings::computerScore), Settings::screenWidth / 2 - 80, 20, 80, WHITE);
        DrawText(TextFormat("%i", Settings::playerScore), Settings::screenWidth / 2 + 40, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
}
