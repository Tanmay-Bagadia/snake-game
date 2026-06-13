#include "terminal.h"
#include <unistd.h>
#include <fcntl.h>

// CONSRUCTOR:
Terminal ::Terminal()
{

    tcgetattr(STDIN_FILENO, &original_state);

    struct termios raw = original_state;

    raw.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDERR_FILENO, F_SETFL, flags | O_NONBLOCK);
}

// DESTRUCTOR
Terminal::~Terminal()
{

    tcsetattr(STDERR_FILENO, TCSANOW, &original_state);

    int flags = fcntl(STDERR_FILENO, F_GETFL, 0);
    fcntl(STDERR_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}