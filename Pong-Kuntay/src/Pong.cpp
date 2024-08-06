#include "Pong.h"
#include <iostream>
#include "raylib.h"
#include "Settings.h"
#include "Ball.h"
#include "Paddle.h"
#include "ComputerPaddle.h"

namespace Pong 
{

    void Run() 
    {
        InitWindow(Settings::screenWidth, Settings::screenHeight, "Pong.Kuntay");
        SetTargetFPS(Settings::targetFPS);

        Ball mainBall{ Settings::screenWidth / 2, Settings::screenHeight / 2, 5, 5, 25.f };
        Paddle playerPaddle{ Settings::screenWidth - 25, Settings::screenHeight / 2 - 100, 25, 200, 5 };
        ComputerPaddle computerPaddle{ 0, Settings::screenHeight / 2 - 100, 25, 200, 6 };

        while (!WindowShouldClose()) 
        {
            // Update game logic
            Update(mainBall, playerPaddle, computerPaddle);

            // Render game
            Draw(mainBall, playerPaddle, computerPaddle);
        }

        CloseWindow();
    }



    void Update(Ball& mainBall, Paddle& playerPaddle, ComputerPaddle& computerPaddle) 
    {
        mainBall.Update();
        playerPaddle.Update();
        computerPaddle.Update(mainBall.GetPosY());

        // Collision Detection
        CheckCollisions(mainBall, playerPaddle, computerPaddle);
    }

    void CheckCollisions(Ball& mainBall, Paddle& playerPaddle, ComputerPaddle& computerPaddle) 
    {
        // Collision with Player
        if (CheckCollisionCircleRec(Vector2{ mainBall.GetPosX(), mainBall.GetPosY() },
            mainBall.GetRadius(),
            Rectangle{ playerPaddle.GetPosX(), playerPaddle.GetPosY(), playerPaddle.GetWidth(), playerPaddle.GetHeight() }))
        {
            mainBall.BounceBallOnX();
        }
        // Collision with Computer
        else if (CheckCollisionCircleRec(Vector2{ mainBall.GetPosX(), mainBall.GetPosY() },
            mainBall.GetRadius(),
            Rectangle{ computerPaddle.GetPosX(), computerPaddle.GetPosY(), computerPaddle.GetWidth(), computerPaddle.GetHeight() }))
        {
            mainBall.BounceBallOnX();
        }

        // Check for Scoring
        if (mainBall.GetPosX() < 0) 
        {
            Settings::playerScore++;
            mainBall.ResetBall();
        }
        else if (mainBall.GetPosX() > Settings::screenWidth) 
        {
            Settings::computerScore++;
            mainBall.ResetBall();
        }
    }

    void Draw(const Ball& mainBall, const Paddle& playerPaddle, const ComputerPaddle& computerPaddle) 
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw middle line
        DrawLine(Settings::screenWidth / 2, 0, Settings::screenWidth / 2, Settings::screenHeight, WHITE);

        // Draw Game Objects
        mainBall.Draw();
        playerPaddle.Draw();
        computerPaddle.Draw();

        // Draw Scores
        DrawText(TextFormat("%i", Settings::computerScore), Settings::screenWidth / 2 - 80, 20, 80, WHITE);
        DrawText(TextFormat("%i", Settings::playerScore), Settings::screenWidth / 2 + 40, 20, 80, WHITE);

        //Signature
        DrawText(TextFormat("Kuntay"), Settings::screenWidth / 2 - 75,Settings::screenHeight - 40 ,40,BLUE);

        EndDrawing();
    }
}
