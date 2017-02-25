#include <unistd.h>
#include <track.h>
#include <randomutils.h>

#include <iostream>

#define FIGURE_COUNT 5

void playRound(Track &bs)
{
    std::vector<elements::Figures> figures =
    {
        elements::Figures::BLUE, elements::Figures::GREEN, elements::Figures::ORANGE,
        elements::Figures::WHITE, elements::Figures::YELLOW
    };
    randomutils::shuffleVector(figures);
    while (!figures.empty())
    {
        int spaces = randomutils::getNumberFromInterval(1, 3);
        elements::Figures figure = figures.back();
        figures.pop_back();

        std::cout << "moving " << (char)figure << " for " << spaces <<
                     " | bonus on " << bs.moveFigure(figure, spaces) << std::endl;
        std::cout << bs.getState() << std::endl;
        //sleep(1);
        if (bs.isRaceOver()) break;
    }
    std::cout << "=====================" << std::endl;
}

int main()
{
    Track bs;

    bs.placeBonusTile(elements::BonusTiles::PLUS, 5);
    bs.placeBonusTile(elements::BonusTiles::MINUS, 10);

    std::cout << "Starting..." << std::endl;

    while (1)
    {
        playRound(bs);
        if (bs.isRaceOver()) break;
    }

    std::cout << "Done!" << std::endl;

    return 0;
}
