#include <iostream>
#include "graph.h"

// ===================================
// graph implementation

Graph::Graph(const int n_vertices,
             const bool is_directed,
             const std::vector<int>& edges_from,
             const std::vector<int>& edges_to,
             const std::vector<int>& weights) {
    const int n_edges = edges_from.size();
    _n_vertices = n_vertices;
    _n_edges = n_edges;
    _is_directed = is_directed;
    adj_list.resize(n_vertices);
    node_list.resize(n_vertices);
    int i;
    for (i = 0; i < n_vertices; ++i) {
        node_list[i] = Node{0, NIL};
    }
    for (i = 0; i < n_edges; ++i) {
        add_edge(edges_from[i], edges_to[i], weights[i]);
    }
}

void Graph::add_edge(int from, int to, int weight) {
    adj_list[from].push_back(Edge{to, weight});
    if (!_is_directed) {
        adj_list[to].push_back(Edge{from, weight});
    }
}

// ===================================

// Breadth first search
// Break the cycles in unweighted undirected graph.
void BFS(Graph& G) {
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
                G.node_list[v].parent = u;
                visited[v] = 1;
                Q.push(v);
            }
        }
    }
}

// "Maximum" spanning tree
// Break the cycles in weighted undirected graph.
void MST(Graph& G) {
    int i, u, v, w;
    for (i = 0; i < G.n_vertices(); ++i) {
        G.node_list[i].key = -INF;
    }
    G.node_list[0].key = 0;
    MaxHeap<Node> heap(G.node_list);
    while (!heap.is_empty()) {
        u = heap.extract_maximum();
        for (i = 0; i < G.adj_list[u].size(); ++i) {
            v = G.adj_list[u][i].to;
            w = G.adj_list[u][i].weight;
            if (heap.contains(v) && w > G.node_list[v].key) {
                G.node_list[v].parent = u;
                heap.increase_key(v, w);
            }
        }
    }
}

// Break the cycles in weighted directed graph.
void XXX(Graph& G) {
    return;
}
