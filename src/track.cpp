#include <track.h>

// adding an extra space on the track to enable "crosssing the finish line"
#define TRACK_LENGTH (TRACK_SPACES + 1)

Track::Track() : track(TRACK_LENGTH), raceIsOver(false)
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
    return raceIsOver;
}

unsigned int Track::moveFigure(const elements::Figures figure, unsigned int spaces)
{
    int triggeredBonusTile = 0;
    // no moving if the race is over
    if (isRaceOver())
    {
        return triggeredBonusTile;
    }
    // go through the track spaces
    for (size_t i = 0; i < TRACK_SPACES; i++)
    {
        // go through the figures on the given space
        for (size_t j = 0; j < track.at(i).size(); j++)
        {
            // find matching figure
            if (track.at(i).at(j) == (char)figure)
            {
                // check if race will be over with this move
                if ((i + spaces) >= TRACK_SPACES)
                {
                    raceIsOver = true;
                    // adjust to make only one step after finish line
                    spaces = TRACK_SPACES - i;
                }
                else
                {
                    // check for placed bonus tiles before moving
                    size_t plannedSpace = i + spaces;
                    if (!track.at(plannedSpace).empty())
                    {
                        char alreadyPlaced = track.at(plannedSpace).at(0);
                        // if a bonus tile was triggered we adjust the steps and return real space
                        // instead of a vector index
                        if (alreadyPlaced == (char)elements::BonusTiles::PLUS)
                        {
                            triggeredBonusTile = plannedSpace + 1;
                            spaces++;
                        }
                        if (alreadyPlaced == (char)elements::BonusTiles::MINUS)
                        {
                            triggeredBonusTile = plannedSpace + 1;
                            spaces--;
                        }
                    }
                }
                // now prepare to move figure/unit
                auto thisFigure = track.at(i).begin() + j;
                auto topUnitFigure = track.at(i).end();
                auto unitSize = topUnitFigure - thisFigure;

                // usually the figure is placed on top of others...
                auto newSpace = track.at(i + spaces).end();
                // ...but must be placed below others if bouncing back from a negative bonus tile
                if (triggeredBonusTile > 0 &&
                    track.at(triggeredBonusTile - 1).at(0) == (char)elements::BonusTiles::MINUS)
                {
                    newSpace = track.at(i + spaces).begin();
                }

                // make a copy of the moving unit
                std::vector<char> unitCopy(thisFigure, topUnitFigure);
                // erase unit from the old space
                auto oldSpace = track.at(i).begin() + j;
                track.at(i).erase(oldSpace, oldSpace + unitSize);
                // now place unit on the new space
                track.at(i + spaces).insert(newSpace, unitCopy.begin(), unitCopy.end());

                // we are done with this figure, exit
                return triggeredBonusTile;
            }
        }
    }
    // reaching here means no match for figure since we only started the game,
    // so place the figure directly and exit
    track.at(spaces - 1).push_back((char)figure);
    return triggeredBonusTile;
}

int Track::placeBonusTile(const elements::BonusTiles tile, unsigned int space, bool flipExisting)
{
    // check boundaries (not allowed to place on space 1)
    if (space < 2 || space > TRACK_SPACES)
    {
        return -1;
    }
    // real spaces start at 1, but vector indices start at 0
    space--;

    // check placement rules...

    // existing tiles can be flipped
    if (!track.at(space).empty())
    {
        if (flipExisting)
        {
            char placed = track.at(space).at(0);
            // check that we are actually flipping an existing tile
            if ((placed != (char)tile) &&
                (placed == (char)elements::BonusTiles::PLUS ||
                 placed == (char)elements::BonusTiles::MINUS))
            {
                track.at(space).at(0) = (char)tile;
                return 0;
            }
        }
        return -1;
    }
    // otherwise place a tile on an empty space
    else
    {
        char placedLeft = 'X';
        if (space > 1 && !track.at(space - 1).empty())
        {
            placedLeft = track.at(space - 1).at(0);
        }
        char placedRight = 'X';
        if (space < (TRACK_SPACES - 1) && !track.at(space + 1).empty())
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
}

std::vector<std::vector<char> > Track::stateToTrack(const std::string &state)
{
    std::vector<std::vector<char>> track(TRACK_LENGTH);
    size_t space = 0;
    for (char c : state)
    {
        // detect separators to change space
        if (c == (char)elements::State::SEPARATOR)
        {
            space ++;
            continue;
        }
        // skip finish characters
        else if (c == (char)elements::State::FINSTART ||
                 c == (char)elements::State::FINEND)
        {
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
        // add separator to end space
        state.push_back((char)elements::State::SEPARATOR);
    }
    // finish space does not need a separator, so remove it
    state.pop_back();
    // add finish line characters if there are figures on the finish space
    if (state.back() != (char)elements::State::SEPARATOR)
    {
        size_t finishSpace = state.find_last_of((char)elements::State::SEPARATOR) + 1;
        state.insert(finishSpace, 1, (char)elements::State::FINSTART);
        state.push_back((char)elements::State::FINEND);
    }
    return state;
}
