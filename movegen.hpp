#include "board.hpp"
#include "attack.hpp"

constexpr int makeMove(int from, int to, int captured, int promoted, int FLAG) {
    return from | (to << 7) | (captured << 14) | (promoted << 20) | FLAG;
}

void generateAllMoves(Board& board, MOVELIST& moveList);