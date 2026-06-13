#include "terminal.h"
#include "game.h"
#include "renderer.h"
#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <ctime>

int main()
{

    srand(time(NULL));

    Terminal term;
    Game game(40, 20);
    Renderer renderer;

    while (true)
    {

        char c;

        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (c == 'q')
            {
                break;
            }
            else if (c == 'w')
            {
                game.setDirection(UP);
            }
            else if (c == 's')
            {
                game.setDirection(DOWN);
            }
            else if (c == 'a')
            {
                game.setDirection(LEFT);
            }
            else if (c == 'd')
            {
                game.setDirection(RIGHT);
            }
        }

        game.update();

        if (game.isGameOver())
        {
            break;
        }

        renderer.draw(game);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\033[2J\033[H";
    std::cout << "Game Over! Thanks for playing." << std::endl;

    return 0;
}