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

    if (g_type == U_U) {
        U_Graph G(n_vertices, edges_from, edges_to, weights);
        BFS(G);
        G.deleted_edges(ans_weight,
                        ans_edges_from,
                        ans_edges_to,
                        ans_weights);
    } else if (g_type == W_U) {
        U_Graph G(n_vertices, edges_from, edges_to, weights);
        MST(G);
        G.deleted_edges(ans_weight,
                        ans_edges_from,
                        ans_edges_to,
                        ans_weights);
    } else if (g_type == W_D) {
        // D_Graph G(n_vertices, edges_from, edges_to, weights);
        // XXX(G);
        // G.deleted_edges(ans_weight,
        //                 ans_edges_from,
        //                 ans_edges_to,
        //                 ans_weights);
    } else {
        std::cout << "Wrong graph type!" << std::endl;
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
