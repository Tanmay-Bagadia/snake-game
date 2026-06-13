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

    // Initialize a length-3 snake
    snake.push_back({start_x, start_y});     // Head
    snake.push_back({start_x - 1, start_y}); // Body
    snake.push_back({start_x - 2, start_y}); // Tail

    spawnApple();
}

void Game::update()
{

    if (game_over || current_dir == STOP)
    {
        return;
    }

    Point new_head = snake.front();

    switch (current_dir)
    {
    case UP:
        new_head.y -= 1;
        break;
    case DOWN:
        new_head.y += 1;
        break;
    case RIGHT:
        new_head.x += 1;
        break;
    case LEFT:
        new_head.x -= 1;
        break;
    case STOP:
        break;
    }

    if (new_head.x <= 0 || new_head.x >= width ||
        new_head.y <= 0 || new_head.y >= height)
    {
        game_over = true;
        return;
    }

    for (size_t i = 0; i < snake.size(); i++)
    {
        if (new_head.x == snake[i].x && new_head.y == snake[i].y)
        {
            game_over = true;
            return;
        }
    }

    snake.push_front(new_head);

    if (new_head.x == apple.x && new_head.y == apple.y)
    {
        spawnApple();
    }
    else
    {
        snake.pop_back();
    }
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

void Game::spawnApple()
{
    bool valid_pos = false;
    int temp_x, temp_y;

    while (!valid_pos)
    {
        temp_x = (rand() % (width - 2)) + 1;
        temp_y = (rand() % (height - 2)) + 1;

        valid_pos = true;

        for (size_t i = 0; i < snake.size(); i++)
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

const std::deque<Point> &Game::getSnake() const { return snake; }
Point Game::getApple() const { return apple; }
bool Game::isGameOver() const { return game_over; }