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

// heuristic function pointer for directed graph
typedef void (*heu_fun_ptr)(const int,
                            const std::vector<int>&,
                            const std::vector<int>&,
                            const std::vector<int>&,
                            std::list<Edge>&);

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

long long sum_weights(std::list<Edge>&);

void heuristic_1(const int,
                 const std::vector<int>&,
                 const std::vector<int>&,
                 const std::vector<int>&,
                 std::list<Edge>&
                 );

void heuristic_2(const int,
                 const std::vector<int>&,
                 const std::vector<int>&,
                 const std::vector<int>&,
                 std::list<Edge>&
                 );

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
