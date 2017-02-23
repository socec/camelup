#pragma once

#include <string>
#include <vector>

#define TRACK_LENGTH 16

typedef std::vector<char> tileStack;

class BoardState
{
public:
    BoardState();

    void setState(const std::string &newState);
    std::string getState();

    bool isRaceOver();

    void moveFigure(char figure, int steps);
    int placeBonusTile(char tile, int position);

private:
    std::string state;
    std::vector<tileStack> track;

    std::vector<tileStack> stateToTrack(const std::string &state);
    std::string trackToState(const std::vector<tileStack> &track);
};
