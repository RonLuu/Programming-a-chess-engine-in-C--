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
bool isAttackedByKnight(int sq, int side, Board& board) {
    for (int index = 0; index < numKnDir; index++) {
        int piece = board.squareToPiece[sq+KnDir[index]];
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

        while (curPiece != NULL_PIECE) {
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
bool isAttackedByBishopQueen(int sq, int side, Board& board) {
    for (int index = 0; index < numBsDir; index++) {
        int newSq = sq + BsDir[index];
        int curPiece = board.squareToPiece[newSq];

        while (curPiece != NULL_PIECE) {
            if (curPiece != EMPTY) {
                if (isBishopQueen[curPiece] && pieceColor[curPiece] == side) {
                    return true;
                }
                break;
            } 
            newSq += BsDir[index];
            curPiece = board.squareToPiece[newSq];
        }
    }

    return false;
}
bool isAttackedByKing(int sq, int side, Board& board) {
    for (int index = 0; index < numKiDir; index++) {
        int newSq = sq + KiDir[index];
        int curPiece = board.squareToPiece[newSq];

        if (isPieceValid(curPiece)) {
            if (isKing[curPiece] && pieceColor[curPiece] == side) {
                return true;
            }
            break;
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
           isAttackedByRookQueen(sq, side, board) ||
           isAttackedByBishopQueen(sq, side, board) ||
           isAttackedByKing(sq, side, board);
}