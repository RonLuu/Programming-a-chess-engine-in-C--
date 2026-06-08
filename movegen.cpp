#include "movegen.hpp"

constexpr int makeMove(int from, int to, int captured, int promoted, int FLAG) {
    return from | (to << 7) | (captured << 14) | (promoted << 20) | FLAG;
}

void addCaptureMove(Board& board, int move, MOVELIST& moveList) {
    int index = moveList.currentSize;
    (moveList.moves)[index].move = move;
    (moveList.moves)[index].score = 0;
    moveList.currentSize++;
}
void addEnPassantMove(Board& board, int move, MOVELIST& moveList) {
    int index = moveList.currentSize;
    (moveList.moves)[index].move = move;
    (moveList.moves)[index].score = 0;
    moveList.currentSize++;
}
void addQuietMove(Board& board, int move, MOVELIST& moveList) {
    int index = moveList.currentSize;
    (moveList.moves)[index].move = move;
    (moveList.moves)[index].score = 0;
    moveList.currentSize++;
}
// Add an extra rule for promotion
void addWhitePawnMove(Board& board, int from, MOVELIST& moveList) {
    int to = from + 10;

    assert(isSqOnBoard(from));
    assert(isSqOnBoard(to));

    if (sqToRank[from] != RANK_7) {
        int move = makeMove(from, to, EMPTY, EMPTY, 0);
        addQuietMove(board, move, moveList);
    } else {
        int promoteQ = makeMove(from, to, EMPTY, wQ, 0);
        int promoteR = makeMove(from, to, EMPTY, wR, 0);
        int promoteN = makeMove(from, to, EMPTY, wN, 0);
        int promoteB = makeMove(from, to, EMPTY, wB, 0);

        addQuietMove(board, promoteQ, moveList);
        addQuietMove(board, promoteR, moveList);
        addQuietMove(board, promoteN, moveList);
        addQuietMove(board, promoteB, moveList);
    }
}


void generateAllMoves(Board& board, MOVELIST& moveList) {

    
}