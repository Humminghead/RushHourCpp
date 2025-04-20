#include <functional>
#include <iostream>

using namespace std;

int main() {
    {
        // C++17: Recursive lambda via std::function
        auto factorial = [](int n) {
            std::function<int(int)> recurse = [&](int k) { return (k <= 1) ? 1 : k * recurse(k - 1); };
            return recurse(n);
        };
        std::cout << factorial(5) << "\n"; // 120
    }

    {
        // C++20: Recursive lambda with auto&& and Y-combinator
        auto factorial = [](auto self, int n) -> int { return (n <= 1) ? 1 : n * self(self, n - 1); };
        std::cout << factorial(factorial, 5) << "\n"; // 120
    }

    {
        auto factorial = [](this auto self, int n) -> int {
            return (n <= 1) ? 1 : n * self(n - 1); // No need to pass 'self'!
        };
        std::cout << factorial(5) << "\n";
        ; // Just call it normally
    }

    return 0;
}
