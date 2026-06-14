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
    
    assert(foundPieceIndex != -1);
    assert(0 <= foundPieceIndex && foundPieceIndex < MAX_NUM_PIECE);

    board.numPieceOnBoard[piece]--;
    board.pieceSq[piece][foundPieceIndex] = board.pieceSq[piece][board.numPieceOnBoard[piece]];
}
void movePiece(int from, int to, Board &board) {
    assert(isSqOnBoard(from));
    assert(isSqOnBoard(to));

    int piece = board.squareToPiece[from];
    assert(isPieceValid(piece));
    int color = pieceColor[piece];
    assert(isSideValid(color));

    hashPiece(piece, from, board);
    board.squareToPiece[from] = EMPTY;
    
    hashPiece(piece, to, board);
    board.squareToPiece[to] = piece;

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

void recordHistory(int move, Board &board) {
    board.history[board.historyIndex].hashkey = board.hashkey;
    board.history[board.historyIndex].move = move;
    board.history[board.historyIndex].fiftyMove = board.fiftyMove;
    board.history[board.historyIndex].enPasSq = board.enPasSq;
    board.history[board.historyIndex].castlePermission = board.castlePermission;
}
void applyEnPassant(int move, Board &board) {
    int side = board.side;
    int to = moveToTo(move);
    if (side == WHITE) {
        clearPiece(to - 10, board);
    } else {
        clearPiece(to + 10, board);
    }
}
void applyCastle(int move, Board &board) {
    int to = moveToTo(move);
    switch (to)
    {
        case C1: movePiece(A1, D1, board); break;
        case G1: movePiece(H1, F1, board); break;
        case C8: movePiece(A8, D8, board); break;
        case G8: movePiece(H8, F8, board); break;    
        default: assert(false); break;
    }
}
void applyHashCastle(int move, Board &board) {
    int from = moveToFrom(move);
    int to = moveToTo(move);

    hashCastle(board);
    board.castlePermission &= castlePermission[from];
    board.castlePermission &= castlePermission[to];
    hashCastle(board);
}
void applyHashEnPassant(int move, Board &board) {
    int from = moveToFrom(move);
    int side = board.side;

    if (board.enPasSq != NO_SQ) {
        hashEnPassant(board);
        board.enPasSq = NO_SQ;
    }

    int piece = board.squareToPiece[from];
    if (isPawn[piece]) {
        board.fiftyMove = 0;
        if (move & PAWN_START_FLAG) {
            if (side == WHITE) {
                board.enPasSq = from + 10;
                assert(sqToRank[board.enPasSq] == RANK_3);
            } else {
                board.enPasSq = from - 10;
                assert(sqToRank[board.enPasSq] == RANK_6);
            }
            hashEnPassant(board);
        }
    }
}
void applyCapturedPiece(int move, Board &board) {
    int to = moveToTo(move);
    int capturedPiece = moveToCapturedPiece(move);
    if (capturedPiece != EMPTY) {
        assert(isPieceValid(capturedPiece));
        if (to == 62) std::cout << "Holer" << std::endl;
        clearPiece(to, board);
        board.fiftyMove = 0;
    }
}
void applyKingSq(int move, Board &board) {
    int to = moveToTo(move);
    if (isKing[board.squareToPiece[to]]) {
        board.kingSq[board.side] = to;
    }
}
void applyPromotion(int move, Board &board) {
    int to = moveToTo(move);
    int promotedPiece = moveToPromotedPiece(move);
    if (promotedPiece != EMPTY) {
        assert(isPieceValid(promotedPiece) && !isPawn[promotedPiece] &&
               !isKing[promotedPiece]);
        clearPiece(to, board);
        addPiece(to, board, promotedPiece);
    }
}

bool makeMove(Board &board, int move) {
    assert(board.checkBoard());

    int from = moveToFrom(move);
    assert(isSqOnBoard(from));
    
    int to = moveToTo(move);
    assert(isSqOnBoard(to));
    
    int side = board.side;
    assert(isSideValid(side));

    assert(0 <= board.ply && board.ply < MAX_MOVE_GENERATED);
    assert(0 <= board.historyIndex && board.historyIndex <= MAX_GAME_MOVE);

    recordHistory(move, board);

    board.fiftyMove++;

    if (move & EN_PASSANT_FLAG) {
        applyEnPassant(move, board);
    } else if (move & CASTLE_FLAG) {
        applyCastle(move, board);
    }

    applyHashCastle(move, board);
    applyHashEnPassant(move, board);

    applyCapturedPiece(move, board);
    movePiece(from, to, board);
    applyKingSq(move, board);
    applyPromotion(move, board);
    
    board.side ^= 1;
    hashSide(board);

    board.historyIndex++;
    assert(board.historyIndex >= 0 && board.historyIndex < MAX_GAME_MOVE);
    
    board.ply++;
    assert(board.ply >= 0 && board.ply < MAX_MOVE_GENERATED);

    assert(board.checkBoard());

    if (isSqBeingAttacked(board.kingSq[side], board.side, board)) {
        takeMove(board);
        return false;
    }
    return true;
}

void undoHashEnPassant(UNDO undo, Board &board) {
    if (board.enPasSq != NO_SQ) hashEnPassant(board);
    board.enPasSq = undo.enPasSq;
    if (board.enPasSq != NO_SQ) hashEnPassant(board);
}
void undoHashCastle(UNDO undo, Board &board) {
    hashCastle(board);
    board.castlePermission = undo.castlePermission;
    hashCastle(board);
}
void undoEnPassant(int move, Board &board) {
    int to = moveToTo(move);
    if (board.side == WHITE) {
        addPiece(to - 10, board, bP);
    } else {
        addPiece(to - 10, board, wP);
    }
}
void undoCastle(int move, Board &board) {
    int to = moveToTo(move);
    switch (to) {
        case C1: movePiece(D1, A1, board); break;
        case C8: movePiece(D8, A8, board); break;
        case G1: movePiece(F1, H1, board); break;
        case G8: movePiece(F8, H8, board); break;
        default: assert(false); break;
    }
}
void undoKingSq(int move, Board &board) {
    int from = moveToFrom(move);
    if (isKing[board.squareToPiece[from]]) {
        board.kingSq[board.side] = from;
    }
}
void undoCapturedPiece(int move, Board &board) {
    int to = moveToTo(move);
    int capturedPiece = moveToCapturedPiece(move);
    if (capturedPiece != EMPTY) {
        assert(isPieceValid(capturedPiece));
        addPiece(to, board, capturedPiece);
    }
}
void undoPromotion(int move, Board &board) {
    int from = moveToFrom(move);
    int promotedPiece = moveToPromotedPiece(move);
    if (promotedPiece != EMPTY) {
        assert(isPieceValid(promotedPiece) && !isPawn[promotedPiece] &&
               !isKing[promotedPiece]);
        clearPiece(from, board);
        addPiece(from, board, (pieceColor[promotedPiece] == WHITE ? wP : bP));
    }
}

void takeMove(Board &board) {
    assert(board.checkBoard());
    board.historyIndex--;
    assert(board.historyIndex >= 0 && board.historyIndex < MAX_GAME_MOVE);

    board.ply--;
    assert(board.ply >= 0 && board.ply < MAX_MOVE_GENERATED);

    UNDO undo = board.history[board.historyIndex]; 
    int move = undo.move;

    int from = moveToFrom(move);
    assert(isSqOnBoard(from));
    
    int to   = moveToTo(move);
    assert(isSqOnBoard(to));

    board.fiftyMove = undo.fiftyMove;

    undoHashEnPassant(undo, board);
    undoHashCastle(undo, board);
    
    board.side ^= 1;
    hashSide(board);

    if (move & EN_PASSANT_FLAG) {
        undoEnPassant(move, board);
    } else if (move & CASTLE_FLAG) {
        undoCastle(move, board);
    }

    movePiece(to, from, board);

    undoKingSq(move, board);
    undoCapturedPiece(move, board);
    undoPromotion(move, board);
    
    assert(board.checkBoard());
}