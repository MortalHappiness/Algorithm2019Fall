#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "io.h"

// ========================================

int parse_int(char*& buffer) {
    int num, i;
    bool is_negative = 0;
    if (*buffer == '-') {
        ++buffer;
        is_negative = 1;
    }
    num = 0;
    while (1) {
        if (*buffer == ' ' || *buffer == '\n') {
            break;
        }
        num  = num * 10 + *buffer - '0';
        ++buffer;
    }
    ++buffer;
    if (is_negative) { num = -num; }
    return num;
}

bool read_file(const char *filename,
               std::vector<int>& edges_from,
               std::vector<int>& edges_to,
               std::vector<int>& weights,
               int& n_vertices
               ) {
    char graph_type;
    int n_edges;

    // read the file into a buffer
    FILE *pFile;
    size_t filesize, readsize;
    char *buffer;

    pFile = fopen(filename, "rb");
    if (pFile == NULL) { fputs("File error", stderr); }

    fseek(pFile, 0, SEEK_END);
    filesize = ftell(pFile);
    rewind(pFile);

    buffer = (char*) malloc(sizeof(char) * filesize);
    if (buffer == NULL) { fputs("Memory error", stderr); }

    readsize = fread(buffer, 1, filesize, pFile);
    if (readsize != filesize) { fputs("Reading error", stderr); }

    fclose(pFile);

    // parse the buffer
    char *cur = buffer;
    graph_type = *(cur);
    cur += 2;

    n_vertices = parse_int(cur);
    n_edges = parse_int(cur);

    int i, num;

    for (i = 0; i < n_edges; ++i) {
        num = parse_int(cur);
        edges_from.push_back(num);
        num = parse_int(cur);
        edges_to.push_back(num);
        num = parse_int(cur);
        weights.push_back(num);
    }

    free(buffer);

    // determine the graph type
    if (graph_type == 'd') {
        return 1;
    }
    if (graph_type == 'u') {
        return 0;
    }
    std::cout << "Wrong input graph type!" << std::endl;
}

int int_to_buf(char*& buffer, int n) {
    if (n == 0) {
        *buffer = '0';
        ++buffer;
        return 1;
    }
    int length = 0;
    if (n < 0) {
        *buffer = '-';
        ++buffer;
        ++length;
        n = -n;
    }
    char *num_head = buffer;
    while (n != 0) {
        *buffer = (n % 10) + '0';
        ++length;
        ++buffer;
        n /= 10;
    }
    // reverse
    int start, end, temp;
    start = 0;
    end = buffer - num_head - 1;
    while (start < end) {
        temp = *(num_head + start);
        *(num_head + start) = *(num_head + end);
        *(num_head + end) = temp;
        ++start;
        --end;
    }

    return length;
}

void write_file(const char* filename,
                const long long ans_weight,
                const std::vector<int>& ans_edges_from,
                const std::vector<int>& ans_edges_to,
                const std::vector<int>& ans_weights
                ) {
    const int n = ans_edges_from.size();
    FILE *pFile;
    pFile = fopen(filename, "wb");

    if (n == 0) {
        putc('0', pFile);
    } else {
        int i;
        fprintf(pFile, "%lld\n", ans_weight);

        // allocate buffer
        char *buffer;
        // 19 = 6 + 1 + 6 + 1 + 4 + 1
        //     6: max vertex bit(100000)
        //     4: max weight bit(-100)
        //     1: space and newline
        const size_t maxbufsize = 19 * n;
        buffer = (char*) malloc(sizeof(char) * maxbufsize);
        if (buffer == NULL) { fputs("Memory error", stderr); }

        // write into buffer
        char *cur = buffer;
        size_t length = 0;
        for (i = 0; i < n; ++i) {
            length += int_to_buf(cur, ans_edges_from[i]);
            *cur = ' '; ++cur; ++length;
            length += int_to_buf(cur, ans_edges_to[i]);
            *cur = ' '; ++cur; ++length;
            length += int_to_buf(cur, ans_weights[i]);
            *cur = '\n'; ++cur; ++length;
        }
        fwrite(buffer, sizeof(char), sizeof(char) * length, pFile);
        free(buffer);
    }

    fclose(pFile);
}
