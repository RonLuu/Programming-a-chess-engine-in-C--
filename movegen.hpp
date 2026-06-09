#include "board.hpp"
#include "attack.hpp"

constexpr int loopSlidePiece[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0};
constexpr int loopSlideIndex[2] = {0, 4};

constexpr int numDir[13] = {0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};

constexpr int pieceDir[13][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {-8, -19, -21, -12, 8, 19, 21, 12}, // Knight direction
    {-9, -11, 11, 9, 0, 0, 0, 0},       // Bishop direction
    {-1, -10, 1, 10, 0, 0, 0, 0},       // Rook direction
    {-1, -10, 1, 10, -9, -11, 11, 9},   // Queen direction
    {-1, -10, 1, 10, -9, -11, 11, 9},   // King direction
    {0, 0, 0, 0, 0, 0, 0, 0},
    {-8, -19, -21, -12, 8, 19, 21, 12}, // Knight direction
    {-9, -11, 11, 9, 0, 0, 0, 0},       // Bishop direction
    {-1, -10, 1, 10, 0, 0, 0, 0},       // Rook direction
    {-1, -10, 1, 10, -9, -11, 11, 9},   // Queen direction
    {-1, -10, 1, 10, -9, -11, 11, 9},   // King direction
};

constexpr int makeMove(int from, int to, int captured, int promoted, int FLAG) {
    return from | (to << 7) | (captured << 14) | (promoted << 20) | FLAG;
}

void generateAllMoves(Board& board, MOVELIST& moveList);