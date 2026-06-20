#pragma once

#include "defintion.hpp"
#include <vector>

constexpr int pvTableSize = 0x100000 * 2;
struct Board;

struct PVEntry {
    U64 hashkey = 0;
    int move = NO_MOVE;
};

struct PVTable {
    std::vector<PVEntry> entries;
    int numEntries = 0;

    void init();
    void clear();
    void store(U64 hashkey, int move);
    int probe(U64 hashkey); 
    int getPVSequence(Board &board, int depth);
};