#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <cassert>
#include <stack>
#include <queue>

std::random_device rd;
std::mt19937 mt(rd());

template <class T_vertices, class T_edges>
class MatrixGraph;
template <class T_vertices, class T_edges>
class ListGraph;

//---------------------------------------------------------------------------------------------------------------//

template <class T_vertices, class T_edges>
class MatrixGraph
{
private:
    unsigned verticesN;
    std::vector<T_vertices> vertices; //data in vertices
    std::vector<std::vector<T_edges*>> edges; //!connectivity matrix!

    std::vector<std::vector<bool>> getMatrix() const;//returns copy of adjacency matrix (to change)
    bool DFS(unsigned start, const std::vector<std::vector<bool>> &matrix) const;
    std::vector<unsigned*> BFS(unsigned start, unsigned end) const;
public:
    MatrixGraph(); //empty constructor
    //MatrixGraph(MatrixGraph<T_vertices, T_edges> &toCopy); //copy constructor from MatrixGraph
    explicit MatrixGraph(const ListGraph<T_vertices, T_edges> &toCopy); //copy constructor from ListGraph
    ~MatrixGraph(); //destructor
    void addVertex(const T_vertices &data); //add a new vertex
    void delVertex(unsigned vertex); //delete a vertex
    void addEdge(unsigned from, unsigned to, const T_edges &data); //add a new edge
    void delEdge(unsigned from, unsigned to); //delete an edge
    void clear(); //cleans the graph
    bool isEdgeExists(unsigned from, unsigned to) const; //checks if there's an edge in the graph
    unsigned size() const; //returns the number of vertices in the graph
    std::vector<std::vector<unsigned>> getEdges() const; //return all edges in graph
    std::string getString() const; //return a string representation of adjacency matrix
    void randomGraph(unsigned minVertices, unsigned maxVertices, double edgeProb, const T_vertices &verticesData, const T_edges &edgesData);
    //fill graph with random number of vertices and random edges
    bool stronglyConnected() const; //checks if the graph is strongly connected
    bool weaklyConnected() const; //checks if the graph is weakly connected
    std::vector<unsigned> getRouteVertices(unsigned from, unsigned to) const; //returns vertices chain between 2 vertices [from-->to]
    unsigned getRouteLength(unsigned from, unsigned to) const; //returns number of edges between 2 vertices (or 0, if disconnected)

    T_vertices& operator()(unsigned vertex); //get a reference to vertex
    T_edges& operator()(unsigned from, unsigned to); //get a reference to edge
    //MatrixGraph<T_vertices, T_edges>& operator=(const MatrixGraph<T_vertices, T_edges> &toCopy); //copy MatrixGraph
    MatrixGraph<T_vertices, T_edges>& operator=(ListGraph<T_vertices, T_edges> &toCopy); //copy ListGraph
};

template <class T_vertices, class T_edges>
class ListGraph
{
private:
    struct edge
    {
        unsigned vertex;
        T_edges* data;
    };
    unsigned verticesN;
    std::vector<T_vertices> vertices; //data in vertices
    std::vector<std::vector<edge>> edges; //!connectivity list!

    std::vector<std::vector<unsigned>> getList() const; //returns copy of adjacency list (to change)
    bool DFS(unsigned start, const std::vector<std::vector<unsigned>> &list) const;
    std::vector<unsigned*> BFS(unsigned start, unsigned end) const;
public:
    ListGraph(); //empty constructor
    //ListGraph(ListGraph<T_vertices, T_edges> &toCopy); //copy constructor from ListGraph
    explicit ListGraph(const MatrixGraph<T_vertices, T_edges> &toCopy); //copy constructor from MatrixGraph
    ~ListGraph(); //destructor
    void addVertex(const T_vertices &data); //add a new vertex
    void delVertex(unsigned vertex); //delete a vertex
    void addEdge(unsigned from, unsigned to, const T_edges &data); //add a new edge
    void delEdge(unsigned from, unsigned to); //delete an edge
    void clear(); //cleans the graph
    bool isEdgeExists(unsigned from, unsigned to) const; //checks if there's an edge in the graph
    unsigned size() const; //returns the number of vertices in the graph
    std::vector<std::vector<unsigned>> getEdges() const; //return all edges in graph
    std::string getString() const; //return a string representation of adjacency list
    void randomGraph(unsigned minVertices, unsigned maxVertices, double edgeProb, const T_vertices &verticesData, const T_edges &edgesData);
    //fill graph with random number of vertices and random edges
    bool stronglyConnected() const; //checks if the graph is strongly connected
    bool weaklyConnected() const; //checks if the graph is weakly connected
    std::vector<unsigned> getRouteVertices(unsigned from, unsigned to) const; //returns vertices chain between 2 vertices [from-->to]
    unsigned getRouteLength(unsigned from, unsigned to) const; //returns number of edges between 2 vertices (or 0, if disconnected)

