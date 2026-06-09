#include "board.hpp"

void checkMaterialPoint(Board& board) {
    std::array<int,2> materialPointsCounter = {0, 0};
    for (int sq64 = 0; sq64 < NUM_SML_SQ; sq64++) {
        int sq120 = sq64To120[sq64];
        int curPiece = board.squareToPiece[sq120];
        int colour = pieceColor[curPiece];
        materialPointsCounter[colour] += pieceToValue[curPiece];
    }

    assert(materialPointsCounter[WHITE] == board.materialPoints[WHITE] && 
           materialPointsCounter[BLACK] == board.materialPoints[BLACK]);
}
void checkNumberOfPiece(Board& board) {
    std::array<int, 13>piece_counter = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int curSq = 0; curSq < NUM_SML_SQ; curSq++) {
        int sq120 = sq64To120[curSq];
        int curPiece = board.squareToPiece[sq120];
        piece_counter[curPiece] ++;
    }

    for (int i = wP; i <= bK; i++) {
        assert(piece_counter[i] == board.numPieceOnBoard[i]);
    }
}
void checkNumberOfSpecialPiece(Board& board) {
    std::array<int,2> bigPiecesCounter = {0, 0};
    std::array<int,2> majPiecesCounter = {0, 0};
    std::array<int,2> minPiecesCounter = {0, 0};

    for (int curSq = 0; curSq < NUM_SML_SQ; curSq++) {
        int sq120 = sq64To120[curSq];
        int curPiece = board.squareToPiece[sq120];
        int color = pieceColor[curPiece];

        if (isPieceBig[curPiece]) bigPiecesCounter[color]++; 
        if (isPieceMaj[curPiece]) majPiecesCounter[color]++; 
        if (isPieceMin[curPiece]) minPiecesCounter[color]++; 
    }

    assert(bigPiecesCounter[WHITE] == board.numBigPieces[WHITE] && bigPiecesCounter[BLACK] == board.numBigPieces[BLACK]);
    assert(majPiecesCounter[WHITE] == board.numMajPieces[WHITE] && majPiecesCounter[BLACK] == board.numMajPieces[BLACK]);
    assert(minPiecesCounter[WHITE] == board.numMinPieces[WHITE] && minPiecesCounter[BLACK] == board.numMinPieces[BLACK]);
    
}
void checkPiecePosition(Board& board) {
    for (int curPiece = wP; curPiece <= bK; curPiece++) {
        for (int pieceIndex = 0; pieceIndex < board.numPieceOnBoard[curPiece]; pieceIndex++) {
            int sq120 = board.pieceSq[curPiece][pieceIndex];
            assert(board.squareToPiece[sq120] == curPiece);   
        }
    }
}
void checkPawnBit(Board& board) {
    U64 whiteBit = board.pawnBitboard[WHITE];
    U64 blackBit = board.pawnBitboard[BLACK]; 
    U64 bothBit  = board.pawnBitboard[BOTH];

    int whiteBitCount = std::popcount(whiteBit);
    int blackBitCount = std::popcount(blackBit);
    int bothBitCount  = std::popcount(bothBit);
    
    assert(whiteBitCount == board.numPieceOnBoard[wP]);
    assert(blackBitCount == board.numPieceOnBoard[bP]);
    assert(bothBitCount == board.numPieceOnBoard[wP] + board.numPieceOnBoard[bP]);


    while (whiteBit) {
        int sq64 = popBit(whiteBit);
        assert(board.squareToPiece[sq64To120[sq64]] == wP);
    }

    while (blackBit) {
        int sq64 = popBit(blackBit);
        assert(board.squareToPiece[sq64To120[sq64]] == bP);
    }
    
    while (bothBit) {
        int sq64 = popBit(bothBit);
        assert(board.squareToPiece[sq64To120[sq64]] == bP ||
               board.squareToPiece[sq64To120[sq64]] == wP);
    }
}

void hashPieces(U64& key, Board&board) {
    for (int curSq = 0; curSq < NUM_SML_SQ; curSq++)
    {
        int sq120 = sq64To120[curSq];
        int curPiece = board.squareToPiece[sq120];
        if (curPiece != EMPTY && curPiece != NO_SQ && curPiece != OFFBOARD) {
            assert(isPieceValid(curPiece));
            key ^= pieceHashKeys[curPiece][sq120];
        }
    }
}
void hashSide(U64& key, Board& board) {
    if (board.side == WHITE) {
        key ^= sideHashKey;
    }
}
void hashEnPassant(U64& key, Board& board) {
    int enPasSq = board.enPasSq;
    if (enPasSq != NO_SQ) {
        assert(isSqOnBoard(enPasSq));
        assert(sqToRank[enPasSq] == RANK_3 || sqToRank[enPasSq] == RANK_6);
        key ^= pieceHashKeys[EMPTY][enPasSq];
    }
}
void hashCastlePerm(U64& key, Board& board) {
    assert(0 <= board.castlePermission && board.castlePermission <= 15);
    key ^= castleHashKeys[board.castlePermission];
}

void Board::updateListMaterial() {
    int curPiece;
    int color;

    for (int sq64 = 0; sq64 < NUM_SML_SQ; sq64++) {
        int sq120 = sq64To120[sq64];
        curPiece = squareToPiece[sq120];
        if (curPiece != EMPTY) {
            color = pieceColor[curPiece];

            if (isPieceBig[curPiece]) numBigPieces[color] ++;
            if (isPieceMaj[curPiece]) numMajPieces[color] ++;
            if (isPieceMin[curPiece]) numMinPieces[color] ++;

            materialPoints[color] += pieceToValue[curPiece];

            pieceSq[curPiece][numPieceOnBoard[curPiece]++] = sq120;

            if (curPiece == wK) kingSq[WHITE] = sq120;
            if (curPiece == bK) kingSq[BLACK] = sq120;

            if (curPiece == wP) {
                setBit(pawnBitboard[WHITE], sq64);
                setBit(pawnBitboard[BOTH], sq64);
            }
            else if (curPiece == bP) {
                setBit(pawnBitboard[BLACK], sq64);
                setBit(pawnBitboard[BOTH], sq64);
            }

        }
    }
}

U64 Board::generateHashKey() {
    U64 key = 0;
    hashPieces(key, *this);
    hashSide(key, *this);
    hashEnPassant(key, *this);
    hashCastlePerm(key, *this);
    return key;
}

bool Board::checkBoard() {
    checkPiecePosition(*this);
    checkNumberOfPiece(*this);
    checkNumberOfSpecialPiece(*this);
    checkMaterialPoint(*this);
    checkPawnBit(*this);

    assert(side == WHITE || side == BLACK);
    assert(enPasSq == NO_SQ || sqToRank[enPasSq] == RANK_3 || sqToRank[enPasSq] == RANK_6);
    assert(squareToPiece[kingSq[WHITE]] == wK);
    assert(squareToPiece[kingSq[BLACK]] == bK);

    return true;
}

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
