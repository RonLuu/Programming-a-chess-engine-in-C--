#include "defintion.hpp"
#include "board.hpp"

int main() {
    allInit();
    Board board;
    board.parseFen(START_FEN);
    board.printBoard();
}