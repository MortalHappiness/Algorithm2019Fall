#include <iostream>
#include "graph.h"

// ===================================
// graph implementation

U_Graph::U_Graph(const int n_vertices,
                 const std::vector<int>& edges_from,
                 const std::vector<int>& edges_to,
                 const std::vector<int>& weights) {
    adj_list.resize(n_vertices);
    const int n_edges = edges_from.size();
    _n_vertices = n_vertices;
    _n_edges = n_edges;
    int i;
    for (i = 0; i < n_edges; ++i) {
        add_edge(edges_from[i], edges_to[i], weights[i]);
    }
}

U_Graph::~U_Graph() {
    int i;
    for (i = 0; i < _alloc_ptrs.size(); ++i) {
        delete _alloc_ptrs[i];
    }
}

void U_Graph::add_edge(int from, int to, int weight) {
    bool *remained = new bool;
    _alloc_ptrs.push_back(remained);
    *remained = 0;
    U_Edge forward = {to, weight, remained};
    U_Edge backward = {from, weight, remained};
    adj_list[from].push_back(forward);
    adj_list[to].push_back(backward);
}

void U_Graph::deleted_edges(int& ans_weight,
                            std::vector<int>& ans_edges_from,
                            std::vector<int>& ans_edges_to,
                            std::vector<int>& ans_weights
                            ) {
    int i, j;
    ans_weight = 0;
    for (i = 0; i < _n_vertices; ++i) {
        for (j = 0; j < adj_list[i].size(); ++j) {
            const U_Edge& edge = adj_list[i][j];
            if (!(*(edge.remained))) {
                ans_edges_from.push_back(i);
                ans_edges_to.push_back(edge.to);
                ans_weights.push_back(edge.weight);
                ans_weight += edge.weight;
                *(edge.remained) = 1;
            }
        }
    }
}

// ===================================

// Breadth first search
// Break the cycles in unweighted undirected graph.
void BFS(U_Graph& G) {
    int i, j, u, v;
    std::vector<bool> visited(G.n_vertices(), 0);
    std::queue<int> Q;
    visited[0] = 1;
    Q.push(0);
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (i = 0; i < G.adj_list[u].size(); ++i) {
            v = G.adj_list[u][i].to;
            if (!visited[v]) {
                *(G.adj_list[u][i].remained) = 1;
                visited[v] = 1;
                Q.push(v);
            }
        }
    }
}

// "Maximum" spanning tree
// Break the cycles in weighted undirected graph.
void MST(U_Graph& G) {
    return;
}

// Break the cycles in weighted directed graph.
void XXX(D_Graph& G) {
    return;
}
