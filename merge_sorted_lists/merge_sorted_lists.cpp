/** Task: You need to merge n sorted lists to the sorted vector.
 *
 * Complexity O(n * k * log(k)) where k is a number of lists and n
 * is a number of elements in lists.
 *
 * Copyright 2014 Aman Orazaev
 */
#include <cstddef>
#include <list>
#include <vector>
#include <utility>
#include <queue>


std::vector<int> mergeSortedLists(std::vector<std::list<int>> inputLists)
{
    typedef std::pair<int, size_t> MinWithIndex;
    auto pairCmp = [] (
        const MinWithIndex& first,
        const MinWithIndex& second)
    {
        return first.first > second.first;
    };
    typedef
        std::priority_queue<
            MinWithIndex,
            std::vector<MinWithIndex>,
            decltype(pairCmp)>
        MinWithIndexHeap;

    MinWithIndexHeap firstElements(pairCmp);
    std::vector<int> result;

    for (size_t i = 0; i < inputLists.size(); ++i) {
       firstElements.push(MinWithIndex(inputLists[i].front(), i));
       inputLists[i].pop_front();
    }

    while (!firstElements.empty()) {
        auto current = firstElements.top();
        firstElements.pop();

        result.push_back(current.first);
        if (!inputLists[current.second].empty()) {
            firstElements.push(MinWithIndex(
                inputLists[current.second].front(),
                current.second));
            inputLists[current.second].pop_front();
        }
    }

    return result;
}


/////////////////////////////////////////////
//                Testing
/////////////////////////////////////////////

#include <iostream>
#include <algorithm>

template <typename C>
std::ostream& operator << (
    std::ostream& out,
    const std::vector<C>& collection)
{
    bool first = true;
    out << "{";
    for (const auto& elem: collection) {
        if (first) {
            first = false;
        } else {
            out << ", ";
        }
        out << elem;
    }
    return out << "}";
}

template <typename C>
void checkEqual(const C& got, const C& expect) {
    if (got.size() != expect.size()) {
        std::cout << "Got:    " << got << std::endl
                  << "Expect: " << expect << std::endl;
        throw std::runtime_error("Sizes are different");
    }

    for (size_t i = 0; i < got.size(); ++i) {
        if (got[i] != expect[i]) {
            std::cout << "Got:    " << got << std::endl
                      << "Expect: " << expect << std::endl;
            throw std::runtime_error("Different collections!");
        }
    }
}

int main() {
    {
        std::vector<std::list<int>> input = {
            {2, 10, 15},
            {1, 28, 30},
            {3, 11, 14}
        };

        auto mergedList = mergeSortedLists(input);
        checkEqual(mergedList, {1, 2, 3, 10, 11, 14, 15, 28, 30});

        checkEqual(mergeSortedLists({}), {});
    }
    return 0;
}
