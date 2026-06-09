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

void generateAllMoves(Board &board, MOVELIST &moveList) {}