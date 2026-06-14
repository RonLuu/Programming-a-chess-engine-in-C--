#pragma once

#include "board.hpp"

std::string moveToStr(int move);

void parseFen(Board &board, std::string_view);
void printBoard(Board &board);
void printMoveList(MOVELIST &moveList);