#include "ComputerPaddle.h"

    ComputerPaddle::ComputerPaddle(float posX, float posY, float width, float height, int speed)
        :Paddle{ posX,posY,width,height,speed }
    {
    }

    void ComputerPaddle::Update(int ballPosY) //Movement algorithm for computer paddle
    {
        if ((m_PosY + (m_Height / 2)) < ballPosY && m_PosY + m_Height < GetScreenHeight() - 100) 
        {
            m_PosY = m_PosY + m_Speed;
        }

        if ((m_PosY + (m_Height / 2)) > ballPosY && m_PosY > 100)
        {
            m_PosY = m_PosY - m_Speed;
        }
    }

