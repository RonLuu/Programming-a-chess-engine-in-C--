#include "movegen.hpp"

void addCaptureMove(Board &board, int move, MOVELIST &moveList) {
    int index = moveList.currentSize;
    (moveList.moves)[index].move = move;
    (moveList.moves)[index].score = 0;
    moveList.currentSize++;
}
void addEnPassantMove(Board &board, int move, MOVELIST &moveList) {
    int index = moveList.currentSize;
    (moveList.moves)[index].move = move;
    (moveList.moves)[index].score = 0;
    moveList.currentSize++;
}
void addQuietMove(Board &board, int move, MOVELIST &moveList) {
    int index = moveList.currentSize;
    (moveList.moves)[index].move = move;
    (moveList.moves)[index].score = 0;
    moveList.currentSize++;
}
// Add an extra rule for promotion
void addBlackPawnMove(Board &board, int from, MOVELIST &moveList) {
    int to = from - 10;

    assert(isSqOnBoard(from));
    assert(isSqOnBoard(to));

    if (sqToRank[from] != RANK_2) {
        int move = makeMove(from, to, EMPTY, EMPTY, NO_FLAG);
        addQuietMove(board, move, moveList);
    } else {
        int promoteQ = makeMove(from, to, EMPTY, wQ, NO_FLAG);
        int promoteR = makeMove(from, to, EMPTY, wR, NO_FLAG);
        int promoteN = makeMove(from, to, EMPTY, wN, NO_FLAG);
        int promoteB = makeMove(from, to, EMPTY, wB, NO_FLAG);

        addQuietMove(board, promoteQ, moveList);
        addQuietMove(board, promoteR, moveList);
        addQuietMove(board, promoteN, moveList);
        addQuietMove(board, promoteB, moveList);
    }
}
void addBlackPawnCaptureMove(Board &board, int from, int to, int capturedPiece, MOVELIST &moveList) {
    assert(isPieceValid(capturedPiece));
    assert(isSqOnBoard(from));
    assert(isSqOnBoard(to));

    if (sqToRank[from] != RANK_2) {
        int move = makeMove(from, to, capturedPiece, EMPTY, NO_FLAG);
        addCaptureMove(board, move, moveList);
    } else {
        int promoteQ = makeMove(from, to, capturedPiece, wQ, NO_FLAG);
        int promoteR = makeMove(from, to, capturedPiece, wR, NO_FLAG);
        int promoteN = makeMove(from, to, capturedPiece, wN, NO_FLAG);
        int promoteB = makeMove(from, to, capturedPiece, wB, NO_FLAG);

        addCaptureMove(board, promoteQ, moveList);
        addCaptureMove(board, promoteR, moveList);
        addCaptureMove(board, promoteN, moveList);
        addCaptureMove(board, promoteB, moveList);
    }
}
// Add an extra rule for promotion
void addWhitePawnMove(Board &board, int from, MOVELIST &moveList) {
    int to = from + 10;

    assert(isSqOnBoard(from));
    assert(isSqOnBoard(to));

    if (sqToRank[from] != RANK_7) {
        int move = makeMove(from, to, EMPTY, EMPTY, NO_FLAG);
        addQuietMove(board, move, moveList);
    } else {
        int promoteQ = makeMove(from, to, EMPTY, wQ, NO_FLAG);
        int promoteR = makeMove(from, to, EMPTY, wR, NO_FLAG);
        int promoteN = makeMove(from, to, EMPTY, wN, NO_FLAG);
        int promoteB = makeMove(from, to, EMPTY, wB, NO_FLAG);

        addQuietMove(board, promoteQ, moveList);
        addQuietMove(board, promoteR, moveList);
        addQuietMove(board, promoteN, moveList);
        addQuietMove(board, promoteB, moveList);
    }
}
void addWhitePawnCaptureMove(Board &board, int from, int to, int capturedPiece, MOVELIST &moveList) {
    assert(isPieceValid(capturedPiece));
    assert(isSqOnBoard(from));
    assert(isSqOnBoard(to));

    if (sqToRank[from] != RANK_7) {
        int move = makeMove(from, to, capturedPiece, EMPTY, NO_FLAG);
        addCaptureMove(board, move, moveList);
    } else {
        int promoteQ = makeMove(from, to, capturedPiece, wQ, NO_FLAG);
        int promoteR = makeMove(from, to, capturedPiece, wR, NO_FLAG);
        int promoteN = makeMove(from, to, capturedPiece, wN, NO_FLAG);
        int promoteB = makeMove(from, to, capturedPiece, wB, NO_FLAG);

        addCaptureMove(board, promoteQ, moveList);
        addCaptureMove(board, promoteR, moveList);
        addCaptureMove(board, promoteN, moveList);
        addCaptureMove(board, promoteB, moveList);
    }
}

