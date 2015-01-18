#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>


int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int> data;
    data.reserve(N);
    std::istream_iterator<int> input(std::cin);
    for (int i = 0; i < N; ++i) {
        data.push_back(*input++);
    }
    
    std::sort(data.begin(), data.end(),
              [] (int x, int y) { return y < x; });
    
    while (data.size() != 0) {
        std::cout << data.size() << std::endl;
        int last = data.back();
        while (data.back() == last) {
            data.pop_back();
        }
    }
    return 0;
}

