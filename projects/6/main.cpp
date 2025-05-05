#include <iostream>

#include <map>
#include <vector>

#include <ChronoTimer/chronotimer.h>

using namespace std;

template <class T> auto testFuncVecLh(std::vector<T> &vec) -> void {
    for (auto it = std::begin(vec); it != std::end(vec); ++it) {
        *it += 1;
    }
}

template <class T> auto testFuncVecRh(std::vector<T> &vec) -> void {
    for (auto it = std::begin(vec); it != std::end(vec); it++) {
        *it += 1;
    }
}

template <class T> auto testFuncMapLh(std::map<T, T> &map) -> void {
    auto it = std::begin(map);
    for (; it != std::end(map); ++it) {
        it->second += 1;
    }
}

template <class T> auto testFuncMapRh(std::map<T, T> &map) -> void {
    auto it = std::begin(map);
    for (; it != std::end(map); it++) {
        it->second += 1;
    }
}

struct A
{
    A &operator+=(int v) {
        c += v;
        return *this;
    }

    int c{0};
};

int main() {
    // Vector
    {
        std::vector<int> vec(1'000'000);

        cerr << "_____________________VEC_LH_______________________\n";
        for (int n = 0; n < 10; n++)
            Estimate::ChronoTimer(testFuncVecLh<int>, vec).RunAndPrint<decltype(cerr), Estimate::Microseconds>(cerr);

        cerr << "_____________________VEC_RH_______________________\n";
        for (int n = 0; n < 10; n++)
            Estimate::ChronoTimer(testFuncVecRh<int>, vec).RunAndPrint<decltype(cerr), Estimate::Microseconds>(cerr);
    }

    // Map
    {
        std::map<int, int> map;
        for (int n = 0; n < 1'000'000; n++)
            map.try_emplace(n, n);

        cerr << "_____________________MAP_LH_______________________\n";
        for (int n = 0; n < 10; n++)
            Estimate::ChronoTimer(testFuncMapLh<int>, map).RunAndPrint<decltype(cerr), Estimate::Microseconds>(cerr);

        cerr << "_____________________MAP_RH_______________________\n";
        for (int n = 0; n < 10; n++)
            Estimate::ChronoTimer(testFuncMapRh<int>, map).RunAndPrint<decltype(cerr), Estimate::Microseconds>(cerr);
    }

    // Vector A
    {
        std::vector<A> vec(1'000'000);

        cerr << "_____________________VEC_A_LH_______________________\n";
        for (int n = 0; n < 10; n++)
            Estimate::ChronoTimer(testFuncVecLh<A>, vec).RunAndPrint<decltype(cerr), Estimate::Microseconds>(cerr);

        cerr << "_____________________VEC_A_RH_______________________\n";
        for (int n = 0; n < 10; n++)
            Estimate::ChronoTimer(testFuncVecRh<A>, vec).RunAndPrint<decltype(cerr), Estimate::Microseconds>(cerr);
    }
    return 0;
}