    T_vertices& operator()(unsigned vertex); //get a reference to vertex
    T_edges& operator()(unsigned from, unsigned to); //get a reference to edge
    //ListGraph<T_vertices, T_edges>& operator=(const ListGraph<T_vertices, T_edges> &toCopy); //copy ListGraph
    ListGraph<T_vertices, T_edges>& operator=(MatrixGraph<T_vertices, T_edges> &toCopy); //copy MatrixGraph
};

//---------------------------------------------------------------------------------------------------------------//
// functions related to class MatrixGraph

template <class T_vertices, class T_edges>
bool MatrixGraph<T_vertices, T_edges>::DFS(unsigned start, const std::vector<std::vector<bool>> &matrix) const
{
    auto visited = new bool[verticesN]{false};
    std::stack<unsigned> stack;
    stack.push(start);
    unsigned curr;
    while(!stack.empty())
    {
        curr = stack.top();
        stack.pop();
        if(!visited[curr])
        {
            visited[curr] = true;
            for(unsigned i=0; i<verticesN; i++)
            {
                if(matrix[curr][i]) stack.push(i);
            }
        }
    }
    for(unsigned i=0; i<verticesN; i++)
    {
        if(!visited[i])
        {
            delete []visited;
            return false;
        }
    }
    delete []visited;
    return true;
}

template <class T_vertices, class T_edges>
std::vector<unsigned*> MatrixGraph<T_vertices, T_edges>::BFS(unsigned start, unsigned end) const
{
    std::vector<unsigned*> prev{verticesN,nullptr};
    auto visited = new bool[verticesN]{false};
    std::queue<unsigned> queue;
    visited[start] = true;
    queue.push(start);
    unsigned curr;
    while(!queue.empty())
    {
        curr = queue.front();
        queue.pop();
        for(unsigned i=0; i<verticesN; i++)
        {
            if(edges[curr][i] && !visited[i])
            {
                visited[i] = true;
                queue.push(i);
                prev[i] = new unsigned{curr};
                if(i==end) return prev;
            }
        }
    }
    return prev;
}

template <class T_vertices, class T_edges>
MatrixGraph<T_vertices, T_edges>::MatrixGraph()
{
    verticesN = 0;
    vertices = {};
    edges = {};
}

template <class T_vertices, class T_edges>
MatrixGraph<T_vertices, T_edges>::MatrixGraph(const ListGraph<T_vertices, T_edges> &toCopy)
{
    verticesN = 0;
    *this = toCopy;
}

template <class T_vertices, class T_edges>
MatrixGraph<T_vertices, T_edges>::~MatrixGraph()
{
    this->clear();
}

template <class T_vertices, class T_edges>
void MatrixGraph<T_vertices, T_edges>::addVertex(const T_vertices &data)
{
    vertices.push_back(data);
    edges.push_back(std::vector<T_edges*> (edges.size()+1, nullptr));
    for(auto i = edges.begin(); i < edges.end()-1; i++)
    {
        (*i).push_back(nullptr);
    }
    verticesN++;
}

template <class T_vertices, class T_edges>
void MatrixGraph<T_vertices, T_edges>::delVertex(unsigned vertex)
{
    assert(vertex<verticesN);
    vertices.erase(vertices.begin()+vertex); //erasing vertex (with data)
    //deleting data in all edges FROM vertex
    for(auto i = edges[vertex].begin(); i < edges[vertex].end(); i++)
    {
        delete (*i);
    }
    edges.erase(edges.begin()+vertex); //erasing row from the connectivity matrix
    //deleting data in all edges TO vertex, erasing column of the connectivity matrix
    for(auto i = edges.begin(); i < edges.end(); i++)
    {
        delete (*i)[vertex];
        (*i).erase((*i).begin()+vertex);
    }
    verticesN--;
}

