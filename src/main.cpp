#include "terminal.h"
#include "game.h"
#include "renderer.h"
#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>

int main()
{
    Terminal term;
    Game game(30, 20);
    Renderer renderer;

    std::cout << "\033[2J";

    while (true)
    {
        char c;
        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (c == 'q')
                break;
            else if (c == 'w')
                game.setDirection(UP);
            else if (c == 's')
                game.setDirection(DOWN);
            else if (c == 'a')
                game.setDirection(LEFT);
            else if (c == 'd')
                game.setDirection(RIGHT);
            else if (c == '\033')
            {
                char seq[2];
                if (read(STDIN_FILENO, &seq[0], 1) == 1 &&
                    read(STDIN_FILENO, &seq[1], 1) == 1 &&
                    seq[0] == '[')
                {
                    switch (seq[1])
                    {
                    case 'A': game.setDirection(UP); break;
                    case 'B': game.setDirection(DOWN); break;
                    case 'C': game.setDirection(RIGHT); break;
                    case 'D': game.setDirection(LEFT); break;
                    }
                }
            }
        }

        game.update();
        if (game.isGameOver())
            break;

        renderer.draw(game);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\033[2J\033[H";
    std::cout << "\n  Game Over! Final Score: " << game.getScore() << "\n" << std::endl;

    return 0;
}