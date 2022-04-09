#ifndef GEOMETRY_H
#define GEOMETRY_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <vector>
#include <cassert>
#include <string>
#include <memory>

#define EPSILON 1e-12

class Geometry;
struct Point;
class Line;
class Circle;

//---------------------------------------------------------------------------------------------------------------//

class Geometry
{
public:
    virtual ~Geometry() = 0;
};

class Point : public Geometry
{
public:
    double x = 0;
    double y = 0;

    Point(double x, double y) : x(x), y(y) {};
    Point() : x(0), y(0) {};

    Point getSymmetric(const Line &line) const;
    Point getInversion(const Circle &circle) const;
    bool isLiesOn(const Line &line) const;
    bool isLiesOn(const Circle &circle) const;
    std::string getString() const;
    Point round(const unsigned &n) const;

    Point operator -() const;
    friend double getDistance(const Point &first, const Point &second);
    friend std::ostream& operator <<(std::ostream &ofs, const Point &point);
    friend bool operator ==(const Point &first, const Point &second);
    friend bool operator !=(const Point &first, const Point &second);
    friend bool operator >(const Point &first, const Point &second);
    friend bool operator <(const Point &first, const Point &second);
    friend Point operator +(const Point &first, const Point &second);
    friend Point operator -(const Point &first, const Point &second);
};

class Line : public Geometry
{
private:
    double a,b,c; //format: ax+by+c=0, b!=0
public:
    Line() : a(-1), b(1), c(0) {}; //y-x=0
    Line(double a, double b, double c) : a(a), b(b), c(c) {};
    Line(const Line &line);
    Line(double _k, double _b); //y=kx+b => -kx+y-b=0
    Line(const Point &first, const Point &second);
    void set(double _a, double _b, double _c);
    void set(double _k, double _b); //y=kx+b => -kx+y-b=0
    void set(const Point &first, const Point &second);
    void setA(double _a);
    void setB(double _b);
    void setC(double _c);
    double getA() const;
    double getB() const;
    double getC() const;

    Line getSymmetric(const Line &line) const;
    std::shared_ptr<Geometry> getInversion(const Circle &circle) const;
    Point getProjection(const Point &point) const;
    std::string getString() const;
    Line round(const unsigned &n) const;

    friend std::ostream& operator <<(std::ostream &ofs, const Line &line);
    friend bool operator ==(const Line &first, const Line &second);
    friend bool operator !=(const Line &first, const Line &second);
    friend Point operator &&(const Line &first, const Line &second);

    friend double getAngle(const Line &first, const Line &second);
    friend double getAngle(const Line &line, const Circle &circle);
    friend double getAngle(const Circle &circle, const Line &line);
    friend std::vector<Point> operator &&(const Line &line, const Circle &circle);
    friend std::vector<Point> operator &&(const Circle &circle, const Line &line);
    friend std::vector<Point> operator &&(const Circle &first, const Circle &second);
};

class Circle : public Geometry
{
private:
    Point center{};
    double radius;

    Line getTangent(const Point &point) const;
public:
    Circle() : center(0,0), radius(1) {}; //(x2)+(y2)=1
    Circle(Point center, double radius) : center(std::move(center)), radius(radius) {};
    explicit Circle(double radius) : center(0,0), radius(radius) {};
    Circle(const Circle &circle);
    void setCenter(Point _center);
    void setRadius(double _radius);
    Point getCenter() const;
    double getRadius() const;

    Circle getSymmetric(const Line &line) const;
    std::shared_ptr<Geometry> getInversion(const Circle &circle) const;
    Point getProjection(const Point &point) const;
    std::string getString() const;
    Circle round(const unsigned &n) const;

    friend std::ostream& operator <<(std::ostream &ofs, const Circle &circle);
    friend bool operator ==(const Circle &first, const Circle &second);
    friend bool operator !=(const Circle &first, const Circle &second);
    friend std::vector<Point> operator &&(const Circle &first, const Circle &second);

