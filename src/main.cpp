#include <unistd.h>
#include <boardstate.h>
#include <randomutils.h>

#include <iostream>

#define FIGURE_COUNT 5

void playRound(board::BoardState &bs)
{
    std::vector<board::Figures> figures = {board::Figures::BLUE, board::Figures::GREEN,
                                           board::Figures::ORANGE, board::Figures::WHITE,
                                           board::Figures::YELLOW};
    randomutils::shuffleVector(figures);
    while (!figures.empty())
    {
        int steps = randomutils::getNumberFromInterval(1, 3);
        board::Figures figure = figures.back();
        figures.pop_back();

        std::cout << "moving " << (char)figure << " for " << steps <<
                     " | bonus on " << bs.moveFigure(figure, steps) << std::endl;
        std::cout << bs.getState() << std::endl;
        sleep(1);

        if (bs.isRaceOver()) return;
    }
    std::cout << "=====================" << std::endl;
}

int main()
{
    board::BoardState bs;

    bs.placeBonusTile(board::Bonuses::PLUS, 5);
    bs.placeBonusTile(board::Bonuses::MINUS, 10);

    std::cout << "Starting..." << std::endl;

    while (1)
    {
        playRound(bs);
        if (bs.isRaceOver()) break;
    }

    std::cout << "Done!" << std::endl;

    return 0;
}
