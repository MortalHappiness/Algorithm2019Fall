#include "mps.h"
#include <iostream>

// =====================================

void read_file(char *filename, u_short_array& chords) {
    std::fstream fin(filename);
    int i, n_vertices, n_chords, a, b;
    fin >> n_vertices;
    n_chords = n_vertices / 2;
    chords.assign(n_vertices, 0);
    for (i = 0; i < n_chords; ++i) {
        fin >> a >> b;
        chords[a] = b;
        chords[b] = a;
    }
    fin.close();
}

void write_file(char *filename,
                u_short_array& ans_first,
                u_short_array& ans_second
                ) {
    std::fstream fout;
    fout.open(filename, std::ios::out);
    const int n = ans_first.size();
    fout << n << std::endl;
    int i;
    for (i = 0; i < n; ++i) {
        fout << ans_first[i] << " " << ans_second[i] << std::endl;
    }
    fout.close();
}

void compute_mps(u_short_array& chords,
                 u_short_array& ans_first,
                 u_short_array& ans_second) {
    const int n_vertices = chords.size();
    // M[i][j]: number of chords in maximum planar subset between i and j
    // C[i][j]: whether the chord connected to j is selected
    u_short_matrix M(n_vertices, u_short_array(n_vertices));
    bool_matrix C(n_vertices, bool_array(n_vertices));
    int i, j, l, k, num;

    for (l = 1; l < n_vertices; ++l) {
        for (i = 0; i < n_vertices - l; ++i) {
            j = i + l;
            k = chords[j];
            // case 1
            if (k > j || k < i) {
                M[i][j] = M[i][j-1];
            }
            // case 2
            if (i < k && k < j) {
                // not select (k, j) chord
                M[i][j] = M[i][j-1];
                // select (k, j) chord
                num = M[i][k-1] + M[k+1][j-1] + 1;
                if (num > M[i][j]) {
                    M[i][j] = num;
                    C[i][j] = 1;
                }
            }
            // case 3
            if (k == i) {
                M[i][j] = M[i+1][j-1] + 1;
                C[i][j] = 1;
            }
        }
    }

    get_ans(chords, ans_first, ans_second, C, 0, n_vertices - 1);
}

// back traverse to get answer(reverse), store it into ans
void get_ans(u_short_array& chords,
             u_short_array& ans_first,
             u_short_array& ans_second,
             bool_matrix& C,
             int i,
             int j) {
    int k;
    if (i < j) {
        if (!C[i][j]) {
            get_ans(chords, ans_first, ans_second, C, i, j-1);
        } else {
            k = chords[j];
            // case 3
            if (k == i) {
                ans_first.push_back(k);
                ans_second.push_back(j);
                get_ans(chords, ans_first, ans_second, C, i + 1, j - 1);
            }
            // case 2
            if (i < k && k < j) {
                get_ans(chords, ans_first, ans_second, C, i, k - 1);
                ans_first.push_back(k);
                ans_second.push_back(j);
                get_ans(chords, ans_first, ans_second, C, k + 1, j - 1);
            }
        }
    }
}
