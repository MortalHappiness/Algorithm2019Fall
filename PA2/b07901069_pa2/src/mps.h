#ifndef _MPS_H
#define _MPS_H

#include <vector>
#include <fstream>

// ========================================

// typedef std::vector<int> int_array;
// typedef std::vector<int_array> int_matrix;
typedef std::vector<unsigned short> u_short_array;
typedef std::vector<u_short_array> u_short_matrix;
typedef std::vector<bool> bool_array;
typedef std::vector<bool_array> bool_matrix;

void read_file(char*, u_short_array&);
void write_file(char*, u_short_array&, u_short_array&);
unsigned short top_down_mps(u_short_array&, u_short_matrix&, bool_matrix&, int, int);
void compute_mps(u_short_array&, u_short_array&, u_short_array&);
void get_ans(u_short_array&, u_short_array&, u_short_array&, bool_matrix&, int, int);

// ========================================

#endif
