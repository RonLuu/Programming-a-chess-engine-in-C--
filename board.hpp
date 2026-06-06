#pragma once

#include "defintion.hpp"

struct Board {
    int squareToPiece[NUM_BIG_SQ];
    U64 pawnSq[3];
    int kingSq[2];

    int side;
    int enPasSq;
    int fiftyMove;

    int ply;
    int historyIndex;
    
    U64 hashkey;

    int numPieceOnBoard[NUM_PIECE];

    int castlePermission;

    int numBigPieces[2];
    int numMajPieces[2];
    int numMinPieces[2];

    int materialPoints[2];

    int pieceSq[NUM_PIECE][MAX_NUM_PIECE];
};