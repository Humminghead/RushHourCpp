#include <chronotimer.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

int main() {
    // C++17 Version
    auto cpp17 = [] {
        std::vector<int> nums = {1, 8, 3, 2, 5, 6, 7, 4, 9, 10};

        // Filter (only even numbers)
        auto begin = std::begin(nums);
        {
            auto last = std::prev(std::end(nums));
            for (auto it = begin; it <= last;) {
                if ((*it) % 2 == 0) {
                    *it *= (*it);
                    it++;
                } else {
                    std::swap(*it, *last);
                    nums.pop_back();
                    last = std::prev(std::end(nums));
                }
            };
            // Invalidate iterators (relocation will occur)
            // nums.shrink_to_fit();
        }

        // Sort
        std::sort(std::begin(nums), std::end(nums));

        // Print first 3 elements
        auto it4rd = begin;
        std::advance(it4rd, 3);
        std::for_each(begin, it4rd, [](auto &n) { std::cout << "n: " << n << "\n"; });
    };

    // C++23 Version
    auto cpp23 = [] {
        std::vector<int> nums = {1, 8, 3, 2, 5, 6, 7, 4, 9, 10};

        auto result = nums | std::views::filter([](int n) { return n % 2 == 0; }) // Filter (only even numbers)
                      | std::views::transform([](int n) { return n * n; })        // Multiply x2
                      | std::ranges::to<decltype(nums)>();

        std::sort(result.begin(), result.end());

        for (int n : result | std::views::take(3) // We take the first 3 numbers
        ) {
            std::cout << "n: " << n << "\n";
        }
    };

    {
        Estimate::ChronoTimer time1((std::function(cpp17)));
        std::cout << "-------------------- C++17 ----------------------\n";
        time1.Run();
        std::cout << "Time:" << time1.GetTime<Estimate::Nanoseconds>() << " ns\n";
    }

    {
        Estimate::ChronoTimer time2((std::function(cpp23)));
        std::cout << "-------------------- C++23 ----------------------\n";
        time2.Run();
        std::cout << "Time:" << time2.GetTime<Estimate::Nanoseconds>() << " ns\n";
    }

    return 0;
}
