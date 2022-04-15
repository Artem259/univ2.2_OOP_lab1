#include <vector>
#include <algorithm>
#include "../Geometry.h"
#include "gtest/gtest.h"

Point roundPoint(Point &point)
{
    point = point.round(3);
    return point;
}
double roundDouble(double number)
{
    return std::round(number*1000)/1000;
}

TEST(Geometry, LineAndLine)
{
    Point res;

    res = Line{2,3,-5} && Line{3,5,-4};
    roundPoint(res);
    EXPECT_EQ(res, Point({13,-7}));

    res = Line{-6,2,5} && Line{3,5,-4};
    roundPoint(res);
    EXPECT_EQ(res, Point({0.917,0.25}));

    res = Line{-1,-1,5} && Line{6.5,-4,50};
    roundPoint(res);
    EXPECT_EQ(res, Point({-2.857,7.857}));

    res = Line{-60,1,58} && Line{60,1,-59};
    roundPoint(res);
    EXPECT_EQ(res, Point({0.975, 0.5}));

    res = Line{-1,1,0} && Line{1,1,0};
    roundPoint(res);
    EXPECT_EQ(res, Point({0, 0}));

    res = Line{-60,1,58} && Line{2,-4};
    roundPoint(res);
    EXPECT_EQ(res, Point({0.931, -2.138}));

    res = Line{0,50,-25} && Line{0.005,-0.005, 1};
    roundPoint(res);
    EXPECT_EQ(res, Point({-199.5, 0.5}));

    res = Line{50,50,-25} && Line{0.005,-0.005, 1};
    roundPoint(res);
    EXPECT_EQ(res, Point({-99.75, 100.25}));

    res = Line{3,4,-5} && Line{6,-7, 8};
    roundPoint(res);
    EXPECT_EQ(res, Point({0.067, 1.2}));

    res = Line{0,4,0} && Line{1,-7, 1};
    roundPoint(res);
    EXPECT_EQ(res, Point({-1, 0}));
}
TEST(Geometry, CircleAndCircle)
{
    std::vector<Point> res;

    res = Circle{{1.44,-1.44},16} && Circle{{14,-12.5},15};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{-0.192,-17.357}, {17.022, 2.192}}));

    res = Circle{{0,2},4} && Circle{{0,-8},6};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{0,-2}}));

    res = Circle{{0,2},4} && Circle{{1,-8},6};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Circle{{5,2},4} && Circle{{5,2.1},3.7};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Circle{{0,2},5} && Circle{{1,3},6};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{-4.977,2.477}, {0.477,-2.977}}));

    res = Circle{{0,2},5} && Circle{{0,-3},2};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{-1.96,-2.6}, {1.96,-2.6}}));

    res = Circle{{0,2},5} && Circle{{1.1,-2.9},10.03};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Circle{{0,2},5} && Circle{{1.1,-2.9},10.02};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{-1.287,6.832}, {-0.902,6.918}}));

    res = Circle{{0,2},4} && Circle{{1,-8},6};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Circle{{1.1,-1050},0.5} && Circle{{0,2},5};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({}));
}
TEST(Geometry, LineAndCircle)
{
    std::vector<Point> res;

    res = Line{-60,1,58} && Circle{{4,3},5};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{0.951,-0.962}, {1.084,7.062}}));

    res = Line{2,-4} && Circle{{10,3},5};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Line{0,-1,-7} && Circle{{10,3},10};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{10,-7}}));

    res = Line{0,0} && Circle{{0,0},1};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{-1,0}, {1,0}}));

    res = Line{1,4,-1} && Circle{{0,0},1};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{-0.882,0.471}, {1,0}}));

    res = Line{1,4,-1} && Circle{{5,0},1};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{4.529,-0.882}, {5,-1}}));

    res = Line{1,4.3,-1} && Circle{{5.2,-3.6},2.59};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{5.366,-1.015}, {6.192,-1.207}}));

    res = Line{0,4.3,-2} && Circle{{5.2,-3.6},2.59};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({}));

    res = Line{0,4,4} && Circle{{1,1},2};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({{1,-1}}));

    res = Line{1.25,-1} && Circle{{1.44,-1.44},16};
    std::sort(res.begin(), res.end());
    std::for_each(res.begin(), res.end(), roundPoint);
    EXPECT_EQ(res, std::vector<Point>({ {-9.61,-13.012}, {10.304,11.88}}));
}
TEST(Geometry, AngleLineLine)
{
    double res;

    res = angle(Line{2, 3, -5}, Line{2, 3, 4});
    EXPECT_EQ(roundDouble(res), roundDouble(double(0)));

    res = angle(Line{2, 3, -5}, Line{-6, -9, 8});
    EXPECT_EQ(roundDouble(res), roundDouble(double(0)));

    res = angle(Line{2, 3, -5}, Line{2, 3, -5});
    EXPECT_EQ(roundDouble(res), roundDouble(double(0)));

    res = angle(Line{0, 0}, Line{1, -10});
    EXPECT_EQ(roundDouble(res), roundDouble(double(M_PI/4)));

    res = angle(Line{0, 0}, Line{0.5, -10});
    EXPECT_EQ(roundDouble(res), roundDouble(double(0.463648)));

    res = angle(Line{0.5, 6}, Line{1, -10});
    EXPECT_EQ(roundDouble(res), roundDouble(double(0.321751)));

    res = angle(Line{0.5, 6}, Line{0.25, 100});
    EXPECT_EQ(roundDouble(res), roundDouble(double(0.218669)));
}
TEST(Geometry, AngleCircleCircle)
{
    double res;

    res = angle(Circle{{1.44, -1.44}, 16}, Circle{{14, -12.5}, 15});
    EXPECT_EQ(roundDouble(res), roundDouble(double(1.1389)));

    res = angle(Circle{{0, 2}, 5}, Circle{{0, -3}, 2});
    EXPECT_EQ(roundDouble(res), roundDouble(double(1.369438)));

    res = angle(Circle{{0, 2}, 4}, Circle{{0, -8}, 6});
    EXPECT_EQ(roundDouble(res), roundDouble(double(0)));

    res = angle(Circle{{0, 2}, 4}, Circle{{1, -8}, 6});
    EXPECT_EQ(roundDouble(res), roundDouble(double(-1)));

    res = angle(Circle{{5, 2}, 4}, Circle{{5, 2.1}, 3.7});
    EXPECT_EQ(roundDouble(res), roundDouble(double(-1)));
}
TEST(Geometry, SymmetricPoint)
{
    Point res;

    res = Point({0, 0}).symmetric(Line({0, 2}));
    EXPECT_EQ(res, Point({0,4}));

    res = Point({0, 0}).symmetric(Line({1, 0}));
    EXPECT_EQ(res, Point({0,0}));

    res = Point({0, 1}).symmetric(Line({1, 0}));
    EXPECT_EQ(res, Point({1,0}));

    res = Point({30, 110}).symmetric(Line({2, 0}));
    EXPECT_EQ(res, Point({70,90}));

    res = Point({3, 15}).symmetric(Line({5, -3, 8}));
    EXPECT_EQ(res, Point({double(161)/17,double(189)/17}));
}
TEST(Geometry, SymmetricLine)
{
    Line res;

    res = Line({1, 0}).symmetric(Line({0, 0}));
    EXPECT_EQ(res, Line({-1,0}));

    res = Line({3.2, -2, 1.12}).symmetric(Line({3.2, -2, 1.12}));
    EXPECT_EQ(res, Line({3.2,-2,1.12}));

    res = Line({1, -2, -6.5}).symmetric(Line({1, -2, 1}));
    EXPECT_EQ(res, Line({1,-2,8.5}));

    res = Line({0, -2}).symmetric(Line({0, 5}));
    EXPECT_EQ(res, Line({0,12}));

    res = Line({1, -2}).symmetric(Line({-1, 2}));
    EXPECT_EQ(res, Line({1,-2}));
}
TEST(Geometry, SymmetricCircle)
{
    Circle res;

    res = Circle({{0, 0}, 2.22}).symmetric(Line({0, 2}));
    EXPECT_EQ(res, Circle({{0,4},2.22}));

    res = Circle({{0, 0}, 0.25}).symmetric(Line({1, 0}));
    EXPECT_EQ(res, Circle({{0,0}, 0.25}));

    res = Circle({{0, 1}, 4.2}).symmetric(Line({1, 0}));
    EXPECT_EQ(res, Circle({{1,0},4.2}));

    res = Circle({{30, 110}, 1}).symmetric(Line({2, 0}));
    EXPECT_EQ(res, Circle({{70,90},1}));

    res = Circle({{3, 15}, 6.66}).symmetric(Line({5, -3, 8}));
    EXPECT_EQ(res, Circle({{double(161)/17,double(189)/17},6.66}));
}
TEST(Geometry, InversionLine)
{
    std::shared_ptr<Geometry> res;

    res = Line{0.54, 0.08}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Circle&>(*res).round(3), Circle({{1.2987,-3.7013},sqrt(2.17844)}).round(3));

    res = Line{-2.56, 0.66116}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Circle&>(*res).round(3), Circle({{39.84451,9.78301},sqrt(1650.74459)}).round(3));

    res = Line{0, -3}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Circle&>(*res).round(3), Circle({{2,-1},sqrt(16)}).round(3));

    res = Line{-0.25, -4.5}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Line&>(*res).round(3), Line({-0.25,-4.5}).round(3));

    res = Line{0, -5}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Line&>(*res).round(3), Line({0,-5}).round(3));
}
TEST(Geometry, InversionCircle)
{
    std::shared_ptr<Geometry> res;

    res = Circle{{4.62563, -7.05884}, sqrt(0.20522)}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Circle&>(*res).round(3), Circle({{5.84443,-8.01454},sqrt(0.43997)}).round(3));

    res = Circle{{1.63727, -6.04978}, sqrt(7.09914)}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Circle&>(*res).round(3), Circle({{2.98947,-2.13642},sqrt(52.82391)}).round(3));

    res = Circle{{2, -5}, sqrt(8)}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Circle&>(*res).round(3), Circle({{2,-5},sqrt(32)}).round(3));

    res = Circle{{2, -5}, sqrt(16)}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Circle&>(*res).round(3), Circle({{2,-5},sqrt(16)}).round(3));

    res = Circle{{-1, -8}, sqrt(18)}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Line&>(*res), Line({-0.7071067811865,-0.7071067811865,-4.006938426724}));

    res = Circle{{8, 4}, sqrt(117)}.inversion({{2, -5}, 4});
    EXPECT_EQ(dynamic_cast<Line&>(*res), Line({0.5547001962252,0.8320502943378,2.311250817605}));
}