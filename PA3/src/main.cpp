#include <iostream>
#include "cb.h"

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
    G_type g_type;
    int n_vertices;
    std::vector<int> edges_from, edges_to, weights,
                     ans_edges_from, ans_edges_to, ans_weights;
    read_file(argv[1], g_type, edges_from, edges_to, weights, n_vertices);

    // cycle breaking
    int ans_weight;
    cycle_break(g_type, n_vertices, edges_from, edges_to, weights,
                ans_weight, ans_edges_from, ans_edges_to, ans_weights);

    // Write file
    write_file(argv[2], ans_weight,
               ans_edges_from, ans_edges_to, ans_weights);
}
