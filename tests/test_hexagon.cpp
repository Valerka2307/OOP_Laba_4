#include "gtest/gtest.h"
#include "hexagon.hpp"
#include <memory>
#include <sstream>
#include <cmath>

TEST(HexagonTest, AreaAndCenter)
{
    Array<std::pair<double, double>> coords;
    double r = 1.0;
    for (int i = 0; i < 6; ++i) {
        double angle = 2.0 * 3.14159265 * i / 6.0;
        coords.Push({r * cos(angle), r * sin(angle)});
    }
    Hexagon<double> h(coords);
    double expected_area = 6 * pow(r * sqrt(2 - 2 * cos(2 * 3.14159265 / 6)), 2) / (4 * tan(3.14159265 / 6));
    EXPECT_NEAR(h.square(), expected_area, 1e-6);
    auto center = h.geom_center();
    EXPECT_NEAR(center.first, 0.0, 1e-6);
    EXPECT_NEAR(center.second, 0.0, 1e-6);
}

TEST(HexagonTest, Equality)
{
    Array<std::pair<double, double>> coords1, coords2;
    for (int i = 0; i < 6; ++i) {
        double angle = 2.0 * 3.14159265 * i / 6.0;
        coords1.Push({cos(angle), sin(angle)});
        coords2.Push({cos(angle), sin(angle)});
    }
    Hexagon<double> h1(coords1), h2(coords2);
    EXPECT_TRUE(h1 == h2);
}

TEST(HexagonTest, StreamInputOutput) {
    Hexagon<double> h;

    std::stringstream ss("1 2 3 4 5 6 7 8 9 10 11 12");

    ss >> h;

    std::stringstream out;
    out << h;

    EXPECT_TRUE(out.str().find("x: 1") != std::string::npos);
    EXPECT_TRUE(out.str().find("y: 12") != std::string::npos);
}

TEST(HexagonTest, CompareHexagons) {
    Array<std::pair<double,double>> arr1, arr2;

    for (int i = 0; i < 6; i++) {
        arr1.Push({(double)i, 1});
        arr2.Push({(double)i, 1});
    }

    Hexagon<double> h1(arr1), h2(arr2);

    EXPECT_TRUE(h1 == h2);
}

TEST(HexagonTest, SquarePositive) {
    Array<std::pair<double,double>> arr;
    arr.Push({0,0});
    arr.Push({1,0});
    arr.Push({2,1});
    arr.Push({1,2});
    arr.Push({0,2});
    arr.Push({-1,1});

    Hexagon<double> h(arr);

    EXPECT_GT(h.square(), 0);
}
