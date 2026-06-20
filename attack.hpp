#pragma once

#include "board.hpp"
constexpr int numKnDir = 8;
constexpr int numRkDir = 4;
constexpr int numBsDir = 4;
constexpr int numKiDir = 8;

constexpr std::array<int, numKnDir> KnDir = {-8, -19, -21, -12, 8, 19, 21, 12};
constexpr std::array<int, numRkDir> RkDir = {-1, 1, -10, 10};
constexpr std::array<int, numBsDir> BsDir = {-9, -11, 11, 9};
constexpr std::array<int, numKiDir> KiDir = {-9, -11, 11, 9, -1, 1, -10, 10};
bool isSqBeingAttacked(int sq, int side, Board& board);