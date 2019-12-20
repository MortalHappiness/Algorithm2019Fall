// Disjoint set implementation

#ifndef _SET_H
#define _SET_H

// ================================

#include <vector>

// ================================

typedef struct {
    int p;
    int rank;
} SetNode;

class Set {
public:
    // Construct n separated sets
    Set(int);
    // Union
    void Union(int, int);
    // Find
    int Find(int);

private:
    std::vector<SetNode> _set;
    void _link(int, int);
};

// ================================

#endif
