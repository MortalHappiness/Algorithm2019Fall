#include "mps.h"

// =====================================

void read_file(char *filename, int_array& chords) {
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

void write_file(char *filename, chord_set& ans) {
    std::fstream fout;
    fout.open(filename, std::ios::out);
    fout << ans.size() << std::endl;
    int i;
    for (i = 0; i < ans.size(); ++i) {
        fout << ans[i].first << " " << ans[i].second << std::endl;
    }
    fout.close();
}

void compute_mps(int_array& chords, chord_set& ans) {
    const int n_vertices = chords.size();
    // M[i][j]: number of chords in maximum planar subset between i and j
    // C[i][j]: whether the chord connected to j is selected
    int_matrix M(n_vertices, int_array(n_vertices));
    int_matrix C(n_vertices, int_array(n_vertices));
    int i, j, l, k, num;

    for (l = 1; l < n_vertices; ++l) {
        for (i = 0; i < n_vertices - l; ++i) {
            j = i + l;
            k = chords[j];
            // case 3
            if (k == i) {
                M[i][j] = M[i+1][j-1] + 1;
                C[i][j] = 1;
            }
            // case 1
            if (k > j || k < i) {
                M[i][j] = M[i][j-1];
                C[i][j] = 0;
            }
            // case 2
            if (i < k && k < j) {
                // not select (k, j) chord
                M[i][j] = M[i][j-1];
                C[i][j] = 0;
                // select (k, j) chord
                num = M[i][k-1] + M[k+1][j-1] + 1;
                if (num > M[i][j]) {
                    M[i][j] = num;
                    C[i][j] = 1;
                }
            }
        }
    }

    get_ans(chords, ans, C, 0, n_vertices - 1);
}

// back traverse to get answer(reverse), store it into ans
void get_ans(int_array& chords,
             chord_set& ans,
             int_matrix& C,
             int i,
             int j) {
    int k;
    if (i < j) {
        if (!C[i][j]) {
            get_ans(chords, ans, C, i, j-1);
        } else {
            k = chords[j];
            // case 3
            if (k == i) {
                Chord chord(k, j);
                ans.push_back(chord);
                get_ans(chords, ans, C, i + 1, j - 1);
            }
            // case 2
            if (i < k && k < j) {
                get_ans(chords, ans, C, i, k - 1);
                Chord chord(k, j);
                ans.push_back(chord);
                get_ans(chords, ans, C, k + 1, j - 1);
            }
        }
    }
}
