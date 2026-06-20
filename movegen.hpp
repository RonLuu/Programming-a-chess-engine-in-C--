#pragma once

#include "board.hpp"

constexpr std::array<int, 8> loopSlidePiece = {wB, wR, wQ, 0, bB, bR, bQ, 0};
constexpr std::array<int, 2> loopSlideIndex = {0, 4};

constexpr std::array<int, 6> loopNonSlidePiece = {wN, wK, 0, bN, bK, 0};
constexpr std::array<int, 2> loopNonSlideIndex = {0, 3};

constexpr std::array<int, 13> numDir = {0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};

constexpr std::array<std::array<int, 8>, 13> pieceDir = {{
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
}};

constexpr int createMove(int from, int to, int captured, int promoted, int FLAG) {
    return from | (to << 7) | (captured << 14) | (promoted << 20) | FLAG;
}

void generateAllMoves(Board& board, MOVELIST& moveList);
bool isMoveValid(Board &board, int move);