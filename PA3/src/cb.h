#ifndef _CB_H
#define _CB_H

#include <vector>
#include <fstream>
#include "set.h"

// ========================================

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

// ========================================

// read the file and return whether the graph is directed graph
bool read_file(const char*,
               std::vector<int>&,
               std::vector<int>&,
               std::vector<int>&,
               int&);

// cycle breaking
void cycle_break(const bool,
                 const int,
                 const std::vector<int>&,
                 const std::vector<int>&,
                 const std::vector<int>&,
                 long long&,
                 std::vector<int>&,
                 std::vector<int>&,
                 std::vector<int>&);

// Kruskal's "Maximum" spanning tree algorithm
void MST(const int,
         std::vector<Edge>&,
         long long&,
         std::vector<int>&,
         std::vector<int>&,
         std::vector<int>&);

// counting sort(non-decreasing order)
void counting_sort(const std::vector<Edge>&,
                   std::vector<Edge>&,
                   int);

// write the output file
void write_file(const char*,
                const long long,
                const std::vector<int>&,
                const std::vector<int>&,
                const std::vector<int>&);

// ========================================

#endif
