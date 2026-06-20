#pragma once

#include "defintion.hpp"
#include "pvtable.hpp"

struct Board {
    std::array<int, NUM_BIG_SQ> squareToPiece;
    std::array<U64, NUM_OF_SIDE + 1> pawnBitboard;
    std::array<int, NUM_OF_SIDE> kingSq;

    int side;

    int enPasSq;
    
    int fiftyMove;

    int ply;
    
    int historyIndex;
    std::array<UNDO, MAX_GAME_MOVE> history;
    
    U64 hashkey;

    std::array<int, NUM_UNIQUE_PIECE> numPieceOnBoard;

    int castlePermission;

    std::array<int, NUM_OF_SIDE> numBigPieces;
    std::array<int, NUM_OF_SIDE> numMajPieces;
    std::array<int, NUM_OF_SIDE> numMinPieces;
    
    std::array<int, NUM_OF_SIDE> materialPoints;

    std::array<std::array<int, MAX_NUM_PIECE>, NUM_UNIQUE_PIECE> pieceSq;

    std::array<int, MAX_DEPTH> pvSequence;

    PVTable pvTable;

    bool checkBoard();
    U64 generateHashKey();
    void resetBoard();
    void updateListMaterial();
};