void generatePawnAndCastleMoves(Board &board, MOVELIST &moveList) {
    int side = board.side;

    if (side == WHITE) {
        for (int curPawn = 0; curPawn < board.numPieceOnBoard[wP]; curPawn++) {
            int curSq = board.pieceSq[wP][curPawn];
            assert(isSqOnBoard(curSq));
            if (board.squareToPiece[curSq + 10] == EMPTY) {
                addWhitePawnMove(board, curSq, moveList);
                if (sqToRank[curSq] == RANK_2 && board.squareToPiece[curSq + 20] == EMPTY) {
                    int move = makeMove(curSq, curSq + 20, EMPTY, EMPTY, PAWN_START_FLAG);
                    addQuietMove(board, move, moveList);
                }
            }
            if (isSqOnBoard(curSq + 9) &&
                pieceColor[board.squareToPiece[curSq + 9]] == BLACK) {
                addWhitePawnCaptureMove(board, curSq, curSq + 9, board.squareToPiece[curSq + 9], moveList);
            }
            if (isSqOnBoard(curSq + 11) &&
                pieceColor[board.squareToPiece[curSq + 11]] == BLACK) {
                addWhitePawnCaptureMove(board, curSq, curSq + 11, board.squareToPiece[curSq + 11], moveList);
            }
            if (board.enPasSq != NO_SQ) {
                if (curSq + 9 == board.enPasSq) {
                    int move = makeMove(curSq, curSq + 9, EMPTY, EMPTY, EN_PASSANT_FLAG);
                    addEnPassantMove(board, move, moveList);
                }
                if (curSq + 11 == board.enPasSq) {
                    int move = makeMove(curSq, curSq + 11, EMPTY, EMPTY, EN_PASSANT_FLAG);
                    addEnPassantMove(board, move, moveList);
                }
            }
        }
        if (board.castlePermission & WKCA) {
            if (board.squareToPiece[F1] == EMPTY && board.squareToPiece[G1] == EMPTY) {
                if (!isSqBeingAttacked(F1, BLACK, board) && !isSqBeingAttacked(G1, BLACK, board)) {
                    int move = makeMove(E1, G1, EMPTY, EMPTY, CASTLE_FLAG);
                    addQuietMove(board, move, moveList);
                }
            }
        }
        if (board.castlePermission & WQCA) {
            if (board.squareToPiece[D1] == EMPTY && board.squareToPiece[C1] == EMPTY && board.squareToPiece[B1] == EMPTY) {
                if (!isSqBeingAttacked(E1, BLACK, board) && !isSqBeingAttacked(D1, BLACK, board)) {
                    int move = makeMove(E1, C1, EMPTY, EMPTY, CASTLE_FLAG);
                    addQuietMove(board, move, moveList);
                }
            }
        }
    } else {
        for (int curPawn = 0; curPawn < board.numPieceOnBoard[bP]; curPawn++) {
            int curSq = board.pieceSq[bP][curPawn];
            assert(isSqOnBoard(curSq));
            if (board.squareToPiece[curSq - 10] == EMPTY) {
                addBlackPawnMove(board, curSq, moveList);
                if (sqToRank[curSq] == RANK_7 && board.squareToPiece[curSq - 20] == EMPTY) {
                    int move = makeMove(curSq, curSq - 20, EMPTY, EMPTY, PAWN_START_FLAG);
                    addQuietMove(board, move, moveList);
                }
            }
            if (isSqOnBoard(curSq - 9) && pieceColor[board.squareToPiece[curSq - 9]] == WHITE) {
                addBlackPawnCaptureMove(board, curSq, curSq - 9, board.squareToPiece[curSq - 9], moveList);
            }
            if (isSqOnBoard(curSq - 11) && pieceColor[board.squareToPiece[curSq - 11]] == WHITE) {
                addBlackPawnCaptureMove(board, curSq, curSq - 11, board.squareToPiece[curSq - 11], moveList);
            }
            if (board.enPasSq != NO_SQ) {
                if (curSq - 9 == board.enPasSq) {
                    int move = makeMove(curSq, curSq - 9, EMPTY, EMPTY, EN_PASSANT_FLAG);
                    addEnPassantMove(board, move, moveList);
                }
                if (curSq - 11 == board.enPasSq) {
                    int move = makeMove(curSq, curSq - 11, EMPTY, EMPTY, EN_PASSANT_FLAG);
                    addEnPassantMove(board, move, moveList);
                }
            }
        }
        if (board.castlePermission & BKCA) {
            if (board.squareToPiece[F8] == EMPTY && board.squareToPiece[G8] == EMPTY) {
                if (!isSqBeingAttacked(F8, WHITE, board) && !isSqBeingAttacked(G8, WHITE, board)) {
                    int move = makeMove(E8, G8, EMPTY, EMPTY, CASTLE_FLAG);
                    addQuietMove(board, move, moveList);
                }
            }
        }
        if (board.castlePermission & BQCA) {
            if (board.squareToPiece[D8] == EMPTY && board.squareToPiece[C8] == EMPTY && board.squareToPiece[B8] == EMPTY) {
                if (!isSqBeingAttacked(E8, WHITE, board) && !isSqBeingAttacked(D8, WHITE, board)) {
                    int move = makeMove(E8, C8, EMPTY, EMPTY, CASTLE_FLAG);
                    addQuietMove(board, move, moveList);
                }
            }
        }
    }
}
void generateSlidePieceMoves(Board &board, MOVELIST &moveList) {
    int side = board.side;
    int indexLoop = loopSlideIndex[side];
    int slidePiece = loopSlidePiece[indexLoop];

    while (slidePiece != 0) {
        assert(isPieceValid(slidePiece));
        int numberOfSlidePiece = board.numPieceOnBoard[slidePiece];

        for (int indexSlidePiece = 0; indexSlidePiece < numberOfSlidePiece; indexSlidePiece++) {
            int curSq = board.pieceSq[slidePiece][indexSlidePiece];
            assert(isSqOnBoard(curSq));

            for (int indexDir = 0; indexDir < numDir[slidePiece]; indexDir++) {
                int dir = pieceDir[slidePiece][indexDir];
                int nextSq = curSq + dir;

                while (isSqOnBoard(nextSq)) {
                    int piece = board.squareToPiece[nextSq];
                    if (piece == EMPTY) {
                        int move = makeMove(curSq, nextSq, EMPTY, EMPTY, NO_FLAG);
                        addQuietMove(board, move, moveList);
                        nextSq += dir;
                        continue;
                    }

                    if (pieceColor[piece] == (side^1)) {
                        int move = makeMove(curSq, nextSq, piece, EMPTY, NO_FLAG);
                        addCaptureMove(board, move, moveList);
                    }
                    break;
                }
            }
        }
        slidePiece = loopSlidePiece[++indexLoop];
    }
}
void generateNonSlidePieceMoves(Board &board, MOVELIST &moveList) {
    int side = board.side;
    int indexLoop = loopNonSlideIndex[side];
    int nonSlidePiece = loopNonSlidePiece[indexLoop];

    while (nonSlidePiece != 0) {
        assert(isPieceValid(nonSlidePiece));
        int numberOfNonSlidePiece = board.numPieceOnBoard[nonSlidePiece];

        for (int indexNonSlidePiece = 0; indexNonSlidePiece < numberOfNonSlidePiece; indexNonSlidePiece++) {
            int curSq = board.pieceSq[nonSlidePiece][indexNonSlidePiece];
            assert(isSqOnBoard(curSq));

            for (int indexDir = 0; indexDir < numDir[nonSlidePiece]; indexDir++) {
                int dir = pieceDir[nonSlidePiece][indexDir];
                int nextSq = curSq + dir;
                if (!isSqOnBoard(nextSq)) {
                    continue;
                }

                int piece = board.squareToPiece[nextSq];
                if (piece == EMPTY)
                {
                    int move = makeMove(curSq, nextSq, EMPTY, EMPTY, NO_FLAG);
                    addQuietMove(board, move, moveList);
                } else if (pieceColor[piece] == (side ^ 1)) {
                    int move = makeMove(curSq, nextSq, piece, EMPTY, NO_FLAG);
                    addCaptureMove(board, move, moveList);
                }
            }
        }
        nonSlidePiece = loopNonSlidePiece[++indexLoop];
    }
}

void generateAllMoves(Board &board, MOVELIST &moveList) {
    
}