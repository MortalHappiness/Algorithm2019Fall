#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <random>

// ==================================

#define V_MAX 100000
#define E_MAX 50000000

// ==================================

void help_message() {
    std::cout << "usage: ./graph_gen <output_path> <u or d> <V> <E>\n";
}

long long edge_to_key(int x, int y) {
    long long a, b;
    a = static_cast<long long>(x);
    b = static_cast<long long>(y);
    return ((a << 32) | b);
}

void gen_sparse_u(int V,
                  int E,
                  std::vector<std::pair<int, int>>& edges,
                  std::default_random_engine& gen,
                  std::uniform_int_distribution<int>& dis_v
                  ) {
    std::unordered_set<long long> edge_keys;
    long long key;
    int i, u, v, temp;

    // generate a connected component
    std::vector<int> idxs;
    for (i = 0; i < V; ++i) {
        idxs.push_back(i);
    }
    std::random_shuffle(idxs.begin(), idxs.end());
    for (i = 0; i < V-1; ++i) {
        u = idxs[i];
        v = idxs[i+1];
        if (u > v) {
            temp = u; u = v; v = temp;
        }
        edge_keys.insert(edge_to_key(u, v));
        edges.push_back(std::make_pair(u, v));
    }
    // generate edges until E
    while (edges.size() != E) {
        u = dis_v(gen);
        do {
            v = dis_v(gen);
        } while (v == u);
        if (u > v) {
            temp = u; u = v; v = temp;
        }
        key = edge_to_key(u, v);
        if (edge_keys.find(key) == edge_keys.end()) {
            edge_keys.insert(key);
            edges.push_back(std::make_pair(u, v));
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        help_message();
        return 0;
    }
    char *output_path = argv[1];
    char graph_type = argv[2][0];
    int V = atoi(argv[3]);
    int E = atoi(argv[4]);

    srand(time(0));
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dis_w(-100, 100);
    std::uniform_int_distribution<int> dis_v(0, V - 1);

    if (graph_type != 'u' && graph_type != 'd') {
        std::cout << "Only u or d is accepted!" << std::endl;
        return 0;
    }
    if (V > V_MAX) {
        std::cout << "Too many vertices!" << std::endl;
        return 0;
    }
    if (E < V-1) {
        std::cout << "Too less edges!" << std::endl;
        return 0;
    }
    if (E > E_MAX) {
        std::cout << "Too many edges!" << std::endl;
        return 0;
    }

    std::vector<std::pair<int, int>> edges;

    switch (graph_type) {
        case 'u':
            if (static_cast<long long>(E) >
                static_cast<long long>(V) * static_cast<long long>(V-1) / 2) {
                std::cout << "Too many edges!" << std::endl;
            }
            gen_sparse_u(V, E, edges, gen, dis_v);
            break;
        case 'd':
            std::cout << "Currently not supported!" << std::endl;
            return 0;
            break;
    }

    // output
    std::fstream fout;
    fout.open(argv[1], std::ios::out);
    fout << graph_type << std::endl;
    fout << V << std::endl;
    fout << E << std::endl;
    int i;
    for (i = 0; i < E; ++i) {
        fout << edges[i].first << " "
             << edges[i].second << " "
             << dis_w(gen) << "\n";
    }
    fout << 0;
    fout.close();
}
