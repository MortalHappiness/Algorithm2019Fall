#include <iostream>
#include "set.h"

// ================================

Set::Set(int n) {
    int i;
    for (i = 0; i < n; ++i) {
        _set.push_back(SetNode{i, 0});
    }
}

void Set::Union(int x, int y) {
    _link(Find(x), Find(y));
}

int Set::Find(int x) {
    if (x != _set[x].p) {
        _set[x].p = Find(_set[x].p);
    }
    return _set[x].p;
}

void Set::_link(int x, int y) {
    if (_set[x].rank > _set[y].rank) {
        _set[y].p = x;
    } else {
        _set[x].p = y;
        if (_set[x].rank == _set[y].rank) {
            ++(_set[y].rank);
        }
    }
}
