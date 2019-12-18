#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <queue>

// ======================================

// edge for undirected graph
typedef struct {
    int to;
    int weight;
    bool *remained; // whether edge should remain in the graph
} U_Edge;

// edge for directed graph
typedef struct {
    int to;
    int weight;
    bool remained; // whether edge should remain in the graph
} D_Edge;

// undirected graph
class U_Graph {
public:
    // constructor
    U_Graph(const int,
            const std::vector<int>&,
            const std::vector<int>&,
            const std::vector<int>&);
    // destructor
    ~U_Graph();
    // add edge
    void add_edge(int, int, int);

    // getters
    int n_vertices() {return _n_vertices;};
    int n_edges() {return _n_edges;};

    // get the edges that need to be deleted
    void deleted_edges(int&,
                       std::vector<int>&,
                       std::vector<int>&,
                       std::vector<int>&);

    // adjacency list
    std::vector<std::vector<U_Edge>> adj_list;

private:
    // number of vertices
    int _n_vertices;
    // number of edges
    int _n_edges;
    // vector of allocated bool pointers for deleting
    std::vector<bool*> _alloc_ptrs;
};

// directed graph
class D_Graph {

};

// ======================================

void BFS(U_Graph&);

void MST(U_Graph&);

void XXX(D_Graph&);

// ======================================

#endif
