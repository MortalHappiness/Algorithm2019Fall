# check whether the answer is correct

import sys

# ==================================

def read_input_file(filename):
    with open(filename, "r") as fin:
        n_vertices = int(next(fin))
        n_chords = n_vertices // 2
        chords = [0 for _ in range(n_vertices)]
        for i in range(n_chords):
            line = next(fin)
            a, b = line.split()
            a = int(a)
            b = int(b)
            chords[a] = b
            chords[b] = a
    return chords

def read_output_file(filename):
    chords = list()
    with open(filename, "r") as fin:
        next(fin)
        for line in fin:
            a, b = line.split()
            chords.append((int(a), int(b)))
    return chords

def is_crossing(chord1, chord2):
    a, b = chord1
    c, d = chord2
    if (a < c < b) and (d < a or d > b):
        return True
    if (a < d < b) and (c < a or c > b):
        return True
    return False

def check_ans(input_chords, output_chords):
    # check whether the chords in output are all in input
    for a, b in output_chords:
        if a > b:
            print("Chord order reversed!")
            return
        if input_chords[a] != b:
            print("Some chords in output are not in the input!")
            return
    # check whether there are crossing chords
    for i in range(len(output_chords) - 1):
        for j in range(i, len(output_chords)):
            if is_crossing(output_chords[i], output_chords[j]):
                print("Some chords in output are crossing!")
                return
    print("Pass!")

def main(script, inputfile, outputfile):
    input_chords = read_input_file(inputfile)
    output_chords = read_output_file(outputfile)
    check_ans(input_chords, output_chords)

# ==================================

if __name__ == "__main__":
    if len(sys.argv) != 3:
        raise Exception("usage: python utility/check_ans.py <input_file> <output_file>")
    main(*sys.argv)
