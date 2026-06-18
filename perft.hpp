#pragma once

#include "board.hpp"
#include "io.hpp"
#include "makemove.hpp"
#include "movegen.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

extern long leafNode;

void perftTest(Board &board, int depth);
void runPerftSuite(const std::string &filename, Board &board);