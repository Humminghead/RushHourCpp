#include <array>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "Hello Rushed World!" << endl;

    std::array<int, 5> Array{0, 1, 2, 3, 4};

    // STD array
    {
        auto handleArray = [](const auto &array) {
            for (auto &el : array) {
                std::cout << el << ", " << std::endl;
            }
        };
        handleArray(Array);

        // STD vector

        //Easy array to vector replacement
        std::vector<int> Vec{0, 1, 2, 3, 4};
        handleArray(Vec);
    }

    {
        std::cout << "Line " << __LINE__ << " : " << Array.size() << std::endl;
    }

    {
        auto handleArray = []<typename T, size_t N>(const std::array<T, N> &arr) {
            std::cout << "Line " << __LINE__ << " : " << "array size = " << N << std::endl;
        };
        handleArray(Array);
    }

    return 0;
}
