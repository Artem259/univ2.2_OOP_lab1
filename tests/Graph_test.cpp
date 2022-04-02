#include <vector>
#include "../Graph.h"
#include "gtest/gtest.h"

TEST(Graph, TestRandomGraph)
{
    int iter = 10000;

    std::vector<std::vector<unsigned>> matrixGraphEdges;
    std::vector<std::vector<unsigned>> listGraphEdges;
    MatrixGraph<double, double> matrixGraph;
    ListGraph<double, double> listGraph;
    for(unsigned i=0; i<iter; i++)
    {
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
            ASSERT_EQ(matrixGraph.size(), listGraph.size());

            ASSERT_EQ(matrixGraph.checkEdge(0, matrixGraph.size()-1), listGraph.checkEdge(0, matrixGraph.size()-1));
            ASSERT_EQ(matrixGraph.getRouteVertices(0, matrixGraph.size()-1), listGraph.getRouteVertices(0, listGraph.size()-1));

            ASSERT_EQ(matrixGraph.weaklyConnected(), listGraph.weaklyConnected());
            ASSERT_EQ(matrixGraph.stronglyConnected(), listGraph.stronglyConnected());

            matrixGraph.delVertex(0);
            listGraph.delVertex(0);
            matrixGraphEdges = matrixGraph.getEdges();
            listGraphEdges = listGraph.getEdges();

            ASSERT_EQ(matrixGraphEdges, listGraphEdges);

            if(!matrixGraphEdges.empty() && !listGraphEdges.empty())
            {
                matrixGraph.delEdge(matrixGraphEdges[0][0],matrixGraphEdges[0][1]);
                listGraph.delEdge(listGraphEdges[0][0],listGraphEdges[0][1]);
            }
        }
        matrixGraph.clear();
        listGraph.clear();
    }
}