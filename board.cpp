#include "board.hpp"

void Board::resetBoard() {
    // Set all the square to null piece
    for (int i = 0; i < NUM_BIG_SQ; i++)
    {
        squareToPiece[i] = NULL_PIECE;
    }
    
    // Set all the INNER square to empyt piece
    for (int i = 0; i < NUM_SML_SQ; i++)
    {
        int sq120 = sq64To120[i];
        squareToPiece[sq120] = EMPTY;
    }
    
    // Set all pawns bit positions to be zero
    // Add one for both
    for (int i = 0; i < NUM_OF_SIDE+1; i++)
    {
        pawnBitboard[i] = 0LL;
    }

    // Set all king positions to be off board
    for (int i = 0; i < NUM_OF_SIDE; i++)
    {
        kingSq[i] = NO_SQ;
    }

    side = BOTH;

    enPasSq = NO_SQ;

    fiftyMove = 0;

    ply = 0;
    
    historyIndex = 0;
    
    hashkey = 0LL;
    
    for (int i = 0; i < NUM_UNIQUE_PIECE; i++)
    {
        numPieceOnBoard[i] = 0;
    }
    
    castlePermission = 0;


    // Set all the number of all types of pieces to be 0
    // Set all material points to be 0
    for (int i = 0; i < NUM_OF_SIDE; i++)
    {
        numBigPieces[i] = 0;
        numMajPieces[i] = 0;
        numMinPieces[i] = 0;
        materialPoints[i] = 0;
    }

    for (int i = 0; i < NUM_UNIQUE_PIECE; i++)
    {
        for (int j = 0; j < MAX_NUM_PIECE; j++)
        {
            pieceSq[i][j] = NO_SQ;
        }
        
    }
}

