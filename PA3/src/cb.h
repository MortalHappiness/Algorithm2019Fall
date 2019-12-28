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

// directed graph cycle breaking
void d_cb(const int,
          const std::vector<int>&,
          const std::vector<int>&,
          const std::vector<int>&,
          long long&,
          std::vector<int>&,
          std::vector<int>&,
          std::vector<int>&);

// delete edges incident from or to the specified node
// update the node keys accordingly
// write in edges and out edges into the vectors
void delete_edges(int,
                  std::list<Edge>&,
                  std::vector<int>&,
                  std::vector<Edge>&,
                  std::vector<Edge>&,
                  std::vector<int>&,
                  std::vector<int>&
                  );

void categorize_edges(std::vector<Edge>&,
                      std::vector<Edge>&,
                      Set&,
                      std::list<Edge>&
                      );

// ========================================

#endif
