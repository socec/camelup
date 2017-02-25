#include <unistd.h>
#include <track.h>
#include <legdice.h>

#include <iostream>

int main()
{
    Track track;
    LegDice legdice;

    track.placeBonusTile(elements::BonusTiles::PLUS, 1);
    track.placeBonusTile(elements::BonusTiles::MINUS, 10);

    std::cout << "Starting..." << std::endl;

    while (1)
    {
        if (legdice.isLegOver())
        {
            legdice.reset();
            std::cout << "=====================" << std::endl;
        }

        Die die;
        legdice.revealNextDie(die);

        std::cout << "moving " << (char)die.figure << " for " << die.spaces
                  << " | bonus on " << track.moveFigure(die.figure, die.spaces)
                  << " | dice played " << legdice.getRevealedDice()
                  << " | dice left " << legdice.getRemainingDice() << std::endl;
        std::cout << track.getState() << std::endl;

        if (track.isRaceOver())
        {
            std::cout << "=====================" << std::endl;
            break;
        }

        //sleep(1);
    }

    std::cout << "Done!" << std::endl;

    return 0;
}
