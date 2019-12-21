#include <iostream>
#include "cb.h"
#include "../lib/tm_usage.h"
#include <time.h>

// ======================================

void help_message() {
    std::cout << "usage: ./cb <input_file> <output_file>" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        help_message();
        return 0;
    }

    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    time_t t1, t2, t3, t4;
    t1 = clock();

    // Read file
    int n_vertices;
    std::vector<int> edges_from, edges_to, weights,
                     ans_edges_from, ans_edges_to, ans_weights;
    bool is_directed = read_file(argv[1],
                            edges_from, edges_to, weights, n_vertices);
    t2 = clock();
    std::cout << ((double) (t2 - t1)) / CLOCKS_PER_SEC << std::endl;

    // cycle breaking
    long long ans_weight;
    cycle_break(is_directed, n_vertices, edges_from, edges_to, weights,
                ans_weight, ans_edges_from, ans_edges_to, ans_weights);

    t3 = clock();
    std::cout << ((double) (t3 - t2)) / CLOCKS_PER_SEC << std::endl;
    // // Write file
    write_file(argv[2], ans_weight,
               ans_edges_from, ans_edges_to, ans_weights);
    t4 = clock();
    std::cout << ((double) (t4 - t3)) / CLOCKS_PER_SEC << std::endl;

    tmusg.getPeriodUsage(stat);
    std::cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << std::endl;
    std::cout <<"memory: " << stat.vmPeak << "KB" << std::endl; // print peak memory
}
