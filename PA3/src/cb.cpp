#include <iostream>
#include "cb.h"

// ========================================

void read_file(const char *filename,
               G_type& g_type,
               std::vector<int>& edges_from,
               std::vector<int>& edges_to,
               std::vector<int>& weights,
               int& n_vertices
               ) {
    std::fstream fin(filename);

    char graph_type;
    int n_edges;
    fin >> graph_type >> n_vertices >> n_edges;

    int edge_from, edge_to, weight;
    int i;

    for (i = 0; i < n_edges; ++i) {
        fin >> edge_from >> edge_to >> weight;
        edges_from.push_back(edge_from);
        edges_to.push_back(edge_to);
        weights.push_back(weight);
    }
    fin.close();

    // determine the graph type
    if (graph_type == 'd') {
        g_type = W_D;
        return;
    }
    if (graph_type == 'u') {
        // examine whether the graph is unweighted
        bool is_weighted = false;
        for (i = 0; i < n_edges; ++i) {
            if (weights[i] != 1) {
                is_weighted = true;
                break;
            }
        }
        g_type = is_weighted ? W_U : U_U;
        return;
    }
    std::cout << "Wrong input graph type!" << std::endl;
}

void cycle_break(const G_type g_type,
                 const int n_vertices,
                 const std::vector<int>& edges_from,
                 const std::vector<int>& edges_to,
                 const std::vector<int>& weights,
                 int& ans_weight,
                 std::vector<int>& ans_edges_from,
                 std::vector<int>& ans_edges_to,
                 std::vector<int>& ans_weights
                 ) {
    bool is_directed = 0;
    if (g_type == W_D) {
        is_directed = 1;
    }
    Graph G(n_vertices, is_directed, edges_from, edges_to, weights);

    switch (g_type) {
        case U_U:
            BFS(G);
            break;
        case W_U:
            MST(G);
            break;
        case W_D:
            XXX(G);
            break;
        default:
            std::cout << "Wrong graph type!" << std::endl;
            break;
    }

    deleted_edges(G,
                  edges_from, edges_to, weights,
                  ans_weight, ans_edges_from, ans_edges_to, ans_weights);
}

void deleted_edges(Graph& G,
                   const std::vector<int>& edges_from,
                   const std::vector<int>& edges_to,
                   const std::vector<int>& weights,
                   int& ans_weight,
                   std::vector<int>& ans_edges_from,
                   std::vector<int>& ans_edges_to,
                   std::vector<int>& ans_weights) {
    const int n_edges = G.n_edges();
    int i, u, v, w;
    ans_weight = 0;
    for (i = 0; i < n_edges; ++i) {
        u = edges_from[i];
        v = edges_to[i];
        w = weights[i];
        if (
            // undirected
            (!G.is_directed() &&
                !(G.node_list[v].parent == u || G.node_list[u].parent == v))
            ||
            // directed
            (G.is_directed() &&
                (G.node_list[v].parent != u))
            ) {
            ans_edges_from.push_back(u);
            ans_edges_to.push_back(v);
            ans_weights.push_back(w);
            ans_weight += w;
        }
    }
}

void write_file(const char* filename, const int ans_weight,
                const std::vector<int>& ans_edges_from,
                const std::vector<int>& ans_edges_to,
                const std::vector<int>& ans_weights
                ) {
    std::fstream fout;
    fout.open(filename, std::ios::out);
    const int n = ans_edges_from.size();
    if (n == 0) {
        fout << 0 << std::endl;
    } else {
        int i;
        fout << ans_weight << std::endl;
        for (i = 0; i < n; ++i) {
            fout << ans_edges_from[i] << " " << ans_edges_to[i] << " " <<
                    ans_weights[i] << std::endl;
        }
    }

    fout.close();
}
