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


void generateAllMoves(Board& board, MOVELIST& moveList) {
    
}