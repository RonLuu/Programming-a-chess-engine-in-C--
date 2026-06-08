#include "defintion.hpp"
#include "board.hpp"
#include "io.hpp"
#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1q/PPPBBPPP/R3K2R w KQkq - 0 1"

int main() {
    allInit();
    Board board;
    board.parseFen(FEN4);
    board.printBoard();
    std::string input;

    // while (true) {
    //     board.printBoard();
    //     std::cout << "Please enter a move" << std::endl;
    //     std::cin >> input;

    //     if (input[0] == 'q') {
    //         break;
    //     } else if (input[0] == 't') {
    //         // takeMove(board);
    //     } else if (input[0] == 'p') {
    //         // perftTest(4, board);
    //         // max = getPvLine(4, board);
    //         // printf("Pv line of %d moves: ", max);
    //         // for (int pvNum = 0; pvNum < max; pvNum++)
    //         // {
    //         //     move = board->pvArray[pvNum];
    //         //     printf("%s  ", moveToStr(move));
    //         // }
    //         std::cout << "\n";
    //     } else {
    //         // move = parseMove(input, board);
    //         // if (move == ILLEGAL_MOVE) {
    //         //     std::cout << "Illegal move!" << std::endl;
    //         // } else {
    //         //     // storePvMove(board, move);
    //         //     // makeMove(board, move)
    //         // }
    //     }
    // }
    
}