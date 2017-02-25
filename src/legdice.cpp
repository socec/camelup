#include <legdice.h>
#include <randomutils.h>

LegDice::LegDice()
{
    hiddenDice =
    {
        elements::Figures::BLUE, elements::Figures::GREEN, elements::Figures::ORANGE,
        elements::Figures::WHITE, elements::Figures::YELLOW
    };
}

void LegDice::reset()
{
    //hiddenDice.clear();
    hiddenDice =
    {
        elements::Figures::BLUE, elements::Figures::GREEN, elements::Figures::ORANGE,
        elements::Figures::WHITE, elements::Figures::YELLOW
    };
    revealedDice.clear();
}

bool LegDice::isLegOver()
{
    return hiddenDice.empty();
}

int LegDice::revealNextDie(Die &die)
{
    if (hiddenDice.empty())
    {
        return -1;
    }
    else
    {
        // get radnom die and number of steps
        die.spaces = randomutils::getNumberFromInterval(1, 3);
        randomutils::shuffleVector(hiddenDice);
        die.figure = hiddenDice.back();
        // update dice arrays
        hiddenDice.pop_back();
        revealedDice.push_back(die.figure);
    }
    return 0;
}

std::string LegDice::getRevealedDice()
{
    return diceToString(revealedDice);
}

std::string LegDice::getRemainingDice()
{
    return diceToString(hiddenDice);
}

std::string LegDice::diceToString(const std::vector<elements::Figures> &dice)
{
    std::string result;
    for (auto die : dice)
    {
        result.push_back((char)die);
    }
    return result;
}
