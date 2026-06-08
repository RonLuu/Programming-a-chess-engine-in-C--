#include "movegen.hpp"

void addQuietMove(Board& board, int move, MOVELIST& moveList) {
    int index = moveList.currentSize;
    (moveList.moves)[index].move = move;
    (moveList.moves)[index].score = 0;
    moveList.currentSize++;
}

void generateAllMoves(Board& board, MOVELIST& moveList) {
    
}