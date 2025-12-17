#include "gtest/gtest.h"
#include "rhombus.hpp"
#include <memory>
#include <sstream>
#include <cmath>

TEST(RhombusTest, AreaAndCenter)
{
    Array<std::pair<double, double>> coords;
    coords.Push({0,0});
    coords.Push({2,2});
    coords.Push({4,0});
    coords.Push({2,-2});
    Rhombus<double> r(coords);
    double diag_1 = std::sqrt((coords[0].first - coords[2].first) * (coords[0].first - coords[2].first) + (coords[0].second - coords[2].second) * (coords[0].second - coords[2].second));
    double diag_2 = std::sqrt((coords[1].first - coords[3].first) * (coords[1].first - coords[3].first) + (coords[1].second - coords[3].second) * (coords[1].second - coords[3].second));
    double expected_area = diag_1 * diag_2 / 2;
    EXPECT_NEAR(r.square(), expected_area, 1e-6);
    auto center = r.geom_center();
    EXPECT_NEAR(center.first, 2.0, 1e-6);
    EXPECT_NEAR(center.second, 0.0, 1e-6);
}

TEST(RhombusTest, Equality)
{
    Array<std::pair<double, double>> coords1, coords2;
    coords1.Push({0,0});
    coords1.Push({2,2});
    coords1.Push({4,0});
    coords1.Push({2,-2});
    coords2.Push({0,0});
    coords2.Push({2,2});
    coords2.Push({4,0});
    coords2.Push({2,-2});
    Rhombus<double> r1(coords1), r2(coords2);
    EXPECT_TRUE(r1 == r2);
}

TEST(RhombusTest, Square) {
    Array<std::pair<double,double>> arr;
    arr.Push({0,0});
    arr.Push({2,2});
    arr.Push({4,0});
    arr.Push({2,-2});

    Rhombus<double> r(arr);

    EXPECT_NEAR(r.square(), 8.0, 1e-6);
}

TEST(RhombusTest, CopyAndMove) {
    Array<std::pair<double,double>> arr;
    for (int i = 0; i < 4; i++) arr.Push({(double)i, (double)(-i)});

    Rhombus<double> r1(arr);
    Rhombus<double> r2(r1);       // copy
    Rhombus<double> r3(std::move(r2)); // move

    EXPECT_TRUE(r1 == r3);
}

TEST(RhombusTest, StreamOutput) {
    Array<std::pair<double,double>> arr;
    arr.Push({1,2});
    arr.Push({3,4});
    arr.Push({5,6});
    arr.Push({7,8});

    Rhombus<double> r(arr);

    std::stringstream ss;
    ss << r;

    std::string out = ss.str();
    EXPECT_TRUE(out.find("1 coordinate") != std::string::npos);
    EXPECT_TRUE(out.find("x: 1") != std::string::npos);
}
