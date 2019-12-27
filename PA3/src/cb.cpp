#include <iostream>
#include <limits.h>
#include "cb.h"

// ========================================

void cycle_break(const bool is_directed,
                 const int n_vertices,
                 const std::vector<int>& edges_from,
                 const std::vector<int>& edges_to,
                 const std::vector<int>& weights,
                 long long& ans_weight,
                 std::vector<int>& ans_edges_from,
                 std::vector<int>& ans_edges_to,
                 std::vector<int>& ans_weights
                 ) {
    const int n_edges = edges_from.size();
    int i;
    if (!is_directed) {
        std::vector<Edge> edge_list;
        for (i = 0; i < n_edges; ++i) {
            edge_list.push_back(Edge{edges_from[i], edges_to[i], weights[i]});
        }
        MST(n_vertices, edge_list,
            ans_weight, ans_edges_from, ans_edges_to, ans_weights);
    } else {
        // directed graph cycle breaking
        int from, to, weight;
        ans_weight = 0;
        // key = out_weight - in_weight
        std::vector<int> node_keys(n_vertices, 0);
        // linked list
        std::list<Edge> edge_list;
        for (i = 0; i < n_edges; ++i) {
            from = edges_from[i];
            to = edges_to[i];
            weight = weights[i];
            edge_list.push_back(Edge{from, to, weight});
            node_keys[from] += weight;
            node_keys[to] -= weight;
        }

        int idx, val, j;
        std::list<Edge>::iterator iter;
        for (i = 0; i < n_vertices; ++i) {
            // extract maximum key
            idx = 0;
            val = INT_MIN;
            for (j = 0; j < n_vertices; ++j) {
                if (node_keys[j] > val) {
                    idx = j;
                    val = node_keys[j];
                }
            }
            // set the key of the maximum key to INT_MIN
            node_keys[idx] = INT_MIN;
            // traverse the edge list to update key
            iter = edge_list.begin();
            while (iter != edge_list.end()) {
                from = (*iter).from;
                to = (*iter).to;
                weight = (*iter).weight;
                if (from == idx) {
                    node_keys[to] += weight;
                    iter = edge_list.erase(iter);
                } else if (to == idx) {
                    ans_edges_from.push_back(from);
                    ans_edges_to.push_back(to);
                    ans_weights.push_back(weight);
                    ans_weight += weight;
                    node_keys[from] -= weight;
                    iter = edge_list.erase(iter);
                } else {
                    ++iter;
                }
            }
        }
    }
}

void MST(const int n_vertices,
         std::vector<Edge>& edge_list,
         long long& ans_weight,
         std::vector<int>& ans_edges_from,
         std::vector<int>& ans_edges_to,
         std::vector<int>& ans_weights
         ) {
    ans_weight = 0LL;
    int i, u, v, w;
    const int n_edges = edge_list.size();

    // -100 <= weight <= 100, nomalize to [0, 200]
    for (i = 0; i < n_edges; ++i) {
        edge_list[i].weight += 100;
    }

    // sort the edges into "non-decreasing" order
    std::vector<Edge> sorted_edge_list;
    counting_sort(edge_list, sorted_edge_list, 200);

    // for edges in "non-increasing" order, do Union-Find
    Set set(n_vertices);
    for (i = n_edges - 1; i >= 0; --i) {
        u = sorted_edge_list[i].from;
        v = sorted_edge_list[i].to;
        if (set.Find(u) != set.Find(v)) {
            set.Union(u, v);
        } else {
            // normalize the weight back to [-100, 100]
            w = sorted_edge_list[i].weight - 100;
            ans_weight += static_cast<long long>(w);
            ans_edges_from.push_back(u);
            ans_edges_to.push_back(v);
            ans_weights.push_back(w);
        }
    }
}

void counting_sort(const std::vector<Edge>& input,
                   std::vector<Edge>& output,
                   int k) {
    std::vector<int> aux(k + 1, 0);
    const int n = input.size();
    int i, w;
    for (i = 0; i < n; ++i) {
        w = input[i].weight;
        ++aux[w];
    }

    for (i = 1; i <= k; ++i) {
        aux[i] += aux[i-1];
    }

    output.resize(n);
    for (i = n-1; i >= 0; --i) {
        w = input[i].weight;
        output[aux[w] - 1] = input[i];
        --aux[w];
    }
}
