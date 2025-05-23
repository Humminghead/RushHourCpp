#include <array>
#include <cmath>
#include <iostream>
#include <set>

using Point = std::array<double, 2>;

// Функция вычисления "отклонения" (произвольная математическая операция)
double compute_deviation(const Point &p) {
    const Point p0{1, 0};
    const Point vp0p1{-1 / std::sqrt(2), 1 / std::sqrt(2)};
    const Point vp0p{p[0] - 1, p[1]};
    const double dotprod = vp0p1[0] * vp0p[0] + vp0p1[1] * vp0p[1];
    const Point proj{1 + dotprod * vp0p1[0], p0[1] + dotprod * vp0p1[1]};
    return std::sqrt((proj[0] - p[0]) * (proj[0] - p[0]) + (proj[1] - p[1]) * (proj[1] - p[1]));
    // return std::sqrt(p[0]*p[0] + p[1]*p[1]);
}

// Компаратор с потенциальной ошибкой
struct BuggyComparator {
    bool operator()(const Point &a, const Point &b) const {
        double da{0}, db{0};
        da = compute_deviation(a);
        db = compute_deviation(b);
        if (da == db)
            return a < b; // Проблемное место!
        return da < db;
    }
};

// Компаратор с исправлением через volatile
struct FixedComparator {
    bool operator()(const Point &a, const Point &b) const {
        volatile double da = compute_deviation(a);
        volatile double db = compute_deviation(b);
        if (da == db)
            return a < b;
        return da < db;
    }
};

void test_comparator(const char *name, auto comparator) {
    std::set<Point, decltype(comparator)> set(comparator);

    Point p1{1.0, 1.0}; // deviation = sqrt(2)
    // Point p2{std::sqrt(2), 0.0}; // deviation = sqrt(2)
    Point p2{0.0, 0.0}; // deviation = sqrt(2)
    set.insert(p1);
    set.insert(p2);
    std::cout << name << std::endl;
    std::cout << "Set size: " << set.size() << "\n\n";
}

int main() {
    // Тестируем оба компаратора
    test_comparator("Buggy (без volatile)", BuggyComparator{});
    test_comparator("Fixed (с volatile)", FixedComparator{});

    return 0;
}
