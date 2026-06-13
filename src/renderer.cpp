#include "renderer.h"
#include <iostream>

void Renderer::draw(const Game &game)
{

    std::cout << "\033[2J\033[H";

    for (int x = 1; x <= game.getWidth(); x++)
    {
        std::cout << "\033[1;" << x << "H-";
        std::cout << "\033[" << game.getHeight() << ";" << x << "H-";
    }

    for (int y = 1; y <= game.getHeight(); y++)
    {
        std::cout << "\033[" << y << ";1H|";
        std::cout << "\033[" << y << ";" << game.getWidth() << "H|";
    }

    Point apple = game.getApple();
    std::cout << "\033[" << apple.y << ";" << apple.x << "H" << "A";

    const std::deque<Point> &snake = game.getSnake();
    for (size_t i = 0; i < snake.size(); i++)
    {
        std::cout << "\033[" << snake[i].y << ";" << snake[i].x << "H";
        if (i == 0)
        {
            std::cout << "@";
        }
        else
        {
            std::cout << "O";
        }
    }

    std::cout << std::flush;
}
