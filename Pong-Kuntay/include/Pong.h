#include "Ball.h"
#include "Paddle.h"
#include "ComputerPaddle.h"

namespace Pong 
{
    void Run();

    void Update(Ball& mainBall, Paddle& playerPaddle, ComputerPaddle& computerPaddle);

    void CheckCollisions(Ball& mainBall, Paddle& playerPaddle, ComputerPaddle& computerPaddle);

    void Draw(const Ball& mainBall, const Paddle& playerPaddle, const ComputerPaddle& computerPaddle);
}