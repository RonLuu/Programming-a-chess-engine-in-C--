#include "movegen.hpp"

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