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
        d_cb(n_vertices, edges_from, edges_to, weights,
             ans_weight, ans_edges_from, ans_edges_to, ans_weights);
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

void d_cb(const int n_vertices,
          const std::vector<int>& edges_from,
          const std::vector<int>& edges_to,
          const std::vector<int>& weights,
          long long& ans_weight,
          std::vector<int>& ans_edges_from,
          std::vector<int>& ans_edges_to,
          std::vector<int>& ans_weights
         ) {
    int i;
    std::vector<heu_fun_ptr> heuristics = {&heuristic_1, &heuristic_2};
    i = heuristics.size();
    std::vector<std::list<Edge>> del_edges_vec(i);
    std::list<Edge>::iterator iter;

    // run different heuristics
    for (i = 0; i < heuristics.size(); ++i) {
        (*(heuristics[i]))(n_vertices,
                           edges_from, edges_to, weights,
                           del_edges_vec[i]);
    }

    // choose the heuristic that generate minimum weight
    int idx = 0, cur_min = INT_MAX, sum;
    for (i = 0; i < heuristics.size(); ++i) {
        sum = sum_weights(del_edges_vec[i]);
        if (sum < cur_min) {
            idx = i;
            cur_min = sum;
        }
    }
    std::list<Edge> del_edges = del_edges_vec[idx];

    // output deleted edges to answer
    ans_weight = 0;
    for (iter = del_edges.begin(); iter != del_edges.end(); ++iter) {
        ans_edges_from.push_back((*iter).from);
        ans_edges_to.push_back((*iter).to);
        ans_weights.push_back((*iter).weight);
        ans_weight += (*iter).weight;
    }
}

long long sum_weights(std::list<Edge>& edge_list) {
    long long sum = 0LL;
    std::list<Edge>::iterator iter;
    for (iter = edge_list.begin(); iter != edge_list.end(); ++iter) {
        sum += static_cast<long long>((*iter).weight);
    }
    return sum;
}

void heuristic_1(const int n_vertices,
                 const std::vector<int>& edges_from,
                 const std::vector<int>& edges_to,
                 const std::vector<int>& weights,
                 std::list<Edge>& del_edges
                 ) {
    const int n_edges = edges_from.size();
    int from, to, weight, i, j, idx, val;

    // key = out_weight - in_weight
    std::vector<int> node_keys(n_vertices, 0);
    std::list<Edge> edge_list;
    std::vector<int> in_degree(n_vertices, 0);
    std::vector<int> out_degree(n_vertices, 0);

    // initialization
    for (i = 0; i < n_edges; ++i) {
        from = edges_from[i];
        to = edges_to[i];
        weight = weights[i];
        edge_list.push_back(Edge{from, to, weight});
        node_keys[from] += weight;
        node_keys[to] -= weight;
        ++out_degree[from];
        ++in_degree[to];
    }

    std::list<Edge>::iterator iter;
    std::vector<Edge> in_edges, out_edges;
    Set set(n_vertices); // use disjoint set to check for connectivity
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
        delete_edges(idx, edge_list, node_keys, in_edges, out_edges,
                     in_degree, out_degree);
        categorize_edges(out_edges, in_edges, set, del_edges);
    }

    // if disconnected, add edges with largest weight back
    std::list<Edge>::iterator max_iter;
    bool is_connected;
    while (1) {
        is_connected = 1;
        val = INT_MIN;
        for (iter = del_edges.begin(); iter != del_edges.end(); ++iter) {
            from = (*iter).from;
            to = (*iter).to;
            weight = (*iter).weight;
            if (set.Find(from) == set.Find(to)) {
                continue;
            }
            is_connected = 0;
            if (weight > val) {
                val = weight;
                max_iter = iter;
            }
        }
        if (is_connected) {
            break;
        }
        set.Union((*max_iter).from, (*max_iter).to);
        del_edges.erase(max_iter);
    }
}