    friend double getAngle(const Circle &first, const Circle &second);
    friend double getAngle(const Line &line, const Circle &circle);
    friend double getAngle(const Circle &circle, const Line &line);
    friend std::vector<Point> operator &&(const Line &line, const Circle &circle);
    friend std::vector<Point> operator &&(const Circle &circle, const Line &line);
};

//---------------------------------------------------------------------------------------------------------------//

bool isEqual(double a, double b)
{
    return (std::abs(a-b) <= EPSILON);
}

//---------------------------------------------------------------------------------------------------------------//
// functions related to struct Geometry

Geometry::~Geometry() = default;

//---------------------------------------------------------------------------------------------------------------//
// functions related to struct Point

Point Point::getSymmetric(const Line &line) const
{
    Point point = line.getProjection(*this);
    return {2*point.x-x, 2*point.y-y};
}
Point Point::getInversion(const Circle &circle) const
{
    Point c = circle.getCenter();
    double r = circle.getRadius();
    double resX = c.x+(r*r*(x-c.x))/((x-c.x)*(x-c.x)+(y-c.y)*(y-c.y));
    double resY = c.y+(r*r*(y-c.y))/((x-c.x)*(x-c.x)+(y-c.y)*(y-c.y));
    return {resX, resY};
}
bool Point::isLiesOn(const Line &line) const
{
    return isEqual(line.getA()*x+line.getB()*y+line.getC(), 0);
}
bool Point::isLiesOn(const Circle &circle) const
{
    double centerX = circle.getCenter().x;
    double centerY = circle.getCenter().y;
    double R = circle.getRadius();
    return isEqual((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY), R*R);
}
std::string Point::getString() const
{
    return "{"+std::to_string(x)+";"+std::to_string(y)+"}";
}
Point Point::round(const unsigned &n) const
{
    Point res;
    auto power = static_cast<unsigned>(pow(10,n));
    res.x = std::round(x*power)/power;
    res.y = std::round(y*power)/power;
    return res;
}
Point Point::operator -() const
{
    return {-this->x, -this->y};
}
double getDistance(const Point &first, const Point &second)
{
    return sqrt((first.x-second.x)*(first.x-second.x)+(first.y-second.y)*(first.y-second.y));
}
std::ostream& operator <<(std::ostream &ofs, const Point &point)
{
    ofs << point.getString();
    return ofs;
}
bool operator ==(const Point &first, const Point &second)
{
    return (isEqual(first.x, second.x) && isEqual(first.y, second.y));
}
bool operator !=(const Point &first, const Point &second)
{
    return !(first==second);
}
bool operator >(const Point &first, const Point &second)
{
    if(first.x>second.x) return true;
    if(first.x<second.x) return false;
    if(first.y>second.y) return true;
    return false;
}
bool operator <(const Point &first, const Point &second)
{
    return !(first>second || first==second);
}
Point operator +(const Point &first, const Point &second)
{
    return {first.x+second.x, first.y+second.y};
}
Point operator -(const Point &first, const Point &second)
{
    return first+(-second);
}

//---------------------------------------------------------------------------------------------------------------//
// functions related to class Line

Line::Line(const Line &line)
{
    a = line.a;
    b = line.b;
    c = line.c;
}
Line::Line(double _k, double _b)
{
    a = -_k;
    b = 1;
    c = -_b;
}
Line::Line(const Point &first, const Point &second)
{
    assert(first.x!=second.x);
    a = second.y-first.y;
    b = first.x-second.x;
    c = first.y*second.x-first.x*second.y;
}
void Line::set(double _a, double _b, double _c)
{
    assert(_b!=0);
    a = _a;
    b = _b;
    c = _c;
}
void Line::set(double _k, double _b)
{
    a = -_k;
    b = 1;
    c = -_b;
}
void Line::set(const Point &first, const Point &second)
{
    assert(first.x!=second.x);
    a = second.y-first.y;
    b = first.x-second.x;
    c = first.y*second.x-first.x*second.y;
}
void Line::setA(double _a)
{
    a = _a;
}
void Line::setB(double _b)
{
    assert(_b!=0);
    b = _b;
}
void Line::setC(double _c)
{
    c = _c;
}

