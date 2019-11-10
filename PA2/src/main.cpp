#include <iostream>
#include "mps.h"

// ======================================

void help_message() {
    std::cout << "usage: ./mps <input_file> <output_file>" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        help_message();
        return 0;
    }

    // Read file
    int_array chords;
    read_file(argv[1], chords);

    // Compute mps
    chord_set ans;
    compute_mps(chords, ans);

    // Write file
    write_file(argv[2], ans);
}
