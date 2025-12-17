#include "gtest/gtest.h"
#include "pentagon.hpp"
#include <memory>
#include <sstream>
#include <cmath>

TEST(PentagonTest, AreaAndCenter)
{
    Array<std::pair<double, double>> coords;
    double r = 1.0;
    for (int i = 0; i < 5; ++i) {
        double angle = 2.0 * 3.14159265 * i / 5.0;
        coords.Push({r * cos(angle), r * sin(angle)});
    }
    Pentagon<double> p(coords);
    double expected_area = 5 * pow(r * sqrt(2 - 2 * cos(2 * 3.14159265 / 5)), 2) / (4 * tan(3.14159265 / 5));
    EXPECT_NEAR(p.square(), expected_area, 1e-6);
    auto center = p.geom_center();
    EXPECT_NEAR(center.first, 0.0, 1e-6);
    EXPECT_NEAR(center.second, 0.0, 1e-6);
}

TEST(PentagonTest, Equality)
{
    Array<std::pair<double, double>> coords1, coords2;
    for (int i = 0; i < 5; ++i) {
        double angle = 2.0 * 3.14159265 * i / 5.0;
        coords1.Push({cos(angle), sin(angle)});
        coords2.Push({cos(angle), sin(angle)});
    }
    Pentagon<double> p1(coords1), p2(coords2);
    EXPECT_TRUE(p1 == p2);
}

TEST(PentagonTest, Center) {
    Array<std::pair<double,double>> arr;
    arr.Push({0,0});
    arr.Push({2,0});
    arr.Push({3,1});
    arr.Push({1,2});
    arr.Push({-1,1});

    Pentagon<double> p(arr);

    auto c = p.geom_center();
    EXPECT_NEAR(c.first, 1.0, 1e-6);
    EXPECT_NEAR(c.second, 0.8, 1e-6);
}

TEST(PentagonTest, Compare) {
    Array<std::pair<double,double>> a1;
    Array<std::pair<double,double>> a2;

    for (int i = 0; i < 5; i++) {
        a1.Push({(double)i, 0});
        a2.Push({(double)i, 0});
    }

    Pentagon<double> p1(a1), p2(a2);

    EXPECT_TRUE(p1 == p2);
}

TEST(PentagonTest, SquareNonZero) {
    Array<std::pair<double,double>> arr;
    for (int i = 0; i < 5; i++)
        arr.Push({(double)i, 0});

    Pentagon<double> p(arr);
    EXPECT_GT(p.square(), 0);
}