template <class T_vertices, class T_edges>
void MatrixGraph<T_vertices, T_edges>::addEdge(unsigned from, unsigned to, const T_edges &data)
{
    assert(from<verticesN && to<verticesN);
    assert(!edges[from][to]);
    edges[from][to] = new T_edges(data);
}

template <class T_vertices, class T_edges>
void MatrixGraph<T_vertices, T_edges>::delEdge(unsigned from, unsigned to)
{
    assert(from<verticesN && to<verticesN);
    assert(edges[from][to]);
    delete edges[from][to];
    edges[from][to] = nullptr;
}

template <class T_vertices, class T_edges>
void MatrixGraph<T_vertices, T_edges>::clear()
{
    while(verticesN>0)
    {
        this->delVertex(verticesN-1);
    }
}

template <class T_vertices, class T_edges>
bool MatrixGraph<T_vertices, T_edges>::isEdgeExists(unsigned from, unsigned to) const
{
    assert(from<verticesN && to<verticesN);
    if(edges[from][to]) return true;
    return false;
}

template <class T_vertices, class T_edges>
unsigned MatrixGraph<T_vertices, T_edges>::size() const
{
    return verticesN;
}

template <class T_vertices, class T_edges>
std::vector<std::vector<unsigned>> MatrixGraph<T_vertices, T_edges>::getEdges() const
{
    std::vector<std::vector<unsigned>> res;
    for(unsigned i=0; i<verticesN; i++)
    {
        for(unsigned j=0; j<verticesN; j++)
        {
            if(edges[i][j]) res.push_back({i,j});
        }
    }
    return res;
}

template <class T_vertices, class T_edges>
std::vector<std::vector<bool>> MatrixGraph<T_vertices, T_edges>::getMatrix() const
{
    std::vector<std::vector<bool>> res;
    for(unsigned i=0; i<verticesN; i++)
    {
        res.emplace_back();
        for(unsigned j=0; j<verticesN; j++)
        {
            if(edges[i][j]) res.back().push_back(true);
            else res.back().push_back(false);
        }
    }
    return res;
}

template <class T_vertices, class T_edges>
std::string MatrixGraph<T_vertices, T_edges>::getString() const
{
    std::string res;
    for(unsigned i=0; i<verticesN; i++)
    {
        for(unsigned j=0; j<verticesN; j++)
        {
            if(edges[i][j]) res += "1 ";
            else res += "0 ";
        }
        res += "\n";
    }
    return res;
}

template <class T_vertices, class T_edges>
void MatrixGraph<T_vertices, T_edges>::randomGraph(unsigned minVertices, unsigned maxVertices,
                                                   double edgeProb, const T_vertices &verticesData, const T_edges &edgesData)
{
    assert(minVertices<=maxVertices);
    assert(edgeProb>=0 && edgeProb<=1);
    this->clear();
    std::uniform_int_distribution<unsigned> randInt(minVertices, maxVertices);
    std::uniform_real_distribution<double> randDouble(0, 1);
    unsigned n = randInt(mt);
    double isEdge;
    for(unsigned i=0; i<n; i++)
    {
        addVertex(verticesData);
    }
    for(unsigned i=0; i<verticesN; i++)
    {
        for(unsigned j=0; j<verticesN; j++)
        {
            isEdge = randDouble(mt);
            if(isEdge<edgeProb)
            {
                addEdge(i, j, edgesData);
            }
        }
    }
}

