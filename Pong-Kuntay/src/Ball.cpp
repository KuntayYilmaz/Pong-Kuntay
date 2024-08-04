#include "Ball.h"
#include "Settings.h"
#include "raylib.h"

    Ball::Ball(float posX, float posY, float speedX, float speedY, float radius)
        :m_PosX{ posX }, m_PosY{ posY }, m_SpeedX{ speedX }, m_SpeedY{ speedY }, m_Radius{ radius }
    {
    }

    void Ball::ResetBall()
    {
        m_PosX = GetScreenWidth() / 2;
        m_PosY = GetScreenHeight() / 2;

        int speed_choices[2]{ -5,5 };

        m_SpeedX = speed_choices[GetRandomValue(0, 1)];
        m_SpeedY = speed_choices[GetRandomValue(0, 1)];

    }

    void Ball::Draw() const
    {
        DrawCircle(m_PosX, m_PosY, m_Radius, WHITE);
    }

    void Ball::Update()
    {
        if (m_PosY + m_Radius >= GetScreenHeight() || m_PosY - m_Radius <= 0) //LIMITS THE MOVEMENT OF THE BALL TO THE SCREEN
        {
            m_SpeedY *= -1;
        }

        if (m_PosX + m_Radius >= GetScreenWidth()) //COMPUTER SCORES
        {
            ResetBall();
            Settings::computerScore++;
        }
        else if (m_PosX - m_Radius <= 0) //PLAYER SCORES
        {
            ResetBall();
            Settings::playerScore++;
        }

        m_PosX += m_SpeedX;
        m_PosY += m_SpeedY;
    }

    void Ball::BounceBallOnX() //IF ONE OF THE PADDLES CATCH THE BALL GETS FASTER
    {
        m_SpeedX *= -1;
        if (m_SpeedX < 0) { m_SpeedX -= 0.5f; }
        else if (m_SpeedX > 0) { m_SpeedX += 0.5f; }

        if (m_SpeedY < 0) { m_SpeedY -= 0.5f; }
        else if (m_SpeedY > 0) { m_SpeedY += 0.5f; }
    }
