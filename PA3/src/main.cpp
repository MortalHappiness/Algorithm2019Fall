#include <iostream>
#include "cb.h"
#include "io.h"

// ======================================

void help_message() {
    std::cout << "usage: ./cb <input_file> <output_file>" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        help_message();
        return 0;
    }

    // Read file
    int n_vertices;
    std::vector<int> edges_from, edges_to, weights,
                     ans_edges_from, ans_edges_to, ans_weights;
    bool is_directed = read_file(argv[1],
                            edges_from, edges_to, weights, n_vertices);

    // cycle breaking
    long long ans_weight;
    cycle_break(is_directed, n_vertices, edges_from, edges_to, weights,
                ans_weight, ans_edges_from, ans_edges_to, ans_weights);

    // Write file
    write_file(argv[2], ans_weight,
               ans_edges_from, ans_edges_to, ans_weights);
}