void heuristic_2(const int n_vertices,
                 const std::vector<int>& edges_from,
                 const std::vector<int>& edges_to,
                 const std::vector<int>& weights,
                 std::list<Edge>& del_edges
                 ) {
    const int n_edges = edges_from.size();
    int from, to, weight, i, j, idx, val;

    // key = out_weight - in_weight
    std::vector<int> node_keys(n_vertices, 0);
    std::list<Edge> edge_list;
    std::vector<int> in_degree(n_vertices, 0);
    std::vector<int> out_degree(n_vertices, 0);

    // initialization
    for (i = 0; i < n_edges; ++i) {
        from = edges_from[i];
        to = edges_to[i];
        weight = weights[i];
        edge_list.push_back(Edge{from, to, weight});
        node_keys[from] += weight;
        node_keys[to] -= weight;
        ++out_degree[from];
        ++in_degree[to];
    }

    std::list<Edge>::iterator iter;
    std::vector<Edge> in_edges, out_edges;
    Set set(n_vertices); // use disjoint set to check for connectivity
    bool should_cont;
    for (i = 0; i < n_vertices; ++i) {
        should_cont = 0;
        // check for source
        for (j = 0; j < n_vertices; ++j) {
            if (in_degree[j] == 0) {
                delete_edges(j, edge_list, node_keys, in_edges, out_edges,
                             in_degree, out_degree);
                categorize_edges(out_edges, in_edges, set, del_edges);
                should_cont = 1;
                break;
            }
        }
        if (should_cont) {continue;}
        // check for sink
        for (j = 0; j < n_vertices; ++j) {
            if (out_degree[j] == 0) {
                delete_edges(j, edge_list, node_keys, in_edges, out_edges,
                             in_degree, out_degree);
                categorize_edges(in_edges, out_edges, set, del_edges);
                should_cont = 1;
                break;
            }
        }
        if (should_cont) {continue;}
        // extract maximum key
        idx = 0;
        val = INT_MIN;
        for (j = 0; j < n_vertices; ++j) {
            if (node_keys[j] > val) {
                idx = j;
                val = node_keys[j];
            }
        }
        delete_edges(idx, edge_list, node_keys, in_edges, out_edges,
                     in_degree, out_degree);
        categorize_edges(out_edges, in_edges, set, del_edges);
    }

    // if disconnected, add edges with largest weight back
    // std::list<Edge>::iterator max_iter;
    // bool is_connected;
    // while (1) {
    //     is_connected = 1;
    //     val = INT_MIN;
    //     for (iter = del_edges.begin(); iter != del_edges.end(); ++iter) {
    //         from = (*iter).from;
    //         to = (*iter).to;
    //         weight = (*iter).weight;
    //         if (set.Find(from) == set.Find(to)) {
    //             continue;
    //         }
    //         is_connected = 0;
    //         if (weight > val) {
    //             val = weight;
    //             max_iter = iter;
    //         }
    //     }
    //     if (is_connected) {
    //         break;
    //     }
    //     set.Union((*max_iter).from, (*max_iter).to);
    //     del_edges.erase(max_iter);
    // }
}

void delete_edges(int idx,
                  std::list<Edge>& edge_list,
                  std::vector<int>& node_keys,
                  std::vector<Edge>& in_edges,
                  std::vector<Edge>& out_edges,
                  std::vector<int>& in_degree,
                  std::vector<int>& out_degree
                  ) {
    int from, to, weight;
    in_edges.clear();
    out_edges.clear();
    std::list<Edge>::iterator iter;
    iter = edge_list.begin();
    node_keys[idx] = INT_MIN;
    in_degree[idx] = -1;
    out_degree[idx] = -1;
    while (iter != edge_list.end()) {
        from = (*iter).from;
        to = (*iter).to;
        weight = (*iter).weight;
        if (from == idx) {
            node_keys[to] += weight;
            --in_degree[to];
            out_edges.push_back(*iter);
            iter = edge_list.erase(iter);
        } else if (to == idx) {
            node_keys[from] -= weight;
            --out_degree[from];
            in_edges.push_back(*iter);
            iter = edge_list.erase(iter);
        } else {
            ++iter;
        }
    }
}

void categorize_edges(std::vector<Edge>& left,
                      std::vector<Edge>& deleted,
                      Set& set,
                      std::list<Edge>& del_edges
                      ) {
    int i, from, to;
    for (i = 0; i < left.size(); ++i) {
        from = left[i].from;
        to = left[i].to;
        if (set.Find(from) != set.Find(to)) {
            set.Union(from, to);
        }
    }
    for (i = 0; i < deleted.size(); ++i) {
        del_edges.push_back(deleted[i]);
    }
}
