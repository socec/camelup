#include <boardstate.h>

#include <iostream>

namespace board
{

BoardState::BoardState() : track(TRACK_LENGTH)
{
}

void BoardState::setState(const std::string &newState)
{
    state = newState;
    // update track based on new state
    track = stateToTrack(state);
}

std::string BoardState::getState()
{
    // updated state based on current track status
    state = trackToState(track);
    return state;
}

bool BoardState::isRaceOver()
{
    // check for extra tile appended when race is over
    return track.size() > TRACK_LENGTH ? true : false;
}

int BoardState::moveFigure(Figures figure, int steps)
{
    int triggeredBonusTile = 0;
    // go through the track tiles
    for (unsigned int i = 0; i < TRACK_LENGTH; i++)
    {
        // go through the figures on the tile
        for (unsigned int j = 0; j < track.at(i).size(); j++)
        {
            // find match
            if (track.at(i).at(j) == (char)figure)
            {
                // check if race will be over with this move
                if ((i + steps) >= TRACK_LENGTH)
                {
                    // adjust to make only one step after finish line
                    steps = TRACK_LENGTH - i;
                    // add extra tile after finish line
                    track.push_back({'>'});
                }
                // check for placed bonus tiles before moving
                if (!track.at(i + steps).empty())
                {
                    unsigned int plannedPosition = i + steps;
                    char tileContent = track.at(plannedPosition).at(0);
                    // if a bonus tile was triggered return real position instead of vector index
                    if (tileContent == (char)Bonuses::PLUS)
                    {
                        triggeredBonusTile = plannedPosition + 1;
                        steps++;
                    }
                    if (tileContent == (char)Bonuses::MINUS)
                    {
                        triggeredBonusTile = plannedPosition + 1;
                        steps--;
                    }
                }
                // now move figure
                auto newPosition = track.at(i + steps).end();
                auto thisFigure = track.at(i).begin() + j;
                auto topFigure = track.at(i).end();
                int carriedFigures = topFigure - thisFigure;
                // copy to new position
                track.at(i + steps).insert(newPosition, thisFigure, topFigure);
                // erase old position and exit
                auto oldFigurePosition = track.at(i).begin() + j;
                track.at(i).erase(oldFigurePosition, oldFigurePosition + carriedFigures);
                // we are done
                return triggeredBonusTile;
            }
        }
    }
    // no match for figure means we only started the game, place figure directly
    track.at(steps - 1).push_back((char)figure);
    return triggeredBonusTile;
}

int BoardState::placeBonusTile(Bonuses tile, int position)
{
    //TODO: handle flipping your existing tile
    //TODO: handle tile ownership

    // real positions start at 1, but vector indices start at 0
    position--;
    // check boundaries
    if (position < 0 || position >= TRACK_LENGTH)
    {
        return -1;
    }
    // check rules
    if (track.at(position).empty())
    {
        char tileContentLeft = 'X';
        if (position > 0 && !track.at(position - 1).empty())
        {
            tileContentLeft = track.at(position - 1).at(0);
        }
        char tileContentRight = 'X';
        if (position < (TRACK_LENGTH - 1) && !track.at(position + 1).empty())
        {
            tileContentRight = track.at(position + 1).at(0);
        }
        // make sure no adjacent bonus tiles
        if (tileContentLeft != (char)Bonuses::PLUS && tileContentLeft != (char)Bonuses::MINUS &&
            tileContentRight != (char)Bonuses::PLUS && tileContentRight != (char)Bonuses::MINUS)
        {
            track.at(position).push_back((char)tile);
            return 0;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

std::vector<std::vector<char> > BoardState::stateToTrack(const std::string &state)
{
    std::vector<std::vector<char>> track(TRACK_LENGTH);
    int tileIndex = 0;
    for (char c : state)
    {
        if (c == ';')
        {
            tileIndex ++;
            continue;
        }
        else
        {
            track.at(tileIndex).push_back(c);
        }
    }
    return track;
}

std::string BoardState::trackToState(const std::vector<std::vector<char> > &track)
{
    std::string state;
    bool extraFinishTile = false;
    for (std::vector<char> tile : track)
    {
        while (!tile.empty())
        {
            if (tile.front() == '>') extraFinishTile = true;
            state += tile.front();
            tile.erase(tile.begin());
        }
        if (extraFinishTile)
        {
            state += '<';
        }
        else
        {
            state += ';';
        }
    }
    return state;
}

} // namespace board
