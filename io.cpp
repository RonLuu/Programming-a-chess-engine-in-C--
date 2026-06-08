#include "io.hpp"

int parseMove(std::string_view input, Board& board) {
    if (input[0] > 'h' || input[0] < 'a') return false;
    if (input[1] > '8' || input[1] < '1') return false;
    if (input[2] > 'h' || input[2] < 'a') return false;
    if (input[3] > '8' || input[3] < '1') return false;

    int from = fileRankToSq(input[0] - 'a', input[1] - '1');
    int to   = fileRankToSq(input[2] - 'a', input[3] - '1');

    std::cout << "Move: " << input << " From: " << from << " To: " << to;
    assert(isSqOnBoard(from) && isSqOnBoard(to));

    MOVELIST moveList;
    // generateAllMoves(board, moveList);
}