double Line::getA() const
{
    return a;
}
double Line::getB() const
{
    return b;
}
double Line::getC() const
{
    return c;
}

Line Line::getSymmetric(const Line &line) const
{
    const double x1 = -1;
    const double x2 = 1;
    Point first = {x1, -(a/b)*x1-c/b};
    Point second = {x2, -(a/b)*x2-c/b};
    return {first.getSymmetric(line), second.getSymmetric(line)};
}
std::shared_ptr<Geometry> Line::getInversion(const Circle &circle) const
{
    if(circle.getCenter().isLiesOn(*this))
    {
        Line res = *this;
        return std::shared_ptr<Geometry>(new Line{res});
    }
    else
    {
        Circle res;
        Point point = this->getProjection(circle.getCenter());
        point = point.getInversion(circle);
        res.setRadius(getDistance(point, circle.getCenter())/2);
        res.setCenter({(point.x+circle.getCenter().x)/2, (point.y+circle.getCenter().y)/2});
        return std::shared_ptr<Geometry>(new Circle{res});
    }
}
Point Line::getProjection(const Point &point) const
{
    double x = point.x;
    double y = point.y;
    double tmpX = (c*a+a*b*y-b*b*x)/(-a*a-b*b);
    double tmpY = -(a/b)*tmpX-c/b;
    return {tmpX, tmpY};
}
std::string Line::getString() const
{
    return "("+std::to_string(a)+")x+("+std::to_string(b)+")y+("+std::to_string(c)+")=0";
}
Line Line::round(const unsigned &n) const
{
    Line res;
    auto power = static_cast<unsigned>(pow(10,n));
    res.a = std::round(a*power)/power;
    res.b = std::round(b*power)/power;
    res.c = std::round(c*power)/power;
    return res;
}

std::ostream& operator <<(std::ostream &ofs, const Line &line)
{
    ofs << line.getString();
    return ofs;
}
bool operator ==(const Line &first, const Line &second)
{
    return (getAngle(first,second) <= EPSILON);
}
bool operator !=(const Line &first, const Line &second)
{
    return !(first==second);
}
Point operator &&(const Line &first, const Line &second)
{
    assert(!(isEqual(first.a,second.a) && isEqual(first.b,second.b)));
    assert(!(isEqual(first.a,0) && isEqual(second.a,0)));
    Point res;
    res.x = (second.b*first.c-first.b*second.c)/(second.a*first.b-first.a*second.b);
    res.y = -(first.a/first.b)*res.x-(first.c/first.b);
    return res;
}

//---------------------------------------------------------------------------------------------------------------//
// functions related to class Circle

Circle::Circle(const Circle &circle)
{
    center = circle.center;
    radius = circle.radius;
}

void Circle::setCenter(Point _center)
{
    center = _center;
}
void Circle::setRadius(double _radius)
{
    radius = _radius;
}

Point Circle::getCenter() const
{
    return center;
}
double Circle::getRadius() const
{
    return radius;
}

Circle Circle::getSymmetric(const Line &line) const
{
    return {center.getSymmetric(line), radius};
}
std::shared_ptr<Geometry> Circle::getInversion(const Circle &circle) const
{
    if(circle.getCenter().isLiesOn(*this))
    {
        Line res;
        Line line{center, circle.center};
        line = {center, center+Point{line.getA(), line.getB()}};
        std::vector<Point> points = *this && line;
        res = Line{points[0].getInversion(circle), points[1].getInversion(circle)};
        return std::shared_ptr<Geometry>(new Line{res});
    }
    else
    {
        Circle res;
        double r = circle.radius;
        double x = circle.getCenter().x;
        double y = circle.getCenter().y;
        double s = (r*r)/((center.x-x)*(center.x-x)+(center.y-y)*(center.y-y)-radius*radius);
        res.setRadius(radius*abs(s));
        res.setCenter({x+s*(center.x-x), y+s*(center.y-y)});
        return std::shared_ptr<Geometry>(new Circle{res});
    }
}
Point Circle::getProjection(const Point &point) const
{
    assert(center != point);
    Line line{center, point};
    std::vector<Point> candidates = *this && line;
    if(getDistance(candidates[0], point) < getDistance(center, point)) return candidates[0];
    return candidates[1];
}
std::string Circle::getString() const
{
    return "(x-("+std::to_string(center.x)+"))^2 + (y-("+std::to_string(center.y)+"))^2 = ("+std::to_string(radius)+")^2";
}
Circle Circle::round(const unsigned &n) const
{
    Circle res;
    auto power = static_cast<unsigned>(pow(10,n));
    res.center = center.round(n);
    res.radius = std::round(radius*power)/power;
    return res;
}

