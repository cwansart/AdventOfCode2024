#include <iostream>
#include <filesystem>
#include <fstream>
#include <array>
#include <algorithm>
#include <cmath>
#include <stdexcept>

constexpr size_t len = 1000;

static void ReadNumbers(std::array<int, len>& lNumbers, std::array<int, len>& rNumbers)
{
    const std::filesystem::path file{ "C:/src/AdventOfCode2024/Day1/input.txt" };
    std::ifstream in{ file };
    if (!in)
    {
        throw std::runtime_error("failed to open file: " + file.string());
    }

    int lNum, rNum;
    size_t n = 0;
    while (in >> lNum >> rNum)
    {
        lNumbers[n] = lNum;
        rNumbers[n] = rNum;
        n++;
    }
}

static unsigned int Part1(std::array<int, len>& lNumbers, std::array<int, len>& rNumbers)
{
    std::sort(lNumbers.begin(), lNumbers.end());
    std::sort(rNumbers.begin(), rNumbers.end());

    unsigned int dist = 0;
    for (size_t n = 0; n < len; n++)
    {
        dist += std::abs(lNumbers[n] - rNumbers[n]);
    }

    return dist;
}

static unsigned int Part2(const std::array<int, len>& lNumbers, const std::array<int, len>& rNumbers)
{
    unsigned int similarity = 0;
    for (size_t n = 0; n < len; n++)
    {
        auto lNum = lNumbers[n];
        auto count = std::count(rNumbers.begin(), rNumbers.end(), lNum);
        similarity += lNum * count;
    }
    return similarity;
}

int main()
{
    try
    {
        std::array<int, len> lNumbers{}, rNumbers{};
        ReadNumbers(lNumbers, rNumbers);
        auto dist = Part1(lNumbers, rNumbers);
        auto similarity = Part2(lNumbers, rNumbers);

        std::cout << "distance:   " << dist << "\r\n"
                  << "similarity: " << similarity << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
