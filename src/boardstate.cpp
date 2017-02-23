#include <boardstate.h>

#include <iostream>

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

void BoardState::moveFigure(char figure, int steps)
{
    // go through the track tiles
    for (unsigned int i = 0; i < TRACK_LENGTH; i++)
    {
        // go through the figures on the tile
        for (unsigned int j = 0; j < track.at(i).size(); j++)
        {
            // find match
            if (track.at(i).at(j) == figure)
            {
                // check if race will be over with this move
                if ((i + steps) >= TRACK_LENGTH)
                {
                    // adjust to make only one step after finish line
                    steps = TRACK_LENGTH - i;
                    // add extra tile after finish line
                    track.push_back({'>'});
                }
                // check extra tile placement first
                if (!track.at(i + steps).empty())
                {
                    char tileContent = track.at(i + steps).at(0);
                    if (tileContent == '+') steps++;
                    if (tileContent == '-') steps--;
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
                return;
            }
        }
    }
    // no match so far means we only started the game, place figure directly
    track.at(steps - 1).push_back(figure);
}

int BoardState::placeBonusTile(char tile, int position)
{
    //TODO: handle flipping your existing tile
    //TODO: handle tile ownership

    // logical index vs. code index
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
        // make sure no adjacent extra tiles
        if (tileContentLeft != '+' && tileContentLeft != '-' &&
            tileContentRight != '+' && tileContentRight != '-')
        {
            track.at(position).push_back(tile);
            return 0;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

std::vector<tileStack> BoardState::stateToTrack(const std::string &state)
{
    std::vector<tileStack> track(TRACK_LENGTH);
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

std::string BoardState::trackToState(const std::vector<tileStack> &track)
{
    std::string state;
    for (tileStack tile : track)
    {
        while (!tile.empty())
        {
            state += tile.front();
            tile.erase(tile.begin());
        }
        state += ';';
    }
    return state;
}