std::ostream& operator <<(std::ostream &ofs, const Circle &circle)
{
    ofs << circle.getString();
    return ofs;
}
Line Circle::getTangent(const Point &point) const
{
    Line res;
    res.setA(point.x-center.x);
    res.setB(point.y-center.y);
    res.setC(center.x*center.x+center.y*center.y-radius*radius-center.y*point.y-center.x*point.x);
    return res;
}

bool operator ==(const Circle &first, const Circle &second)
{
    return (first.center==second.center && isEqual(first.radius,second.radius));
}
bool operator !=(const Circle &first, const Circle &second)
{
    return !(first==second);
}
std::vector<Point> operator &&(const Circle &first, const Circle &second)
{
    assert(first!=second);
    assert(!isEqual(first.center.y,second.center.y));
    Circle firstTmp = first;
    Circle secondTmp = second;
    Point offset = firstTmp.center;
    firstTmp.center = {0,0};
    secondTmp.center = secondTmp.center-offset;
    double x2 = secondTmp.center.x;
    double y2 = secondTmp.center.y;
    double r1 = firstTmp.radius;
    double r2 = secondTmp.radius;
    Line line;
    line.setA(-2*x2);
    line.setB(-2*y2);
    line.setC(x2*x2+y2*y2+r1*r1-r2*r2);
    std::vector<Point> points = firstTmp && line;
    for(auto &point: points)
    {
        point = point+offset;
    }
    return points;
}

//---------------------------------------------------------------------------------------------------------------//
// additional functions

double getAngle(const Line &first, const Line &second)
{
    double res = abs(atan(-(first.a/first.b))-atan(-(second.a/second.b)));
    if(res>M_PI/2) return M_PI-res;
    return res;
}
double getAngle(const Line &line, const Circle &circle)
{
    std::vector<Point> points = line && circle;
    if(points.empty()) return -1;
    return getAngle(line, circle.getTangent(points[0]));
}
double getAngle(const Circle &circle, const Line &line)
{
    return getAngle(line, circle);
}
double getAngle(const Circle &first, const Circle &second)
{
    std::vector<Point> points = first && second;
    if(points.empty()) return -1;
    return getAngle(first.getTangent(points[0]), second.getTangent(points[0]));
}
std::vector<Point> operator &&(const Line &line, const Circle &circle)
{
    std::vector<Point> res;
    double a = line.a, b = line.b, c = line.c;
    double x = circle.center.x, y = circle.center.y, r = circle.radius;
    double a2 = a*a, b2 = b*b, c2 = c*c;
    double x2 = x*x, y2 = y*y, r2 = r*r;
    //A(x2)+B(x)+C=0
    double A = a2+b2;
    double B = 2*(a*b*y+a*c-b2*x);
    double C = b2*x2+b2*y2+2*b*c*y+c2-r2*b2;
    double D = B*B-4*A*C; //D=b2-4ac
    if(D<0) return {};
    double sqrtD = sqrt(D);
    double X1 = (-B+sqrtD)/(2*A);
    double X2 = (-B-sqrtD)/(2*A);
    double Y1 = -(a/b)*X1-(c/b);
    double Y2 = -(a/b)*X2-(c/b);
    res.emplace_back(X1,Y1);
    if(isEqual(D,0)) return res;
    res.emplace_back(X2,Y2);
    return res;
}
std::vector<Point> operator &&(const Circle &circle, const Line &line)
{
    return (line && circle);
}

#endif
