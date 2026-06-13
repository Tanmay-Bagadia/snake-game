#include "terminal.h"
#include <unistd.h>
#include <iostream>

Terminal::Terminal()
{
    tcgetattr(STDIN_FILENO, &original_state);

    struct termios raw = original_state;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    std::cout << "\033[?25l" << std::flush;
}

Terminal::~Terminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_state);
    std::cout << "\033[?25h" << std::flush;
}