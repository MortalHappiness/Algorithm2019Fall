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
    std::cout << "usage: ./graph_gen <output_path> <u or d> V E" << std::endl;
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

    if (graph_type != 'u' && graph_type != 'd') {
        std::cout << "Only u or d is accepted!" << std::endl;
        return 0;
    }
    if (V > V_MAX) {
        std::cout << "Too many vertices!" << std::endl;
        return 0;
    }
    if (E > E_MAX) {
        std::cout << "Too many edges!" << std::endl;
        return 0;
    }

    std::fstream fout;
    fout.open(argv[1], std::ios::out);
    fout << graph_type << std::endl;
    fout << V << std::endl;
    fout << E << std::endl;

    std::vector<std::pair<int, int>> edges;
    std::unordered_set<unsigned long long> used;
    unsigned long long key;
    int i, j, n_edges, temp;
    // bool dense = (10 * E > V * V);
    bool dense = 0;

    srand(time(0));

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dis_w(-100, 100);
    std::uniform_int_distribution<int> dis_v(0, V - 1);

    switch (graph_type) {
        case 'u':
            n_edges = V * (V - 1) / 2;
            if (E > n_edges) {
                std::cout << "Too many edges!" << std::endl;
                break;
            }
            if (dense) {
                for (i = 0; i < V; ++i) {
                    for (j = i + 1; j < V; ++j) {
                        edges.push_back(std::make_pair(i, j));
                    }
                }
                std::random_shuffle(edges.begin(), edges.end());
            } else {
                while (edges.size() != E) {
                    i = dis_v(gen);
                    while ((j = dis_v(gen)) == i) {
                        j = dis_v(gen);
                    }
                    if (i > j) {
                        temp = i; i = j; j = temp;
                    }
                    key = (unsigned long long)V * (unsigned long long)i +
                          (unsigned long long)j;
                    if (used.find(key) == used.end()) {
                        used.insert(key);
                        edges.push_back(std::make_pair(i, j));
                    }
                }
            }
            break;
        case 'd':
            n_edges = V * (V - 1);
            if (E > n_edges) {
                std::cout << "Too many edges!" << std::endl;
                break;
            }
            if (dense) {
                for (i = 0; i < V; ++i) {
                    for (j = 0; j < V; ++j) {
                        if (i != j) {
                            edges.push_back(std::make_pair(i, j));
                        }
                    }
                }
                std::random_shuffle(edges.begin(), edges.end());
            } else {
                while (edges.size() != E) {
                    i = dis_v(gen);
                    while ((j = dis_v(gen)) == i) {
                        j = dis_v(gen);
                    }
                    key = (unsigned long long)V * (unsigned long long)i +
                          (unsigned long long)j;
                    if (used.find(key) == used.end()) {
                        used.insert(key);
                        edges.push_back(std::make_pair(i, j));
                    }
                }
            }
            break;
    }

    for (i = 0; i < E; ++i) {
        fout << edges[i].first << " "
             << edges[i].second << " "
             << dis_w(gen) << std::endl;
    }
    fout << 0;
    fout.close();
}
