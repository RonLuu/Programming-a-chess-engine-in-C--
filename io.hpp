#pragma once

#include "board.hpp"
#include "movegen.hpp"

std::string moveToStr(int move);

void parseFen(Board &board, std::string_view fen);
int parseMove(Board &board, std::string_view fen);
void printBoard(Board &board);
void printMoveList(MOVELIST &moveList);