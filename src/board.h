#pragma once

#include <boardelements.h>

#include <vector>
#include <string>

#define TRACK_LENGTH 16

/**
 * @brief Class handling the state of the game board.
 * Keeps track of figures and handles their movement/placement.
 * Reports which bonus tiles are triggered and when the race is over.
 */
class Board
{
public:
    Board();

    /**
     * @brief Sets the new state of the board.
     * @param newState Board state in string format.
     */
    void setState(const std::string &newState);
    /**
     * @brief Returns current state of the board.
     * @return Board state in string format.
     */
    std::string getState();

    /**
     * @brief Checks if the race is over.
     * @return True if the race is over, otherwise false.
     */
    bool isRaceOver();

    /**
     * @brief Moves a figure on the board. The figure will be placed on the board if not there yet.
     * @param figure Figure to move.
     * @param steps Number of steps the figure moves.
     * @return Position of a bonus tile on the board if triggered while moving, otherwise 0;
     */
    int moveFigure(const elements::Figures figure, int steps);
    /**
     * @brief Places a bonus tile on the given board location.
     * @param tile Bonus tile to place.
     * @param position Location of the bonus tile.
     * @return In case of illegal placement -1, otherwise 0.
     */
    int placeBonusTile(const elements::Bonuses tile, int position);

private:
    std::string state;
    std::vector<std::vector<char>> track;

    std::vector<std::vector<char>> stateToTrack(const std::string &state);
    std::string trackToState(const std::vector<std::vector<char>> &track);
};
