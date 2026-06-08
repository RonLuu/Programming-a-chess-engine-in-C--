#include "attack.hpp"

constexpr int numKnDir = 8;
constexpr int numRkDir = 4;

constexpr int KnDir[numKnDir] = {-8, -19, -21, -12, 8,  19,  21,  12};
constexpr int RkDir[numRkDir] = {-1, 1, -10, 10};

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
bool isAttackedByKnight(int sq, int side, Board& board) {
    for (int knDir = 0; knDir < numKnDir; knDir++) {
        int piece = board.squareToPiece[sq+knDir];
        if (isPieceValid(piece) && isKnight[piece] && pieceColor[piece] == side) {
            return true;
        }
    }
    return false;
}
bool isAttackedByRookQueen(int sq, int side, Board& board) {
    for (int index = 0; index < numRkDir; index++) {
        int newSq = sq + RkDir[index];
        int curPiece = board.squareToPiece[newSq];

        while (curPiece != OFFBOARD) {
            if (curPiece != EMPTY) {
                if (isRookQueen[curPiece] && pieceColor[curPiece] == side) {
                    return true;
                }
                break;
            } 
            newSq += RkDir[index];
            curPiece = board.squareToPiece[newSq];
        }
    }

    return false;
}

bool isSqBeingAttacked(int sq, int side, Board &board) {
    assert(isSqOnBoard(sq));
    assert(isSideValid(side));
    assert(board.checkBoard());

    return isAttackedByPawn(sq, side, board) ||
           isAttackedByKnight(sq, side, board) ||
           isAttackedByRookQueen(sq, side, board);
}