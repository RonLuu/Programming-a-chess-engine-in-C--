#include "board.hpp"
constexpr int numKnDir = 8;
constexpr int numRkDir = 4;
constexpr int numBsDir = 4;
constexpr int numKiDir = 8;

constexpr int KnDir[numKnDir] = {-8, -19, -21, -12, 8, 19, 21, 12};
constexpr int RkDir[numRkDir] = {-1, 1, -10, 10};
constexpr int BsDir[numBsDir] = {-9, -11, 11, 9};
constexpr int KiDir[numKiDir] = {-9, -11, 11, 9, -1, 1, -10, 10};
bool isSqBeingAttacked(int sq, int side, Board& board);