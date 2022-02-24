#include <vector>
#include <algorithm>
#include "../Geometry.h"
#include "gtest/gtest.h"

void round3(Point &point)
{
    point = point.round(3);
}

TEST(Geometry, CircleAndCircle)
{
    std::vector<Point> res;

    res = Circle{{1.44,-1.44},16} && Circle{{14,-12.5},15};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{-0.192,-17.357}, {17.022, 2.192}}));

    res = Circle{{0,2},4} && Circle{{0,-8},6};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{0,-2}}));

    res = Circle{{0,2},4} && Circle{{1,-8},6};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Circle{{5,2},4} && Circle{{5,2.1},3.7};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Circle{{0,2},5} && Circle{{1,3},6};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{-4.977,2.477}, {0.477,-2.977}}));

    res = Circle{{0,2},5} && Circle{{0,-3},2};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{-1.96,-2.6}, {1.96,-2.6}}));

    res = Circle{{0,2},5} && Circle{{1.1,-2.9},10.03};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Circle{{0,2},5} && Circle{{1.1,-2.9},10.02};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{-1.287,6.832}, {-0.902,6.918}}));

    res = Circle{{0,2},4} && Circle{{1,-8},6};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Circle{{1.1,-1050},0.5} && Circle{{0,2},5};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({}));
}