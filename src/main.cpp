#include <unistd.h>
#include <board.h>
#include <randomutils.h>

#include <iostream>

#define FIGURE_COUNT 5

void playRound(Board &bs)
{
    std::vector<elements::Figures> figures =
    {
        elements::Figures::BLUE, elements::Figures::GREEN, elements::Figures::ORANGE,
        elements::Figures::WHITE, elements::Figures::YELLOW
    };
    randomutils::shuffleVector(figures);
    while (!figures.empty())
    {
        int steps = randomutils::getNumberFromInterval(1, 3);
        elements::Figures figure = figures.back();
        figures.pop_back();

        std::cout << "moving " << (char)figure << " for " << steps <<
                     " | bonus on " << bs.moveFigure(figure, steps) << std::endl;
        std::cout << bs.getState() << std::endl;
        sleep(1);
    }
    std::cout << "=====================" << std::endl;
    if (bs.isRaceOver()) return;
}

int main()
{
    Board bs;

    bs.placeBonusTile(elements::Bonuses::PLUS, 5);
    bs.placeBonusTile(elements::Bonuses::MINUS, 10);

    std::cout << "Starting..." << std::endl;

    while (1)
    {
        playRound(bs);
        if (bs.isRaceOver()) break;
    }

    std::cout << "Done!" << std::endl;

    return 0;
}
