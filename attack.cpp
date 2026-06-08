#include "attack.hpp"

bool isAttackedByPawn(int sq, int side, Board& board) {
    if (side == WHITE) {
        if (board.squareToPiece[sq - 11] == wP || board.squareToPiece[sq - 9] == wP) {
            return true;
        }
    } else {
        if (board.squareToPiece[sq + 11] == bP || board.squareToPiece[sq + 9] == bP) {
            return true;
        }
    }
    return false;
}

bool isSqBeingAttacked(int sq, int side, Board &board) {
    assert(isSqOnBoard(sq));
    assert(isSideValid(side));
    assert(board.checkBoard());

    return isAttackedByPawn(sq, side, board)
}