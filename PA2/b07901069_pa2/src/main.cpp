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
    u_short_array chords;
    read_file(argv[1], chords);

    // Compute mps
    u_short_array ans_first;
    u_short_array ans_second;
    compute_mps(chords, ans_first, ans_second);

    // Write file
    write_file(argv[2], ans_first, ans_second);
}
