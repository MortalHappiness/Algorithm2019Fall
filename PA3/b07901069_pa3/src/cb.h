#ifndef _CB_H
#define _CB_H

#include <vector>
#include <list>
#include "set.h"

// ========================================

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

// ========================================

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

// ========================================

#endif
