#include <track.h>

Track::Track() : track(TRACK_LENGTH)
{
}

void Track::setState(const std::string &newState)
{
    state = newState;
    // update track based on new state
    track = stateToTrack(state);
}

std::string Track::getState()
{
    // updated state based on current track status
    state = trackToState(track);
    return state;
}

bool Track::isRaceOver()
{
    // check for extra space appended when race is over
    return track.size() > TRACK_LENGTH ? true : false;
}

int Track::moveFigure(const elements::Figures figure, int spaces)
{
    int triggeredBonusTile = 0;
    // go through the track spaces
    for (unsigned int i = 0; i < TRACK_LENGTH; i++)
    {
        // go through the figures on the given space
        for (unsigned int j = 0; j < track.at(i).size(); j++)
        {
            // find match
            if (track.at(i).at(j) == (char)figure)
            {
                // check if race will be over with this move
                if ((i + spaces) >= TRACK_LENGTH)
                {
                    // adjust to make only one step after finish line
                    spaces = TRACK_LENGTH - i;
                    // add extra "space" after finish line
                    track.push_back({(char) elements::StateChars::WINSTART});
                }
                // check for placed bonus tiles before moving
                unsigned int plannedSpace = i + spaces;
                if (!track.at(plannedSpace).empty())
                {
                    char alreadyPlaced = track.at(plannedSpace).at(0);
                    // if a bonus tile was triggered adjust the steps and return real space instead
                    // of a vector index
                    if (alreadyPlaced == (char)elements::BonusTiles::PLUS)
                    {
                        triggeredBonusTile = plannedSpace + 1;
                        spaces++;
                    }
                    if (alreadyPlaced == (char)elements::BonusTiles::MINUS)
                    {
                        // TODO handle placement below existing unit
                        triggeredBonusTile = plannedSpace + 1;
                        spaces--;
                    }
                }
                // now move figure
                auto newSpace = track.at(i + spaces).end();
                auto thisFigure = track.at(i).begin() + j;
                auto topFigure = track.at(i).end();
                int carriedFigures = topFigure - thisFigure;
                // copy to new space
                track.at(i + spaces).insert(newSpace, thisFigure, topFigure);
                // erase from old space and exit
                auto oldSpace = track.at(i).begin() + j;
                track.at(i).erase(oldSpace, oldSpace + carriedFigures);
                // we are done
                return triggeredBonusTile;
            }
        }
    }
    // no match for figure means we only started the game, so place figure directly
    track.at(spaces - 1).push_back((char)figure);
    return triggeredBonusTile;
}

int Track::placeBonusTile(const elements::BonusTiles tile, int space)
{
    //TODO: handle flipping your existing tile
    //TODO: handle tile ownership

    // real spaces start at 1, but vector indices start at 0
    space--;
    // check boundaries (also, not allowed to place on space 1)
    if (space <1 || space >= TRACK_LENGTH)
    {
        return -1;
    }
    // check rules
    if (track.at(space).empty())
    {
        char placedLeft = 'X';
        if (space > 1 && !track.at(space - 1).empty())
        {
            placedLeft = track.at(space - 1).at(0);
        }
        char placedRight = 'X';
        if (space < (TRACK_LENGTH - 1) && !track.at(space + 1).empty())
        {
            placedRight = track.at(space + 1).at(0);
        }
        // make sure no adjacent bonus tiles
        if (placedLeft != (char)elements::BonusTiles::PLUS &&
            placedLeft != (char)elements::BonusTiles::MINUS &&
            placedRight != (char)elements::BonusTiles::PLUS &&
            placedRight != (char)elements::BonusTiles::MINUS)
        {
            track.at(space).push_back((char)tile);
            return 0;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

std::vector<std::vector<char> > Track::stateToTrack(const std::string &state)
{
    std::vector<std::vector<char>> track(TRACK_LENGTH);
    int space = 0;
    for (char c : state)
    {
        // detect separators to change space
        if (c == (char)elements::StateChars::SEPARATOR)
        {
            space ++;
            continue;
        }
        // otherwise use character as figure
        else
        {
            track.at(space).push_back(c);
        }
    }
    return track;
}

std::string Track::trackToState(const std::vector<std::vector<char> > &track)
{
    std::string state;
    for (std::vector<char> space : track)
    {
        // translate the space in correct order (bottom-up)
        while (!space.empty())
        {
            state.push_back(space.front());
            space.erase(space.begin());
        }
        // add separator
        state.push_back((char)elements::StateChars::SEPARATOR);
    }
    // add additional character when the race is over
    if (isRaceOver())
    {
        state.pop_back();
        state.push_back((char)elements::StateChars::WINEND);
    }
    return state;
}
