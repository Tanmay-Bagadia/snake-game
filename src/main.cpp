#include "terminal.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>

int main()
{

    Terminal term;

    int counter = 0;

    while (true)
    {

        std::cout << "Engine Running. Tick: " << counter++ << "\r" << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        char c;

        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (c == 'q')
            {
                std::cout << "\nQuit command received. Shutting down." << std::endl;
                break;
            }
        }
    }

    return 0;
}