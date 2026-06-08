#include "attack.hpp"

bool isSqBeingAttacked(int sq, int side, Board &board) {
    assert(isSqOnBoard(sq));
    assert(isSideValid(side));
    assert(board.checkBoard());

}