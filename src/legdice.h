#pragma once

#include <elements.h>

#include <vector>
#include <string>

/**
 * Structure describing a die.
 */
typedef struct {elements::Figures figure; int spaces;} Die;

/**
 * @brief Class handling dice in a race leg.
 */
class LegDice
{
public:
    LegDice();

    /**
     * @brief Resets this object by making all dice available.
     */
    void reset();
    /**
     * @brief Checks if this race leg has ended.
     * @return  True if this leg has ended, false otherwise.
     */
    bool isLegOver();

    /**
     * @brief Reveals the next die for this leg.
     * @param die A Die object to store the result.
     * @return -1 if no more dice available in this leg, 0 otherwise.
     */
    int revealNextDie(Die &die);

    /**
     * @brief Returns a string with dice revealed in this leg.
     * @return String with revealed dice.
     */
    std::string getRevealedDice();
    /**
     * @brief Returns a string with dice still not revealed in this leg.
     * @return String with remaining dice.
     */
    std::string getRemainingDice();

private:
    std::vector<elements::Figures> hiddenDice;
    std::vector<elements::Figures> revealedDice;

    std::string diceToString(const std::vector<elements::Figures> &dice);
};
