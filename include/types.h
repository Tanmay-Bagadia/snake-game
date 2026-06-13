#pragma once

struct Point
{
    int x;
    int y;
};

enum Direction
{
    STOP = 0,
    UP = 1,
    DOWN = -1,
    RIGHT = 2,
    LEFT = -2
};