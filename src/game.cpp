#include "game.h"
#include <cstdlib>

Game::Game(int w, int h)
{

    width = w;
    height = h;

    current_dir = RIGHT;
    game_over = false;

    int start_x = width / 2;
    int start_y = height / 2;

    // length 3 snake
    snake.push_back({start_x, start_y});     // Head
    snake.push_back({start_x - 1, start_y}); // Body
    snake.push_back({start_x - 2, start_y}); // Tail

    spawnApple();
}

void Game::spawnApple()
{
    bool valid_pos = false;

    int temp_x;
    int temp_y;

    while (!valid_pos)
    {

        temp_x = (rand() % (width - 2)) + 1;
        temp_y = (rand() % (height - 2)) + 1;

        valid_pos = true;

        for (int i = 0; i < snake.size(); i++)
        {
            if (snake[i].x == temp_x && snake[i].y == temp_y)
            {
                valid_pos = false;
                break;
            }
        }
    }
    apple.x = temp_x;
    apple.y = temp_y;
}

void Game::setDirection(Direction d)
{
    if (current_dir == STOP)
    {
        current_dir = d;
        return;
    }

    if (current_dir + d == 0)
    {
        return;
    }

    current_dir = d;
}
