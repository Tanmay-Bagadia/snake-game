#pragma once
#include <deque>
#include "types.h"

class Game
{
private:
    int width;
    int height;
    int score;
    std::deque<Point> snake;
    Point apple;
    Direction current_dir;
    bool game_over;

    void spawnApple();

public:
    Game(int w, int h);

    void update();
    void setDirection(Direction d);

    const std::deque<Point> &getSnake() const;
    Point getApple() const;
    bool isGameOver() const;
    int getWidth() const;
    int getHeight() const;
    int getScore() const;
};