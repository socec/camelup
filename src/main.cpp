#include <unistd.h>
#include <boardstate.h>
#include <randomutils.h>

#include <iostream>

#define FIGURE_COUNT 5

void playRound(BoardState &bs)
{
    std::vector<char> figures = {'A','B','C','D','E'};
    randomutils::shuffleArray(figures);
    while (!figures.empty())
    {
        int steps = randomutils::getNumberFromInterval(1, 3);
        char figure = figures.back();
        figures.pop_back();

        std::cout << "moving " << figure << " for " << steps << std::endl;
        bs.moveFigure(figure, steps);
        std::cout << bs.getState() << std::endl;
        sleep(1);

        if (bs.isRaceOver()) return;
    }
    std::cout << "================" << std::endl;
}

int main()
{
    BoardState bs;

    std::cout << "Starting..." << std::endl;

    while (1)
    {
        playRound(bs);
        if (bs.isRaceOver()) break;
    }

    std::cout << "Done!" << std::endl;

    return 0;
}
