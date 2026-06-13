#pragma once

#include <termios.h>

class Terminal
{
private:
    struct termios original_state;

public:
    Terminal();
    ~Terminal();
};