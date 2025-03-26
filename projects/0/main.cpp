#include <iostream>

using namespace std;

int main() {
    cout << "Hello Rushed World!" << endl;

    int cArray[5] = {0, 1, 2, 3, 4};

    // C-style array
    {
        std::cout <<"Line "<<__LINE__<<" : "<<(sizeof(cArray) / sizeof(int)) << std::endl;
    }

    {//Bad
        auto handleArray = [](int arr[5]) {
            std::cout <<"Line "<<__LINE__<<" : "<<(sizeof(arr) / sizeof(int)) << std::endl;
        };
        handleArray(cArray);
    }

    {//Just a litle bit better
        auto handleArray = [](int *arr, const size_t sz) {
            std::cout <<"Line "<<__LINE__<<" : "<< sz << std::endl;
        };
        handleArray(cArray,5);
    }

    {//Ok
        auto handleArray = []<size_t N>(int(&arr)[N]) {
            std::cout << "Line " << __LINE__ << " : " << N << std::endl;
        };
        handleArray(cArray);
    }

/*
    {//Compile error
        auto handleArray = [](int arr[5]) {
            for (int &el : arr) {
                std::cout << el << ", " << std::endl;
            }
        };
        handleArray(cArray);
    }
*/
    return 0;
}
