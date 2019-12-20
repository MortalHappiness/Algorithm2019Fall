#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <queue>
#include "heap.h"

// ======================================

#define NIL -1
#define INF 2147483647

// ======================================

typedef struct {
    int key;
    int parent;
} Node;

typedef struct {
    int to;
    int weight;
} Edge;

class Graph {
public:
    // constructor
    Graph(const int,
          const bool,
          const std::vector<int>&,
          const std::vector<int>&,
          const std::vector<int>&);
    // add edge
    void add_edge(int, int, int);

    // getters
    int n_vertices(void) { return _n_vertices; };
    int n_edges(void) { return _n_edges; };
    bool is_directed(void) { return _is_directed; };

    // adjacency list
    std::vector<std::vector<Edge>> adj_list;
    // vector of nodes
    std::vector<Node> node_list;

private:
    // number of vertices
    int _n_vertices;
    // number of edges
    int _n_edges;
    // whether the graph is a directed graph
    bool _is_directed;
};

// ======================================

void BFS(Graph&);

void MST(Graph&);

void XXX(Graph&);

// ======================================

#endif
