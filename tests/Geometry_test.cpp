#include <vector>
#include <algorithm>
#include "../Geometry.h"
#include "gtest/gtest.h"

void round3(Point &point)
{
    point = point.round(3);
}

TEST(Geometry, LineAndLine)
{
    Point res;

    res = Line{2,3,-5} && Line{3,5,-4};
    round3(res);
    EXPECT_EQ(res, Point({13,-7}));

    res = Line{-6,2,5} && Line{3,5,-4};
    round3(res);
    EXPECT_EQ(res, Point({0.917,0.25}));

    res = Line{-1,-1,5} && Line{6.5,-4,50};
    round3(res);
    EXPECT_EQ(res, Point({-2.857,7.857}));

    res = Line{-60,1,58} && Line{60,1,-59};
    round3(res);
    EXPECT_EQ(res, Point({0.975, 0.5}));

    res = Line{-1,1,0} && Line{1,1,0};
    round3(res);
    EXPECT_EQ(res, Point({0, 0}));

    res = Line{-60,1,58} && Line{2,-4};
    round3(res);
    EXPECT_EQ(res, Point({0.931, -2.138}));

    res = Line{0,50,-25} && Line{0.005,-0.005, 1};
    round3(res);
    EXPECT_EQ(res, Point({-199.5, 0.5}));

    res = Line{50,50,-25} && Line{0.005,-0.005, 1};
    round3(res);
    EXPECT_EQ(res, Point({-99.75, 100.25}));

    res = Line{3,4,-5} && Line{6,-7, 8};
    round3(res);
    EXPECT_EQ(res, Point({0.067, 1.2}));

    res = Line{0,4,0} && Line{1,-7, 1};
    round3(res);
    EXPECT_EQ(res, Point({-1, 0}));
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
TEST(Geometry, LineAndCircle)
{
    std::vector<Point> res;

    res = Line{-60,1,58} && Circle{{4,3},5};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{0.951,-0.962}, {1.084,7.062}}));

    res = Line{2,-4} && Circle{{10,3},5};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Line{0,-1,-7} && Circle{{10,3},10};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{10,-7}}));

    res = Line{0,0} && Circle{{0,0},1};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{-1,0}, {1,0}}));

    res = Line{1,4,-1} && Circle{{0,0},1};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{-0.882,0.471}, {1,0}}));

    res = Line{1,4,-1} && Circle{{5,0},1};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{4.529,-0.882}, {5,-1}}));

    res = Line{1,4.3,-1} && Circle{{5.2,-3.6},2.59};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{5.366,-1.015}, {6.192,-1.207}}));

    res = Line{0,4.3,-2} && Circle{{5.2,-3.6},2.59};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Line{0,4,4} && Circle{{1,1},2};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({{1,-1}}));

    res = Line{1.25,-1} && Circle{{1.44,-1.44},16};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), round3);
    EXPECT_EQ(res, std::vector<Point>({ {-9.61,-13.012}, {10.304,11.88}}));
}
