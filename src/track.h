#pragma once

#include <elements.h>

#include <vector>
#include <string>

#define TRACK_SPACES 16

/**
 * @brief Class handling the state of the race track.
 * Handles figures and their movement/placement, reports which bonus tiles are triggered and when
 * the race is over.
 * The internal state of the race track can be set and extracted in string format.
 */
class Track
{
public:
    Track();

    /**
     * @brief Sets the new state of the race track.
     * @param newState Track state in string format.
     */
    void setState(const std::string &newState);
    /**
     * @brief Returns current state of the race track.
     * @return Track state in string format.
     */
    std::string getState();

    /**
     * @brief Checks if the race is over.
     * @return True if the race is over, otherwise false.
     */
    bool isRaceOver();

    /**
     * @brief Moves a figure on the track. The figure will be placed on the track if not there yet.
     * @param figure Figure to move.
     * @param spaces Number of spaces the figure moves.
     * @return Space of a bonus tile on the track if triggered while moving, otherwise 0;
     */
    unsigned int moveFigure(const elements::Figures figure, unsigned int spaces);
    /**
     * @brief Places a bonus tile on the given track space.
     * @param tile Bonus tile to place.
     * @param space Space to put the bonus tile on.
     * @return In case of illegal placement -1, otherwise 0.
     */
    int placeBonusTile(const elements::BonusTiles tile, unsigned int space);

private:
    std::string state;
    std::vector<std::vector<char>> track;
    bool raceIsOver;

    std::vector<std::vector<char>> stateToTrack(const std::string &state);
    std::string trackToState(const std::vector<std::vector<char>> &track);
};
