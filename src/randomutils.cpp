#include <randomutils.h>
#include <random>

int randomutils::getNumberFromInterval(int start, int end)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(start, end);
    return distribution(generator);
}

void randomutils::shuffleArray(std::vector<char> &array)
{
    unsigned int size = array.size();
    for (unsigned int i = 0; i < size * 2; i++)
    {
        int currentIndex = i % size;
        int newIndex = getNumberFromInterval(0, size - 1);
        char temp = array.at(newIndex);
        array.at(newIndex) = array.at(currentIndex);
        array.at(currentIndex) = temp;
    }
}
