#include <iostream>
#include <vector>
#include "Graph.h"
#include "Geometry.h"

bool TestRandomGraph(unsigned iter)
{
    std::vector<std::vector<unsigned>> matrixGraphEdges;
    std::vector<std::vector<unsigned>> listGraphEdges;
    MatrixGraph<double, double> matrixGraph;
    ListGraph<double, double> listGraph;
    for(unsigned i=0; i<iter; i++)
    {
        std::cout<<"Test "<<i<<": ";
        switch(i%2)
        {
            case 0:
            {
                matrixGraph.randomGraph(3,10,0.5,0,0);
                listGraph = matrixGraph;
                break;
            }
            case 1:
            {
                listGraph.randomGraph(3,10,0.5,0,0);
                matrixGraph = listGraph;
                break;
            }
        }
        for(int j=0; j<2; j++)
        {
            if(matrixGraph.size() != listGraph.size())
            {
                std::cout<<"FAILED [size]\n";
                return false;
            }
            if(matrixGraph.isEdgeExists(0, matrixGraph.size()-1) != listGraph.isEdgeExists(0, matrixGraph.size()-1))
            {
                std::cout<<"FAILED [checkEdge]\n";
                return false;
            }
            if(matrixGraph.getRouteLength(0, matrixGraph.size()-1) != listGraph.getRouteLength(0, listGraph.size()-1))
            {
                std::cout<<"FAILED [getRouteLength]\n";
                return false;
            }
            if(matrixGraph.getRouteVertices(0, matrixGraph.size()-1) != listGraph.getRouteVertices(0, listGraph.size()-1))
            {
                std::cout<<"FAILED [getRouteVertices]\n";
                return false;
            }
            if(matrixGraph.weaklyConnected() != listGraph.weaklyConnected())
            {
                std::cout<<"FAILED [weaklyConnected]\n";
                return false;
            }
            if(matrixGraph.stronglyConnected() != listGraph.stronglyConnected())
            {
                std::cout<<"FAILED [stronglyConnected]\n";
                return false;
            }
            matrixGraph.delVertex(0);
            listGraph.delVertex(0);
            matrixGraphEdges = matrixGraph.getEdges();
            listGraphEdges = listGraph.getEdges();
            if(matrixGraphEdges != listGraphEdges)
            {
                std::cout<<"FAILED [getEdges]\n";
                return false;
            }
            if(!matrixGraphEdges.empty() && !listGraphEdges.empty())
            {
                matrixGraph.delEdge(matrixGraphEdges[0][0],matrixGraphEdges[0][1]);
                listGraph.delEdge(listGraphEdges[0][0],listGraphEdges[0][1]);
            }
        }
        matrixGraph.clear();
        listGraph.clear();
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool LineAndLine()
{
    std::vector<Line> l1, l2;
    std::vector<Point> res;

    l1.emplace_back(2,3,-5);
    l2.emplace_back(3,5,-4);
    res.push_back({13,-7});

    l1.emplace_back(-6,2,5);
    l2.emplace_back(3,5,-4);
    res.push_back({0.917,0.25});

    l1.emplace_back(-1,-1,5);
    l2.emplace_back(6.5,-4,50);
    res.push_back({-2.857,7.857});

    l1.emplace_back(-60,1,58);
    l2.emplace_back(60,1,-59);
    res.push_back({0.975, 0.5});

    l1.emplace_back(-1,1,0);
    l2.emplace_back(1,1,0);
    res.push_back({0, 0});

    l1.emplace_back(-60,1,58);
    l2.emplace_back(2,-4);
    res.push_back({0.931, -2.138});

    l1.emplace_back(0,50,-25);
    l2.emplace_back(0.005,-0.005, 1);
    res.push_back({-199.5, 0.5});

    l1.emplace_back(50,50,-25);
    l2.emplace_back(0.005,-0.005, 1);
    res.push_back({-99.75, 100.25});

    l1.emplace_back(3,4,-5);
    l2.emplace_back(6,-7, 8);
    res.push_back({0.067, 1.2});

    l1.emplace_back(0,4,0);
    l2.emplace_back(1,-7, 1);
    res.push_back({-1, 0});

    Point currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = l1[i] && l2[i];
        if(!(round(currRes.x*1000)/1000==res[i].x && round(currRes.y*1000)/1000==res[i].y))
        {
            std::cout<<"FAILED\n";
            return false;
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool LineAndCircle()
{
    std::vector<Line> l;
    std::vector<Circle> c;
    std::vector<std::vector<Point>> res;

    l.emplace_back(-60,1,58);
    c.push_back({{4,3},5});
    res.push_back({{1.084,7.062}, {0.951,-0.962}});

    l.emplace_back(2,-4);
    c.push_back({{10,3},5});
    res.emplace_back();

    l.emplace_back(0,-1,-7);
    c.push_back({{10,3},10});
    res.push_back({{10,-7}});

    l.emplace_back(0,0);
    c.push_back({{0,0},1});
    res.push_back({{-1,0}, {1,0}});

    l.emplace_back(1,4,-1);
    c.push_back({{0,0},1});
    res.push_back({{-0.882,0.471}, {1,0}});

    l.emplace_back(1,4,-1);
    c.push_back({{5,0},1});
    res.push_back({{5,-1}, {4.529,-0.882}});

    l.emplace_back(1,4.3,-1);
    c.push_back({{5.2,-3.6},2.59});
    res.push_back({{6.192,-1.207}, {5.366,-1.015}});

    l.emplace_back(0,4.3,-2);
    c.push_back({{5.2,-3.6},2.59});
    res.emplace_back();

    l.emplace_back(0,4,4);
    c.push_back({{1,1},2});
    res.push_back({{1,-1}});

    l.emplace_back(1.25,-1);
    c.push_back({{1.44,-1.44},16});
    res.push_back({{10.304,11.88}, {-9.61,-13.012}});

    bool isFound;
    std::vector<Point> currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = l[i] && c[i];
        if(res[i].size()!=currRes.size())
        {
            std::cout<<"FAILED [size]\n";
            return false;
        }
        for(auto &currResI: currRes)
        {
            isFound = false;
            for(auto &resI: res[i])
            {
                if(round(currResI.x*1000)/1000==resI.x && round(currResI.y*1000)/1000==resI.y)
                {
                    isFound = true;
                    break;
                }
            }
            if(!isFound)
            {
                std::cout<<"FAILED [value]\n";
                return false;
            }
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool CircleAndCircle()
{
    std::vector<Circle> c1;
    std::vector<Circle> c2;
    std::vector<std::vector<Point>> res;

    c1.push_back({{1.44,-1.44},16});
    c2.push_back({{14,-12.5},15});
    res.push_back({{-0.192,-17.357}, {17.022, 2.192}});

    c1.push_back({{0,2},4});
    c2.push_back({{0,-8},6});
    res.push_back({{0,-2}});

    c1.push_back({{0,2},4});
    c2.push_back({{1,-8},6});
    res.emplace_back();

    c1.push_back({{5,2},4});
    c2.push_back({{5,2.1},3.7});
    res.emplace_back();

    c1.push_back({{0,2},4});
    c2.push_back({{1,3},6});
    res.emplace_back();

    c1.push_back({{0,2},5});
    c2.push_back({{1,3},6});
    res.push_back({{-4.977,2.477}, {0.477,-2.977}});

    c1.push_back({{0,2},5});
    c2.push_back({{0,-3},2});
    res.push_back({{-1.96,-2.6}, {1.96,-2.6}});

    c1.push_back({{0,2},5});
    c2.push_back({{1.1,-2.9},10.03});
    res.emplace_back();

    c1.push_back({{0,2},5});
    c2.push_back({{1.1,-2.9},10.02});
    res.push_back({{-1.287,6.832}, {-0.902,6.918}});

    c1.push_back({{1.1,-1050},0.5});
    c2.push_back({{0,2},5});
    res.emplace_back();

    bool isFound;
    std::vector<Point> currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = c1[i] && c2[i];
        if(res[i].size()!=currRes.size())
        {
            std::cout<<"FAILED [size]\n";
            return false;
        }
        for(auto &currResI: currRes)
        {
            isFound = false;
            for(auto &resI: res[i])
            {
                if(round(currResI.x*1000)/1000==resI.x && round(currResI.y*1000)/1000==resI.y)
                {
                    isFound = true;
                    break;
                }
            }
            if(!isFound)
            {
                std::cout<<"FAILED [value]\n";
                return false;
            }
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool AngleLineLine()
{
    std::vector<Line> l1, l2;
    std::vector<double> res;

    l1.emplace_back(2,3,-5);
    l2.emplace_back(2,3,4);
    res.push_back(-1);

    l1.emplace_back(0,0);
    l2.emplace_back(1,-10);
    res.push_back(M_PI/4);

    l1.emplace_back(0,0);
    l2.emplace_back(0.5,-10);
    res.push_back(0.463648);

    l1.emplace_back(0.5,6);
    l2.emplace_back(1,-10);
    res.push_back(0.321751);

    l1.emplace_back(0.5,6);
    l2.emplace_back(0.25,100);
    res.push_back(0.218669);

    double currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = getAngle(l1[i], l2[i]);
        if(round(res[i]*1000)/1000 != round(currRes*1000)/1000)
        {
            std::cout<<"FAILED [value]\n";
            return false;
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool AngleCircleCircle()
{
    std::vector<Circle> c1;
    std::vector<Circle> c2;
    std::vector<double> res;

    c1.push_back({{1.44,-1.44},16});
    c2.push_back({{14,-12.5},15});
    res.push_back(1.1389);

    c1.push_back({{0,2},5});
    c2.push_back({{0,-3},2});
    res.push_back(1.369438);

    c1.push_back({{0,2},4});
    c2.push_back({{0,-8},6});
    res.push_back(0);

    c1.push_back({{0,2},4});
    c2.push_back({{1,-8},6});
    res.push_back(-1);

    c1.push_back({{5,2},4});
    c2.push_back({{5,2.1},3.7});
    res.push_back(-1);

    double currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = getAngle(c1[i], c2[i]);
        if(round(res[i]*1000)/1000 != round(currRes*1000)/1000)
        {
            std::cout<<"FAILED [value]\n";
            return false;
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool SymmetricPoint()
{
    std::vector<Point> p;
    std::vector<Line> l;
    std::vector<Point> res;

    p.push_back({0,0});
    l.emplace_back(0,2);
    res.push_back({0,4});

    p.push_back({0,0});
    l.emplace_back(1,0);
    res.push_back({0,0});

    p.push_back({0,1});
    l.emplace_back(1,0);
    res.push_back({1,0});

    p.push_back({30,110});
    l.emplace_back(2,0);
    res.push_back({70,90});

    p.push_back({3,15});
    l.emplace_back(5,-3,8);
    res.push_back({double(161)/17,double(189)/17});

    Point currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = p[i].getSymmetric(l[i]);
        if(res[i] != currRes)
        {
            std::cout<<"FAILED [value]\n";
            return false;
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool SymmetricLine()
{
    std::vector<Line> l1;
    std::vector<Line> l2;
    std::vector<Line> res;

    l1.emplace_back(1,0);
    l2.emplace_back(0,0);
    res.emplace_back(-1,0);

    l1.emplace_back(3.2,-2,1.12);
    l2.emplace_back(3.2,-2,1.12);
    res.emplace_back(3.2,-2,1.12);

    l1.emplace_back(1,-2,-6.5);
    l2.emplace_back(1,-2,1);
    res.emplace_back(1,-2,8.5);

    l1.emplace_back(0,-2);
    l2.emplace_back(0,5);
    res.emplace_back(0,12);

    l1.emplace_back(1,-2);
    l2.emplace_back(-1,2);
    res.emplace_back(1,-2);

    Line currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = l1[i].getSymmetric(l2[i]);
        if(res[i] != currRes)
        {
            std::cout<<"FAILED [value]\n";
            return false;
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool SymmetricCircle()
{
    std::vector<Circle> c;
    std::vector<Line> l;
    std::vector<Circle> res;

    c.push_back({{0,0},2.22});
    l.emplace_back(0,2);
    res.push_back({{0,4},2.22});

    c.push_back({{0,0}, 0.25});
    l.emplace_back(1,0);
    res.push_back({{0,0}, 0.25});

    c.push_back({{0,1},4.2});
    l.emplace_back(1,0);
    res.push_back({{1,0},4.2});

    c.push_back({{30,110},1});
    l.emplace_back(2,0);
    res.push_back({{70,90},1});

    c.push_back({{3,15},6.66});
    l.emplace_back(5,-3,8);
    res.push_back({{double(161)/17,double(189)/17},6.66});

    Circle currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = c[i].getSymmetric(l[i]);
        if(res[i] != currRes)
        {
            std::cout<<"FAILED [value]\n";
            return false;
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool InversionLine()
{
    std::vector<Line> l;
    std::vector<Circle> c;
    std::vector<std::shared_ptr<Geometry>> res;

    //some tests (???)

    std::shared_ptr<Geometry> currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = l[i].getInversion(c[i]);
        if(res[i] != currRes)
        {
            std::cout<<"FAILED [value]\n";
            return false;
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}
bool InversionCircle()
{
    std::vector<Circle> c1;
    std::vector<Circle> c2;
    std::vector<std::shared_ptr<Geometry>> res;

    //some tests (???)

    std::shared_ptr<Geometry> currRes;
    size_t len = res.size();
    for(size_t i=0; i<len; i++)
    {
        std::cout<<"Test "<<i<<": ";
        currRes = c1[i].getInversion(c2[i]);
        if(res[i] != currRes)
        {
            std::cout<<"FAILED [value]\n";
            return false;
        }
        std::cout<<"Passed.\n";
    }
    std::cout<<"\nSection: Passed.\n";
    return true;
}

void Test()
{
    std::cout<<"\n--------------------------------\n";
    std::cout<<"Section 1 [RandomGraphs]:\n\n";
    if(!TestRandomGraph(10)) return;
    std::cout<<"--------------------------------\n";
    std::cout<<"Section 2 [Line && Line]:\n\n";
    if(!LineAndLine()) return;
    std::cout<<"--------------------------------\n";
    std::cout<<"Section 3 [Line && Circle]:\n\n";
    if(!LineAndCircle()) return;
    std::cout<<"--------------------------------\n";
    std::cout<<"Section 4 [Circle && Circle]:\n\n";
    if(!CircleAndCircle()) return;
    std::cout<<"--------------------------------\n";
    std::cout<<"Section 5 [Angle(Line Line)]:\n\n";
    if(!AngleLineLine()) return;
    std::cout<<"--------------------------------\n";
    std::cout<<"Section 6 [Angle(Circle Circle)]:\n\n";
    if(!AngleCircleCircle()) return;
    std::cout<<"--------------------------------\n";
    std::cout<<"Section 7 [Symmetric(Point)]:\n\n";
    if(!SymmetricPoint()) return;
    std::cout<<"--------------------------------\n";
    std::cout<<"Section 8 [Symmetric(Line)]:\n\n";
    if(!SymmetricLine()) return;
    std::cout<<"--------------------------------\n";
    std::cout<<"Section 9 [Symmetric(Circle)]:\n\n";
    if(!SymmetricCircle()) return;
    std::cout<<"--------------------------------\n";
    /*std::cout<<"Section 10 [Inversion(Line)]:\n\n";
    if(!InversionLine()) return;
    std::cout<<"--------------------------------\n";
    std::cout<<"Section 11 [Inversion(Circle)]:\n\n";
    if(!InversionCircle()) return;
    std::cout<<"--------------------------------\n";*/
}


int main()
{
    Test();
    std::cout<<"\n\n";

    MatrixGraph<Line, Point> myGraph;
    myGraph.addVertex({1,0});
    myGraph.addVertex({3,-4});
    myGraph.addVertex({0,0});
    myGraph.addEdge(1,0,{2,3});
    myGraph.addEdge(0,1,{0,5});
    myGraph.addEdge(2,1,{0,5});

    std::cout<<myGraph(0,1)<<std::endl;
    myGraph(0,1)=myGraph(1,0);
    std::cout<<myGraph(0,1)<<std::endl;
    std::cout<<getDistance(myGraph(0, 1),myGraph(2,1))<<std::endl;

    std::cout<<std::endl;
    Point p{2,-5};
    std::cout<<p<<std::endl;
    Line l{2,-5,1};
    std::cout<<l<<std::endl;
    Circle c{{2,-5}, 1};
    std::cout<<c<<std::endl;

    MatrixGraph<Line, std::vector<int>> a;

    return 0;
}
