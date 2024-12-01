#include <iostream>
#include <filesystem>
#include <fstream>
#include <array>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <cstdint>

constexpr uint16_t len = 1000;

static void ReadNumbers(const std::filesystem::path& file, std::array<uint32_t, len>& lNumbers, std::array<uint32_t, len>& rNumbers)
{
    std::ifstream in{ file };
    if (!in)
    {
        throw std::runtime_error("failed to open file: " + file.string());
    }

    uint32_t lNum, rNum;
    uint16_t n = 0;
    while (in >> lNum >> rNum && n < len)
    {
        lNumbers[n] = lNum;
        rNumbers[n] = rNum;
        n++;
    }
}

static uint32_t Part1(std::array<uint32_t, len>& lNumbers, std::array<uint32_t, len>& rNumbers)
{
    std::sort(lNumbers.begin(), lNumbers.end());
    std::sort(rNumbers.begin(), rNumbers.end());

    uint32_t dist = 0;
    for (uint16_t n = 0; n < len; n++)
    {
        dist += (uint32_t)std::abs((int64_t)lNumbers[n] - rNumbers[n]);
    }

    return dist;
}

static uint32_t Part2(const std::array<uint32_t, len>& lNumbers, const std::array<uint32_t, len>& rNumbers)
{
    uint32_t similarity = 0;
    for (uint16_t n = 0; n < len; n++)
    {
        auto lNum = lNumbers[n];
        auto count = std::count(rNumbers.begin(), rNumbers.end(), lNum);
        similarity += (uint32_t)(lNum * count);
    }
    return similarity;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "missing file path parameter" << std::endl;
        return -1;
    }
    const std::filesystem::path file{ argv[1] };

    try
    {
        std::array<uint32_t, len> lNumbers{}, rNumbers{};
        ReadNumbers(file, lNumbers, rNumbers);
        auto dist = Part1(lNumbers, rNumbers);
        auto similarity = Part2(lNumbers, rNumbers);

        std::cout << "distance:   " << dist << "\r\n"
                  << "similarity: " << similarity << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
