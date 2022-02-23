#include <vector>
#include <algorithm>
#include "../Geometry.h"
#include "gtest/gtest.h"

TEST(Geometry, CircleAndCircle)
{
    std::vector<Point> res;

    res = Circle({{1.44,-1.44},16}) && Circle({{14,-12.5},15});
    std::sort(res.begin(), res.end());
    EXPECT_EQ(res, std::vector<Point>({{17.022, 2.192}, {-0.192,-17.357}}));
}