#ifndef _CB_H
#define _CB_H

#include <vector>
#include <fstream>
#include "graph.h"

// ========================================

// graph type
enum G_type {
    U_U,   // unweighted undirected graph
    W_U,   // weighted undirected graph
    W_D    // weighted directed graph
};

// ========================================

void read_file(const char*,
               G_type&,
               std::vector<int>&,
               std::vector<int>&,
               std::vector<int>&,
               int&);
void cycle_break(const G_type,
                 const int,
                 const std::vector<int>&,
                 const std::vector<int>&,
                 const std::vector<int>&,
                 int&,
                 std::vector<int>&,
                 std::vector<int>&,
                 std::vector<int>&);
void write_file(const char*,
                const int,
                const std::vector<int>&,
                const std::vector<int>&,
                const std::vector<int>&);

// ========================================

#endif
