#include <unistd.h>
#include <track.h>
#include <legdice.h>
#include <probabilities.h>

#include <iostream>

int main()
{
    Track track;
    LegDice legdice;
    std::string figures;

    // create a list of possible figures
    figures.push_back((char)elements::Figures::BLUE);
    figures.push_back((char)elements::Figures::GREEN);
    figures.push_back((char)elements::Figures::ORANGE);
    figures.push_back((char)elements::Figures::WHITE);
    figures.push_back((char)elements::Figures::YELLOW);

    // some random bonus tiles
    track.placeBonusTile(elements::BonusTiles::PLUS, 5, false);
    track.placeBonusTile(elements::BonusTiles::MINUS, 10, false);

    std::cout << "==== RACE START ====" << std::endl << std::endl;

    while (1)
    {
        // pretty
        if (legdice.isLegOver())
        {
            legdice.reset();
            std::cout << "==== NEW LEG ====" << std::endl << std::endl;
        }

        // show race track status
        std::cout << "track status: " << track.getState() << std::endl;

        // probabilities for this leg
        Probabilities p (figures, track.getState(), legdice.getRemainingDice());
        std::map<char, unsigned int> prediction = p.getLegPrediction();
        std::cout << "leg probabilitites";
        for (unsigned int i = 0; i < figures.size(); i++)
        {
            std::cout << " | " << figures.at(i) << "=" << prediction[figures.at(i)] << "%";
        }
        std::cout << std::endl << std::endl;

        sleep(1);

        // reveal next die
        Die die;
        legdice.revealNextDie(die);

        // show leg status
        std::cout << "-> revealed " << (char)die.figure << die.spaces
                  << " | bonus hit on " << track.moveFigure(die.figure, die.spaces)
                  << " | dice played " << legdice.getRevealedDice()
                  << " | dice left " << legdice.getRemainingDice() << std::endl << std::endl;


        // pretty
        if (track.isRaceOver())
        {
            std::cout << "track status: " << track.getState() << std::endl;
            std::cout << "winner: " << track.getState().at(track.getState().find_last_of(figures)) << std::endl;
            std::cout << std::endl << "==== RACE OVER ====" << std::endl;
            break;
        }
    }

    return 0;
}
