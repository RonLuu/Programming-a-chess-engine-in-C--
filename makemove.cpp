#include "makemove.hpp"

void addPiece(int sq, Board &board, int piece) {
    assert(isPieceValid(piece));
    assert(isSqOnBoard(sq));

    hashPiece(piece, sq, board);
    board.squareToPiece[sq] = piece;

    int color = pieceColor[piece];
    board.materialPoints[color] += pieceToValue[piece];

    if (isPieceBig[piece]) {
        board.numBigPieces[color]++;
        if (isPieceMaj[piece]) {
            board.numMajPieces[color]++;
        } else {
            board.numMinPieces[color]++;
        }
    } else {
        setBit(board.pawnBitboard[color], sq120To64[sq]);
        setBit(board.pawnBitboard[BOTH], sq120To64[sq]);
    }

    board.pieceSq[piece][board.numPieceOnBoard[piece]++] = sq;
}
void clearPiece(int sq, Board &board) {
    assert(isSqOnBoard(sq));

    int piece = board.squareToPiece[sq];
    assert(isPieceValid(piece));

    hashPiece(piece, sq, board);
    board.squareToPiece[sq] = EMPTY;
    
    int color = pieceColor[piece];
    board.materialPoints[color] -= pieceToValue[piece];

    if (isPieceBig[piece]) {
        board.numBigPieces[color]--;
        if(isPieceMaj[piece]) {
            board.numMajPieces[color]--;
        } else {
            board.numMinPieces[color]--;
        }
    } else {
        clrBit(board.pawnBitboard[color], sq120To64[sq]);
        clrBit(board.pawnBitboard[BOTH], sq120To64[sq]);
    }

    int foundPieceIndex = -1;
    for (int index = 0; index < board.numPieceOnBoard[piece]; index++) {
        if (board.pieceSq[piece][index] == sq) {
            foundPieceIndex = index;
            break;
        }
    }
    
    assert(foundPieceIndex == -1);
    assert(0 <= foundPieceIndex && foundPieceIndex < MAX_NUM_PIECE);

    board.numPieceOnBoard[piece]--;
    board.pieceSq[piece][foundPieceIndex] = board.pieceSq[piece][board.numPieceOnBoard[piece]];
}
void movePiece(int from, int to, Board &board, int piece) {
    assert(isSqOnBoard(from));
    assert(isSqOnBoard(to));

    int piece = board.squareToPiece[from];
    assert(isPieceValid(piece));
    int color = pieceColor[piece];
    assert(isSideValid(color));

    hashPiece(piece, from, board);
    board.squareToPiece[from] = EMPTY;
    
    hashPiece(piece, to, board);
    board.squareToPiece[piece] = piece;

    if (!isPieceBig[piece]) {
        clrBit(board.pawnBitboard[color], sq120To64[from]);
        setBit(board.pawnBitboard[color], sq120To64[to]);
        
        clrBit(board.pawnBitboard[BOTH], sq120To64[from]);
        setBit(board.pawnBitboard[BOTH], sq120To64[to]);
    }

    for (int index = 0; index < board.numPieceOnBoard[piece]; index++) {
        if (board.pieceSq[piece][index] == from) {
            board.pieceSq[piece][index] = to;
            break;
        }
    }
    
}