#ifndef _IO_H
#define _IO_H

#include <vector>
#include <fstream>

// ========================================

// parse out an integer from the buffer (until a space or newline)
int parse_int(char*&);

// read the file and return whether the graph is directed graph
bool read_file(const char*,
               std::vector<int>&,
               std::vector<int>&,
               std::vector<int>&,
               int&);

// write integer into a char buffer, return the written length
int int_to_buf(char*&, int);

// write the output file
void write_file(const char*,
                const long long,
                const std::vector<int>&,
                const std::vector<int>&,
                const std::vector<int>&);

// ========================================

#endif
