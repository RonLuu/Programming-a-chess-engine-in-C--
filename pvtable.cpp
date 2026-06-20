#include "board.hpp"
#include "makemove.hpp"
#include "movegen.hpp"
#include "pvtable.hpp"

void PVTable::init() {
    numEntries = pvTableSize / sizeof(PVEntry);
    entries.resize(numEntries);
    clear();
    std::cout << "PVTable was initialised with " << numEntries << " entries" << std::endl;
}

void PVTable::clear() { 
    std::fill(entries.begin(), entries.end(), PVEntry{}); 
}

void PVTable::store(U64 hashkey, int move) {
    int index = hashkey % numEntries;
    assert(0 <= index && index < numEntries);

    entries[index].move = move;
    entries[index].hashkey = hashkey;
}

int PVTable::probe(U64 hashkey) {
    int index = hashkey % numEntries;
    assert(0 <= index && index < numEntries);
    if (hashkey == entries[index].hashkey) {
        return entries[index].move;
    }
    return NO_MOVE;
}

int PVTable::getPVSequence(Board &board, int depth) {
    assert(depth < MAX_DEPTH);

    int move = probe(board.hashkey);
    int curDepth = 0;
    while (move != NO_MOVE && curDepth < depth) {
        assert(curDepth < MAX_DEPTH);
        if (isMoveValid(board, move)) {
            makeMove(board, move);
            board.pvSequence[curDepth++] = move;
        } else {
            break;
        }

        move = probe(board.hashkey);
    }

    while (board.ply > 0) {
        takeMove(board);
    }

    return curDepth;
}