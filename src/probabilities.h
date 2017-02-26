#pragma once

#include <string>
#include <map>

/**
 * @brief Class handling calculation of probabilities.
 */
class Probabilities
{
public:
    Probabilities(std::string figures, std::string state, std::string remainingDice);

    /**
     * @brief Updates the object with new state of the race and remaining dice.
     * @param state New state of the race.
     * @param remainingDice Dice not yet revealed in the current leg.
     */
    void update(std::string state, std::string remainingDice);

    /**
     * @brief Returns predictions (as rounded percentage) for the current leg.
     * @return Map with figures as keys and their probability of winning the current leg as values.
     */
    std::map<char, unsigned int> getLegPrediction();

private:
    std::string usedFigures;
    std::string currentState;
    std::string possibleLegWinners;
    std::map<char, unsigned int> legPrediction;

    char findLeader(std::string currentState);
    std::string updatePossibleLegWinners(std::string currentState, std::string remainingDice);
    void createLegPrediction();
};
