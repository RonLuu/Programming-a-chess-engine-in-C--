#pragma once

#include "board.hpp"
#include <chrono>
#include "io.hpp"
#include "makemove.hpp"
#include "movegen.hpp"

extern long leafNode;

void perftTest(Board &board, int depth);