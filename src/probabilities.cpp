#include <probabilities.h>
#include <elements.h>
#include <track.h>

Probabilities::Probabilities(std::string figures, std::string state, std::string remainingDice)
{
    // set internal variables
    usedFigures = figures;
    update(state, remainingDice);
}

void Probabilities::update(std::string state, std::string remainingDice)
{
    currentState = state;
    possibleLegWinners = updatePossibleLegWinners(state, remainingDice);
    createLegPrediction();
}

std::map<char, unsigned int> Probabilities::getLegPrediction()
{
    return legPrediction;
}

char Probabilities::findLeader(std::string state)
{
    return state.at(state.find_last_of(usedFigures));
}

std::string Probabilities::updatePossibleLegWinners(std::string state, std::string remainingDice)
{
    // RECURSIVE!
    std::string possibleWinners;
    if (!remainingDice.empty())
    {
        // go through remaining dice
        for (char figure : remainingDice)
        {
            // go through possible spaces revealed by a die
            for (int spaces = 1; spaces <= 3; spaces++)
            {
                // simulate given dice on the tracdk
                Track t;
                t.setState(state);
                t.moveFigure((elements::Figures)figure, spaces);
                // get the next state
                std::string nextState = t.getState();
                // remove the used die from the remaining list
                std::string nextRemaining = remainingDice;
                nextRemaining.erase(nextRemaining.find(figure), 1);
                // if there is no more dice the leg is over, so save the current race leader
                if (nextRemaining.empty())
                {

                    possibleWinners.push_back(findLeader(nextState));
                }
                // otherwise recurse to simulate the remaining dice
                else
                {
                    possibleWinners.append(updatePossibleLegWinners(nextState, nextRemaining));
                }
            }
        }
    }
    return possibleWinners;
}

void Probabilities::createLegPrediction()
{
    // calculate percentage of possible wins for a figure
    for (auto figure : usedFigures)
    {
        unsigned int count = 0;
        for (auto winner : possibleLegWinners)
        {
            if (winner == figure) count++;
        }
        double probability = (double)count / possibleLegWinners.size();
        legPrediction[figure] = (unsigned int)(probability *100);
    }
}
