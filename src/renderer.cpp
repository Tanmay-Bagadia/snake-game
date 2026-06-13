#include "renderer.h"
#include <iostream>
#include <sstream>
#include <vector>

void Renderer::draw(const Game &game)
{
    int w = game.getWidth();
    int h = game.getHeight();

    // Build lookup grid: 0=empty, 1=wall, 2=head, 3=body, 4=apple
    std::vector<std::vector<int>> grid(h + 1, std::vector<int>(w + 1, 0));

    for (int x = 1; x <= w; x++) { grid[1][x] = 1; grid[h][x] = 1; }
    for (int y = 1; y <= h; y++) { grid[y][1] = 1; grid[y][w] = 1; }

    const auto &snake = game.getSnake();
    for (size_t i = 0; i < snake.size(); i++)
        grid[snake[i].y][snake[i].x] = (i == 0) ? 2 : 3;

    Point apple = game.getApple();
    grid[apple.y][apple.x] = 4;

    // ANSI color codes
    const char *C_WALL  = "\033[38;5;240m";
    const char *C_HEAD  = "\033[92m";
    const char *C_BODY  = "\033[32m";
    const char *C_APPLE = "\033[91m";
    const char *C_SCORE = "\033[97m";
    const char *C_DIM   = "\033[90m";
    const char *RESET   = "\033[0m";

    std::ostringstream buf;
    buf << "\033[H";

    buf << "\n " << C_SCORE << " S N A K E" << RESET << "\n\n";

    for (int y = 1; y <= h; y++)
    {
        buf << " ";
        for (int x = 1; x <= w; x++)
        {
            switch (grid[y][x])
            {
            case 1:  buf << C_WALL  << "██"; break;
            case 2:  buf << C_HEAD  << "██"; break;
            case 3:  buf << C_BODY  << "▓▓"; break;
            case 4:  buf << C_APPLE << "██"; break;
            default: buf << "  "; break;
            }
        }
        buf << RESET << "\n";
    }

    buf << "\n " << C_SCORE << " Score: " << game.getScore()
        << RESET << "    "
        << C_DIM << "WASD/Arrows to move  |  Q to quit" << RESET << "\n";

    std::cout << buf.str() << std::flush;
}