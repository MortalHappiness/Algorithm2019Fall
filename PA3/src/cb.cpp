#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "cb.h"

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

void cycle_break(const bool is_directed,
                 const int n_vertices,
                 const std::vector<int>& edges_from,
                 const std::vector<int>& edges_to,
                 const std::vector<int>& weights,
                 long long& ans_weight,
                 std::vector<int>& ans_edges_from,
                 std::vector<int>& ans_edges_to,
                 std::vector<int>& ans_weights
                 ) {
    const int n_edges = edges_from.size();
    int i;
    if (!is_directed) {
        std::vector<Edge> edge_list;
        for (i = 0; i < n_edges; ++i) {
            edge_list.push_back(Edge{edges_from[i], edges_to[i], weights[i]});
        }
        MST(n_vertices, edge_list,
            ans_weight, ans_edges_from, ans_edges_to, ans_weights);
    } else {

    }
}

void MST(const int n_vertices,
         std::vector<Edge>& edge_list,
         long long& ans_weight,
         std::vector<int>& ans_edges_from,
         std::vector<int>& ans_edges_to,
         std::vector<int>& ans_weights
         ) {
    ans_weight = 0LL;
    int i, u, v, w;
    const int n_edges = edge_list.size();

    // -100 <= weight <= 100, nomalize to [0, 200]
    for (i = 0; i < n_edges; ++i) {
        edge_list[i].weight += 100;
    }

    // sort the edges into "non-decreasing" order
    std::vector<Edge> sorted_edge_list;
    counting_sort(edge_list, sorted_edge_list, 200);

    // for edges in "non-increasing" order, do Union-Find
    Set set(n_vertices);
    for (i = n_edges - 1; i >= 0; --i) {
        u = sorted_edge_list[i].from;
        v = sorted_edge_list[i].to;
        if (set.Find(u) != set.Find(v)) {
            set.Union(u, v);
        } else {
            // normalize the weight back to [-100, 100]
            w = sorted_edge_list[i].weight - 100;
            ans_weight += static_cast<long long>(w);
            ans_edges_from.push_back(u);
            ans_edges_to.push_back(v);
            ans_weights.push_back(w);
        }
    }
}

void counting_sort(const std::vector<Edge>& input,
                   std::vector<Edge>& output,
                   int k) {
    std::vector<int> aux(k + 1, 0);
    const int n = input.size();
    int i, w;
    for (i = 0; i < n; ++i) {
        w = input[i].weight;
        ++aux[w];
    }

    for (i = 1; i <= k; ++i) {
        aux[i] += aux[i-1];
    }

    output.resize(n);
    for (i = n-1; i >= 0; --i) {
        w = input[i].weight;
        output[aux[w] - 1] = input[i];
        --aux[w];
    }
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
