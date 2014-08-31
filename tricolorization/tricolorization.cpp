#include <algorithm>
#include <cassert>


bool checkSelectedIsEqualToOther(
    const std::vector<int>& first,
    const std::vector<int>& second)
{
    if (first.size() > second.size()) {
        return checkSelectedIsEqualToOther(second, first);
    }

    int sum = 0;
    int i = 0;
    for (; i < first.size(); ++i) {
        sum += (first[i] - second[i]);
    }
    for (; i < second.size(); ++i) {
        sum -= second[i];
    }
    return sum == 0;
}


bool checkSelectedIsHalfOfOther(
    const std::vector<int>& selected,
    const std::vector<int>& other)
{
    int sum = 0;
    for (int i = 0; i < std::max(selected.size(), other.size()); ++i) {
        if (i < selected.size()) {
            sum += 2 * selected[i];
        }

        if (i < other.size()) {
            sum -= other[i];
        }
    }

    return sum == 0;
}


template <typename T>
void fastRemove(T& container, int position) {
    std::swap(container[position], container.back());
    container.pop_back();
}


std::string colorize(
    std::vector<int>& digitsToColor,
    const std::vector<int>& data,
    char background,
    std::string& digitsColor)
{
    std::string result(data.size(), background);
    for (size_t i = 0; i < data.size(); ++i) {
        auto iter = std::find(
            digitsToColor.begin(),
            digitsToColor.end(),
            data[i]);

        if (iter != digitsToColor.end()) {
            size_t position = iter - digitsToColor.begin();
            result[i] = digitsColor[position];
            fastRemove(digitsColor, position);
            fastRemove(digitsToColor, position);
        }
    }

    return result;
}


std::string twocolorization_(
    std::vector<int> green,
    std::vector<int> other,
    const std::vector<int> data)
{
    if (green.size() == 0) {
        return "";
    }

    if (checkSelectedIsEqualToOther(green, other)) {
        std::string color(green.size(), 'G');
        return colorize(green, data, 'B', color);
    }

    for (int i = 0; i < green.size(); ++i) {
        std::vector<int> nextGreen(green);
        std::vector<int> nextOther(other);

        std::swap(nextGreen[i], nextGreen.back());
        nextGreen.pop_back();
        nextOther.push_back(green[i]);
        std::string result = twocolorization_(nextGreen, nextOther, data);
        if (result != "") {
            return result;
        }
    }

    return "";
}


std::string twocolorization(const std::vector<int>& other) {
    return twocolorization_(other, {}, other);
}


std::string tricolorization_(
    std::vector<int> red,
    std::vector<int> other,
    const std::vector<int>& data)
{
    if (red.size() == 0) {
        return "";
    }

    if (checkSelectedIsHalfOfOther(red, other)) {
        std::string otherColor = twocolorization(other);
        if (otherColor != "") {
            return colorize(other, data, 'R', otherColor);
        }
    }

    for (int i = 0; i < red.size(); ++i) {
        std::vector<int> nextRed(red);
        std::vector<int> nextOther(other);

        std::swap(nextRed[i], nextRed.back());
        nextRed.pop_back();
        nextOther.push_back(red[i]);
        std::string result = tricolorization_(nextRed, nextOther, data);
        if (result != "") {
            return result;
        }
    }

    return "";
}


std::string tricolorization(const std::vector<int>& data) {
    std::string result = tricolorization_(data, {}, data);
    if (result == "") {
        return "imposible";
    }
    return result;
}


int main() {
    assert(tricolorization({1, 2, 3, 3}) == "BBGR");
    assert(tricolorization({1, 1, 1}) == "GBR");
    assert(tricolorization({1, 2, 3, 4, 5}) == "BRRBG");
    assert(tricolorization({1, 2, 3, 4}) == "imposible");
    assert(tricolorization({1, 1, 1, 1}) == "imposible");
    assert(tricolorization({1, 1, 1, 1, 2}) == "BBRRG");
    return 0;
}
