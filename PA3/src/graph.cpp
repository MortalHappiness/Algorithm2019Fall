#include <iostream>
#include "graph.h"

// ===================================

// Breadth first search
// Break the cycles in unweighted undirected graph.
void BFS(const int n_vertices,
         std::vector<int>& edges_from,
         std::vector<int>& edges_to,
         int& ans_weight,
         std::vector<int>& ans_edges_from,
         std::vector<int>& ans_edges_to,
         std::vector<int>& ans_weights
         ) {

    const int n_edges = edges_from.size();
    std::vector<std::vector<int>> adj_list(n_vertices, std::vector<int>(0));
    // use matrix to record edges not to be deleted
    std::vector<std::vector<bool>>
                edges_remained(n_vertices, std::vector<bool>(n_vertices, 0));
    int i, j, u, v;

    // construct the adjacency list
    for (i = 0; i < n_edges; ++i) {
        u = edges_from[i];
        v = edges_to[i];
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    // run BFS
    std::vector<bool> visited(n_vertices, 0);
    std::queue<int> Q;
    visited[0] = 1;
    Q.push(0);
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (i = 0; i < adj_list[u].size(); ++i) {
            v = adj_list[u][i];
            if (!visited[v]) {
                edges_remained[u][v] = 1;
                edges_remained[v][u] = 1;
                visited[v] = 1;
                Q.push(v);
            }
        }
    }

    // Decide what edges should be deleted
    for (i = 0; i < n_vertices; ++i) {
        for (j = 0; j < adj_list[i].size(); ++j) {
            u = adj_list[i][j];
            if (!edges_remained[i][u]) {
                ans_edges_from.push_back(i);
                ans_edges_to.push_back(u);
                ans_weights.push_back(1);
                edges_remained[u][i] = 1;
            }
        }
    }
    ans_weight = ans_edges_from.size();
}

// "Maximum" spanning tree
// Break the cycles in weighted undirected graph.
void MST(const int n_vertices,
         std::vector<int>& edges_from,
         std::vector<int>& edges_to,
         std::vector<int>& weights,
         int& ans_weight,
         std::vector<int>& ans_edges_from,
         std::vector<int>& ans_edges_to,
         std::vector<int>& ans_weights
         ) {
    return;
}

// Break the cycles in weighted directed graph.
void XXX(const int n_vertices,
         std::vector<int>& edges_from,
         std::vector<int>& edges_to,
         std::vector<int>& weights,
         int& ans_weight,
         std::vector<int>& ans_edges_from,
         std::vector<int>& ans_edges_to,
         std::vector<int>& ans_weights
         ) {
    return;
}
