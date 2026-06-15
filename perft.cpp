#include "perft.hpp"

long leafNode = 0;

void perft(Board &board, int depth) {
    assert(board.checkBoard());

    if (depth == 0) {
        leafNode++;
        return;
    }

    MOVELIST moveList;
    generateAllMoves(board, moveList);

    for (int moveNum = 0; moveNum < moveList.currentSize; moveNum++) {
        int move = moveList.moves[moveNum].move;
        if (!makeMove(board, move)) continue;

        perft(board, depth - 1);
        takeMove(board);
    }
}

void perftTest(Board &board, int depth) {
    assert(board.checkBoard());

    printBoard(board);
    std::cout << "\nStarting Test To Depth: " << depth << std::endl;
    leafNode = 0;
    auto start = std::chrono::steady_clock::now();

    MOVELIST moveList;
    generateAllMoves(board, moveList);

    for (int moveNum = 0; moveNum < moveList.currentSize; moveNum++) {
        int move = moveList.moves[moveNum].move;
        if (!makeMove(board, move)) continue;

        long cumulativeNode = leafNode;
        perft(board, depth-1);
        takeMove(board);

        long oldNode = leafNode - cumulativeNode;
        std::cout << "Move " << moveNum+1 << " : " << moveToStr(move) << " : " << oldNode << std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "\nTest Complete : "<< leafNode << " nodes visited in "<< elapsed <<" ms\n";
}