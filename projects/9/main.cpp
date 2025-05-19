
#include <iostream>
#include <set>
#include <cmath>
#include <array>

using Point = std::array<double, 2>;

// Функция вычисления "отклонения" (произвольная математическая операция)
double compute_deviation(const Point& p) {
    return std::sqrt(p[0]*p[0] + p[1]*p[1]); // Пример: расстояние до (0,0)
}

// Компаратор с потенциальной ошибкой
struct BuggyComparator {
    bool operator()(const Point& a, const Point& b) const {
        double da = compute_deviation(a);
        double db = compute_deviation(b);
        if (da == db) return a < b; // Проблемное место!
        return da < db;
    }
};

// Компаратор с исправлением через volatile
struct FixedComparator {
    bool operator()(const Point& a, const Point& b) const {
        volatile double da = compute_deviation(a);
        volatile double db = compute_deviation(b);
        if (da == db) return a < b;
        return da < db;
    }
};

void test_comparator(const char* name, auto comparator) {
    std::set<Point, decltype(comparator)> set(comparator);

    Point p1{1.0, 1.0}; // deviation = sqrt(2)
    Point p2{std::sqrt(2), 0.0}; // deviation = sqrt(2)

    std::cout << name << " test:\n";
    std::cout << "Inserting p1: " << set.insert(p1).second << "\n";
    std::cout << "Inserting p2: " << set.insert(p2).second << "\n";
    std::cout << "Set size: " << set.size() << "\n\n";
}

int main() {
    // Тестируем оба компаратора
    test_comparator("Buggy (без volatile)", BuggyComparator{});
    test_comparator("Fixed (с volatile)", FixedComparator{});

    return 0;
}
