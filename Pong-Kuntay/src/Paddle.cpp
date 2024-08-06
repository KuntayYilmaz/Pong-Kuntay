#include "Paddle.h"

    Paddle::Paddle(float posX, float posY, float width, float height, int speed)
        :m_PosX{ posX }, m_PosY{ posY }, m_Width{ width }, m_Height{ height }, m_Speed{ speed }
    {
    }

    void Paddle::Draw() const
    {
        DrawRectangle(m_PosX, m_PosY, m_Width, m_Height, WHITE);
    }

    void Paddle::Update()
    {
        if (IsKeyDown(KEY_W) && m_PosY >= 20)
        {
            m_PosY = m_PosY - m_Speed;
        }
        if (IsKeyDown(KEY_S) && (m_PosY + m_Height) <= GetScreenHeight() - 20)
        {
            m_PosY = m_PosY + m_Speed;
        }
    }
