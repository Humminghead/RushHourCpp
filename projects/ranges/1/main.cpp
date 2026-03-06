#include <ranges>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto result = nums
                  | std::views::filter([](int n) { return n % 2 == 0; })  // только чётные
                  | std::views::transform([](int n) { return n * n; })   // возводим в квадрат
                  | std::views::take(3);                                  // берём первые 3

    for (int x : result) {
        std::cout << x << ' ';  // 4 16 36
    }
}
