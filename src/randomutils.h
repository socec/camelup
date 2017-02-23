#pragma once

#include <vector>
#include <random>

namespace randomutils
{

/**
 * @brief Returns a random integer from the given closed interval.
 * @param start Minimal integer that can be returned.
 * @param end Maximal integer that can be returned.
 * @return Randomly generated integer.
 */
int getNumberFromInterval(int start, int end)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(start, end);
    return distribution(generator);
}

/**
 * Shuffles the given vector.
 */
template <typename T> void shuffleVector(std::vector<T> &array)
{
    unsigned int size = array.size();
    const unsigned int shuffleCount = 2;
    for (unsigned int i = 0; i < size * shuffleCount; i++)
    {
        int currentIndex = i % size;
        int newIndex = getNumberFromInterval(0, size - 1);
        T temp = array.at(newIndex);
        array.at(newIndex) = array.at(currentIndex);
        array.at(currentIndex) = temp;
    }
}

} // namespace randomutils
