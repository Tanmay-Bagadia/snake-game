#include "game.h"
#include <random>

Game::Game(int w, int h)
{
    width = w;
    height = h;
    score = 0;
    current_dir = STOP;
    game_over = false;

    int start_x = width / 2;
    int start_y = height / 2;

    snake.push_back({start_x, start_y});
    snake.push_back({start_x - 1, start_y});
    snake.push_back({start_x - 2, start_y});

    spawnApple();
}

void Game::update()
{
    if (game_over || current_dir == STOP)
        return;

    Point new_head = snake.front();

    switch (current_dir)
    {
    case UP:    new_head.y -= 1; break;
    case DOWN:  new_head.y += 1; break;
    case RIGHT: new_head.x += 1; break;
    case LEFT:  new_head.x -= 1; break;
    case STOP:  break;
    }

    if (new_head.x <= 1 || new_head.x >= width ||
        new_head.y <= 1 || new_head.y >= height)
    {
        game_over = true;
        return;
    }

    for (size_t i = 0; i < snake.size() - 1; i++)
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
        score++;
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
        return;
    current_dir = d;
}

void Game::spawnApple()
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist_x(2, width - 1);
    std::uniform_int_distribution<int> dist_y(2, height - 1);

    bool valid_pos = false;
    while (!valid_pos)
    {
        apple.x = dist_x(rng);
        apple.y = dist_y(rng);

        valid_pos = true;
        for (size_t i = 0; i < snake.size(); i++)
        {
            if (snake[i].x == apple.x && snake[i].y == apple.y)
            {
                valid_pos = false;
                break;
            }
        }
    }
}

const std::deque<Point> &Game::getSnake() const { return snake; }
Point Game::getApple() const { return apple; }
bool Game::isGameOver() const { return game_over; }
int Game::getWidth() const { return width; }
int Game::getHeight() const { return height; }
int Game::getScore() const { return score; }