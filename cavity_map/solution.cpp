#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

bool isBorder(
    size_t x,
    size_t y,
    const std::string * const buffers)
{
    return (x == 0 || y == 0
        || x == buffers[y % 3].size() - 1
        || y == buffers[y % 3].size() - 1);
}

bool isCavity(
    size_t x,
    size_t y,
    const std::string * const buffers)
{
    return (
        !isBorder(x, y, buffers)
        && buffers[y % 3][x] > buffers[(y + 1) % 3][x]
        && buffers[y % 3][x] > buffers[(y - 1) % 3][x]
        && buffers[y % 3][x] > buffers[y % 3][x + 1]
        && buffers[y % 3][x] > buffers[y % 3][x - 1]);
}

int main()
{
    size_t lakeSize;
    std::string buffers[3];

    std::cin >> lakeSize;
    std::cin >> buffers[0];
    for (size_t y = 1; y < lakeSize; ++y) {
        std::cin >> buffers[y % 3];
        std::cout << buffers[(y - 1) % 3][0];
        for (size_t x = 1; x < lakeSize; ++x) {
            if (isCavity(x, y - 1, buffers)) {
                std::cout << 'X';
            } else {
                std::cout << buffers[(y - 1) % 3][x];
            }
        }
        std::cout << std::endl;
    }
    std::cout << buffers[(lakeSize - 1) % 3] << std::endl;
    return 0;
}
