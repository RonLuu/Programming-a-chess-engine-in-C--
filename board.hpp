#pragma once

#include "defintion.hpp"

struct Board {
    int squareToPiece[NUM_BIG_SQ];
    U64 pawnBitboard[3];
    int kingSq[NUM_OF_SIDE];

    int side;

    int enPasSq;
    
    int fiftyMove;

    int ply;
    
    int historyIndex;
    UNDO history[MAX_GAME_MOVE];
    
    U64 hashkey;

    int numPieceOnBoard[NUM_UNIQUE_PIECE];

    int castlePermission;

    int numBigPieces[NUM_OF_SIDE];
    int numMajPieces[NUM_OF_SIDE];
    int numMinPieces[NUM_OF_SIDE];

    int materialPoints[NUM_OF_SIDE];

    int pieceSq[NUM_UNIQUE_PIECE][MAX_NUM_PIECE];


    bool checkBoard();
    U64 generateHashKey();
    void resetBoard();
    void updateListMaterial();
};