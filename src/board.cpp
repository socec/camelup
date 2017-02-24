#include <board.h>

Board::Board() : track(TRACK_LENGTH)
{
}

void Board::setState(const std::string &newState)
{
    state = newState;
    // update track based on new state
    track = stateToTrack(state);
}

std::string Board::getState()
{
    // updated state based on current track status
    state = trackToState(track);
    return state;
}

bool Board::isRaceOver()
{
    // check for extra position appended when race is over
    return track.size() > TRACK_LENGTH ? true : false;
}

int Board::moveFigure(const elements::Figures figure, int steps)
{
    int triggeredBonusTile = 0;
    // go through the track positions
    for (unsigned int i = 0; i < TRACK_LENGTH; i++)
    {
        // go through the figures on the given position
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
                    // add extra position after finish line
                    track.push_back({'>'});
                }
                // check for placed bonus tiles before moving
                unsigned int plannedPosition = i + steps;
                if (!track.at(plannedPosition).empty())
                {
                    char alreadyPlaced = track.at(plannedPosition).at(0);
                    // if a bonus tile was triggered adjust the steps and return real position
                    // instead of vector index
                    if (alreadyPlaced == (char)elements::Bonuses::PLUS)
                    {
                        triggeredBonusTile = plannedPosition + 1;
                        steps++;
                    }
                    if (alreadyPlaced == (char)elements::Bonuses::MINUS)
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
    // no match for figure means we only started the game, so place figure directly
    track.at(steps - 1).push_back((char)figure);
    return triggeredBonusTile;
}

int Board::placeBonusTile(const elements::Bonuses tile, int position)
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
        char placedLeft = 'X';
        if (position > 0 && !track.at(position - 1).empty())
        {
            placedLeft = track.at(position - 1).at(0);
        }
        char placedRight = 'X';
        if (position < (TRACK_LENGTH - 1) && !track.at(position + 1).empty())
        {
            placedRight = track.at(position + 1).at(0);
        }
        // make sure no adjacent bonus tiles
        if (placedLeft != (char)elements::Bonuses::PLUS &&
            placedLeft != (char)elements::Bonuses::MINUS &&
            placedRight != (char)elements::Bonuses::PLUS &&
            placedRight != (char)elements::Bonuses::MINUS)
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

std::vector<std::vector<char> > Board::stateToTrack(const std::string &state)
{
    std::vector<std::vector<char>> track(TRACK_LENGTH);
    int position = 0;
    for (char c : state)
    {
        if (c == ';')
        {
            position ++;
            continue;
        }
        else
        {
            track.at(position).push_back(c);
        }
    }
    return track;
}

std::string Board::trackToState(const std::vector<std::vector<char> > &track)
{
    std::string state;
    for (std::vector<char> position : track)
    {
        while (!position.empty())
        {
            state.push_back(position.front());
            position.erase(position.begin());
        }
        state += ';';
    }
    if (isRaceOver())
    {
        state.pop_back();
        state.push_back('<');
    }
    return state;
}
