#pragma once
#include "types.h"
#include <deque>

class Game
{

private:
    std::deque<Point> snake;
    Point apple;
    Direction current_dir;

    int width;
    int height;

    bool game_over;

    void spawnApple();

public:
    Game(int w, int h);

    void update();

    void setDirection(Direction d);

    const std::deque<Point> &getSnake() const;
    Point getApple() const;
    bool isGameOver() const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};