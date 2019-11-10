#ifndef _MPS_H
#define _MPS_H

#include <vector>
#include <utility>
#include <fstream>

// ========================================

typedef std::vector<int> int_array;
typedef std::vector<int_array> int_matrix;
typedef std::pair<int, int> Chord;
typedef std::vector<Chord> chord_set;

void read_file(char*, int_array&);
void write_file(char*, chord_set&);
void compute_mps(int_array&, chord_set&);
void get_ans(int_array&, chord_set&, int_matrix&, int, int);

// ========================================

#endif