template <class T_vertices, class T_edges>
bool MatrixGraph<T_vertices, T_edges>::stronglyConnected() const
{
    assert(verticesN>0);
    auto matrix = this->getMatrix();
    if(!DFS(0, matrix)) return false;
    for(unsigned i=0; i<verticesN; i++)
    {
        for(unsigned  j=i+1; j<verticesN; j++)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    if(!DFS(0, matrix)) return false;
    return true;
}

template <class T_vertices, class T_edges>
bool MatrixGraph<T_vertices, T_edges>::weaklyConnected() const
{
    assert(verticesN>0);
    auto matrix = this->getMatrix();
    for(unsigned i=0; i<verticesN; i++)
    {
        for(unsigned  j=i+1; j<verticesN; j++)
        {
            matrix[i][j] = matrix[i][j] || matrix[j][i];
            matrix[j][i] = matrix[i][j];
        }
    }
    if(!DFS(0, matrix)) return false;
    return true;
}

template <class T_vertices, class T_edges>
std::vector<unsigned> MatrixGraph<T_vertices, T_edges>::getRouteVertices(unsigned from, unsigned to) const
{
    assert(from!=to);
    std::vector<unsigned> route;
    std::vector<unsigned*> prev = this->BFS(from, to);
    unsigned curr;
    if(prev[to])
    {
        route.push_back(to);
        curr = *prev[to];
        while(curr!=from)
        {
            route.push_back(curr);
            curr = *prev[curr];
        }
        route.push_back(from);
    }
    for(auto &i: prev) delete i;
    std::reverse(route.begin(), route.end());
    return route;
}

template <class T_vertices, class T_edges>
unsigned MatrixGraph<T_vertices, T_edges>::getRouteLength(unsigned from, unsigned to) const
{
    unsigned length = (this->getRouteVertices(from,to)).size();
    if(length==0) return 0;
    return length-1;
}

template <class T_vertices, class T_edges>
T_vertices& MatrixGraph<T_vertices, T_edges>::operator()(unsigned vertex)
{
    assert(vertex<verticesN);
    return vertices[vertex];
}

template <class T_vertices, class T_edges>
T_edges& MatrixGraph<T_vertices, T_edges>::operator()(unsigned from, unsigned to)
{
    assert(from<verticesN && to<verticesN);
    assert(edges[from][to]);
    return *edges[from][to];
}

template <class T_vertices, class T_edges>
MatrixGraph<T_vertices, T_edges>& MatrixGraph<T_vertices, T_edges>::operator=(ListGraph<T_vertices, T_edges> &toCopy)
{
    this->clear();
    unsigned currLen = toCopy.size();
    for(unsigned i=0; i<currLen; i++)
    {
        this->addVertex(toCopy(i));
    }
    std::vector<std::vector<unsigned>> edgesCopy = toCopy.getEdges();
    currLen = edgesCopy.size();
    for(unsigned i=0; i<currLen; i++)
    {
        this->addEdge(edgesCopy[i][0], edgesCopy[i][1], toCopy(edgesCopy[i][0], edgesCopy[i][1]));
    }
    return *this;
}

//---------------------------------------------------------------------------------------------------------------//
//functions related to class ListGraph

template <class T_vertices, class T_edges>
bool ListGraph<T_vertices, T_edges>::DFS(unsigned start, const std::vector<std::vector<unsigned>> &list) const
{
    auto visited = new bool[verticesN]{false};
    std::stack<unsigned> stack;
    stack.push(start);
    unsigned curr, currLen;
    while(!stack.empty())
    {
        curr = stack.top();
        stack.pop();
        if(!visited[curr])
        {
            visited[curr] = true;
            currLen = list[curr].size();
            for(unsigned i=0; i<currLen; i++)
            {
                stack.push(list[curr][i]);
            }
        }
    }
    for(unsigned i=0; i<verticesN; i++)
    {
        if(!visited[i])
        {
            delete []visited;
            return false;
        }
    }
    delete []visited;
    return true;
}

template <class T_vertices, class T_edges>
std::vector<unsigned*> ListGraph<T_vertices, T_edges>::BFS(unsigned start, unsigned end) const
{
    std::vector<unsigned*> prev{verticesN,nullptr};
    auto visited = new bool[verticesN]{false};
    std::queue<unsigned> queue;
    visited[start] = true;
    queue.push(start);
    unsigned curr, currLen;
    while(!queue.empty())
    {
        curr = queue.front();
        queue.pop();
        currLen = edges[curr].size();
        for(unsigned i=0; i<currLen; i++)
        {
            if(!visited[edges[curr][i].vertex])
            {
                visited[edges[curr][i].vertex] = true;
                queue.push(edges[curr][i].vertex);
                prev[edges[curr][i].vertex] = new unsigned{curr};
                if(edges[curr][i].vertex==end) return prev;
            }
        }
    }
    return prev;
}

template <class T_vertices, class T_edges>
ListGraph<T_vertices, T_edges>::ListGraph()
{
    verticesN = 0;
    vertices = {};
    edges = {};
}

template <class T_vertices, class T_edges>
ListGraph<T_vertices, T_edges>::ListGraph(const MatrixGraph<T_vertices, T_edges> &toCopy)
{
    verticesN = 0;
    *this = toCopy;
}

template <class T_vertices, class T_edges>
ListGraph<T_vertices, T_edges>::~ListGraph()
{
    this->clear();
}

template <class T_vertices, class T_edges>
void ListGraph<T_vertices, T_edges>::addVertex(const T_vertices &data)
{
    vertices.push_back(data);
    edges.push_back({});
    verticesN++;
}

template <class T_vertices, class T_edges>
void ListGraph<T_vertices, T_edges>::delVertex(unsigned vertex)
{
    assert(vertex<verticesN);
    vertices.erase(vertices.begin()+vertex); //erasing vertex (with data)
    //deleting data in all edges FROM vertex
    for(auto i = edges[vertex].begin(); i < edges[vertex].end(); i++)
    {
        delete (*i).data;
    }
    edges.erase(edges.begin()+vertex); //erasing row from the connectivity list
    verticesN--;
    //deleting data in all edges TO vertex, decrement all next vertices
    unsigned currLen;
    for(unsigned i=0; i<verticesN; i++)
    {
        currLen = edges[i].size();
        for(unsigned j=0; j<currLen; j++)
        {
            if(edges[i][j].vertex==vertex)
            {
                delete edges[i][j].data;
                edges[i].erase(edges[i].begin()+j);
                j--;
                currLen--;
            }
            else if(edges[i][j].vertex>vertex)
            {
                edges[i][j].vertex--;
            }
        }
    }
}

template <class T_vertices, class T_edges>
void ListGraph<T_vertices, T_edges>::addEdge(unsigned from, unsigned to, const T_edges &data)
{
    assert(from<verticesN && to<verticesN);
    assert(!this->isEdgeExists(from, to));
    edges[from].push_back({to, new T_edges(data)});
}

template <class T_vertices, class T_edges>
void ListGraph<T_vertices, T_edges>::delEdge(unsigned from, unsigned to)
{
    assert(from<verticesN && to<verticesN);
    unsigned currLen = edges[from].size();
    for(unsigned i=0; i<currLen; i++)
    {
        if(edges[from][i].vertex==to)
        {
            delete edges[from][i].data;
            edges[from].erase(edges[from].begin()+i);
            return;
        }
    }
    assert(false);
}

template <class T_vertices, class T_edges>
void ListGraph<T_vertices, T_edges>::clear()
{
    while(verticesN>0)
    {
        this->delVertex(verticesN-1);
    }
}

template <class T_vertices, class T_edges>
bool ListGraph<T_vertices, T_edges>::isEdgeExists(unsigned from, unsigned to) const
{
    assert(from<verticesN && to<verticesN);
    unsigned currLen = edges[from].size();
    for(unsigned i=0; i<currLen; i++)
    {
        if(edges[from][i].vertex==to) return true;
    }
    return false;
}

template <class T_vertices, class T_edges>
unsigned ListGraph<T_vertices, T_edges>::size() const
{
    return verticesN;
}

template <class T_vertices, class T_edges>
std::vector<std::vector<unsigned>> ListGraph<T_vertices, T_edges>::getEdges() const
{
    std::vector<std::vector<unsigned>> res;
    unsigned currLen;
    for(unsigned i=0; i<verticesN; i++)
    {
        currLen = edges[i].size();
        for(unsigned j=0; j<currLen; j++)
        {
            res.push_back({i,edges[i][j].vertex});
        }
    }
    return res;
}

template <class T_vertices, class T_edges>
std::vector<std::vector<unsigned>> ListGraph<T_vertices, T_edges>::getList() const
{
    std::vector<std::vector<unsigned>> res;
    unsigned currLen;
    for(unsigned i=0; i<verticesN; i++)
    {
        res.emplace_back();
        currLen = edges[i].size();
        for(unsigned j=0; j<currLen; j++)
        {
            res.back().push_back(edges[i][j].vertex);
        }
    }
    return res;
}

template <class T_vertices, class T_edges>
std::string ListGraph<T_vertices, T_edges>::getString() const
{
    std::string res;
    unsigned currLen;
    for(unsigned i=0; i<verticesN; i++)
    {
        res += std::to_string(i) + ": ";
        currLen = edges[i].size();
        for(unsigned j=0; j<currLen; j++)
        {
            res += std::to_string(edges[i][j].vertex) + " ";
        }
        res += "\n";
    }
    return res;
}

template <class T_vertices, class T_edges>
void ListGraph<T_vertices, T_edges>::randomGraph(unsigned minVertices, unsigned maxVertices,
                                                 double edgeProb, const T_vertices &verticesData, const T_edges &edgesData)
{
    assert(minVertices<=maxVertices);
    assert(edgeProb>=0 && edgeProb<=1);
    this->clear();
    std::uniform_int_distribution<unsigned> randInt(minVertices, maxVertices);
    std::uniform_real_distribution<double> randDouble(0, 1);
    unsigned n = randInt(mt);
    double isEdge;
    for(unsigned i=0; i<n; i++)
    {
        this->addVertex(verticesData);
    }
    for(unsigned i=0; i<verticesN; i++)
    {
        for(unsigned j=0; j<verticesN; j++)
        {
            isEdge = randDouble(mt);
            if(isEdge<edgeProb)
            {
                addEdge(i, j, edgesData);
            }
        }
    }
}

template <class T_vertices, class T_edges>
bool ListGraph<T_vertices, T_edges>::stronglyConnected() const
{
    assert(verticesN>0);
    auto list = this->getList();
    if(!DFS(0, list)) return false;
    std::vector<std::vector<unsigned>> list2(verticesN);
    unsigned currLen;
    for(unsigned i=0; i<verticesN; i++)
    {
        currLen = edges[i].size();
        for(unsigned j=0; j<currLen; j++)
        {
            list2[edges[i][j].vertex].push_back(i);
        }
    }
    if(!DFS(0, list2)) return false;
    return true;
}

template <class T_vertices, class T_edges>
bool ListGraph<T_vertices, T_edges>::weaklyConnected() const
{
    assert(verticesN>0);
    auto list = this->getList();
    unsigned currLen;
    for(unsigned i=0; i<verticesN; i++)
    {
        currLen = list[i].size();
        for(unsigned j=0; j<currLen; j++)
        {
            if(!this->isEdgeExists(list[i][j],i))
            {
                list[list[i][j]].push_back(i);
            }
        }
    }
    if(!DFS(0, list)) return false;
    return true;
}

template <class T_vertices, class T_edges>
std::vector<unsigned> ListGraph<T_vertices, T_edges>::getRouteVertices(unsigned from, unsigned to) const
{
    assert(from!=to);
    std::vector<unsigned> route;
    std::vector<unsigned*> prev = this->BFS(from, to);
    unsigned curr;
    if(prev[to])
    {
        route.push_back(to);
        curr = *prev[to];
        while(curr!=from)
        {
            route.push_back(curr);
            curr = *prev[curr];
        }
        route.push_back(from);
    }
    for(auto &i: prev) delete i;
    std::reverse(route.begin(), route.end());
    return route;
}

template <class T_vertices, class T_edges>
unsigned ListGraph<T_vertices, T_edges>::getRouteLength(unsigned from, unsigned to) const
{
    unsigned length = (this->getRouteVertices(from,to)).size();
    if(length==0) return 0;
    return length-1;
}

template <class T_vertices, class T_edges>
T_vertices& ListGraph<T_vertices, T_edges>::operator()(unsigned vertex)
{
    assert(vertex<verticesN);
    return vertices[vertex];
}

template <class T_vertices, class T_edges>
T_edges& ListGraph<T_vertices, T_edges>::operator()(unsigned from, unsigned to)
{
    assert(from<verticesN && to<verticesN);
    unsigned currLen = edges[from].size();
    for(unsigned i=0; i<currLen; i++)
    {
        if(edges[from][i].vertex==to) return *edges[from][i].data;
    }
    assert(false);
    return *edges[0][0].data; //can't be reached
}

template <class T_vertices, class T_edges>
ListGraph<T_vertices, T_edges>& ListGraph<T_vertices, T_edges>::operator=(MatrixGraph<T_vertices, T_edges> &toCopy)
{
    this->clear();
    unsigned currLen = toCopy.size();
    for(unsigned i=0; i<currLen; i++)
    {
        this->addVertex(toCopy(i));
    }
    std::vector<std::vector<unsigned>> edgesCopy = toCopy.getEdges();
    currLen = edgesCopy.size();
    for(unsigned i=0; i<currLen; i++)
    {
        this->addEdge(edgesCopy[i][0], edgesCopy[i][1], toCopy(edgesCopy[i][0], edgesCopy[i][1]));
    }
    return *this;
}

#endif
