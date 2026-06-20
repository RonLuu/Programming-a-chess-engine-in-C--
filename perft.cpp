#include "perft.hpp"
#include "io.hpp"
#include "makemove.hpp"
#include "movegen.hpp"

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

void runPerftSuite(const std::string &filename, Board &board) {
    std::ifstream file(filename);
    std::string line;
    int testCount = 0;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        testCount++;
        if (testCount < 15) {
            continue;
        }
        std::cout << "Test " << testCount << std::endl;
        std::istringstream ss(line);
        std::string fen;
        std::getline(ss, fen, ';');

        parseFen(board, fen);

        std::string token;
        while (std::getline(ss, token, ';')) {
            std::istringstream ts(token);
            std::string depthStr;
            long expected;
            ts >> depthStr >> expected;
            
            int depth = std::stoi(depthStr.substr(1)); // strip 'D'
            if (depth != 5) {
                continue;
            }
            leafNode = 0;
            perft(board, depth);

            bool pass = leafNode == expected;
            std::cout << (pass ? "PASS" : "FAIL") << " depth " << depth
                      << " expected " << expected << " got " << leafNode
                      << "\n";
            if (!pass) {
                exit(1);
            }
        }
    }
}
