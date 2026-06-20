#include "defintion.hpp"
#include "init.hpp"
#include "board.hpp"
#include "io.hpp"
#include "movegen.hpp"
#include "makemove.hpp"
#include "perft.hpp"
#include "pvtable.hpp"
#include "search.hpp"

constexpr std::string_view curFen = "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N w - - 0 1";

int main() {
    allInit();
    Board board;
    MOVELIST moveList;
    
    parseFen(board, START_FEN);
    char input[6];
    int max = 0;
    int move = NO_MOVE;
    while(true) {
        printBoard(board);
        std::cout << "Please enter a move > ";
        std::cin.getline(input, 6);

        if (input[0] == 'q') {
            break;
        } else if (input[0] == 't') {
            takeMove(board);
            continue;
        } else if (input[0] == 'p') {
            // perftTest(board, 4);
            max = board.pvTable.getPVSequence(board, 4);
            std::cout << "PV squences of " << max << " moves: ";
            for (int pvNum = 0; pvNum < max; pvNum++)
            {
                move = board.pvSequence[pvNum];
                std::cout << " " << moveToStr(move);
            }
            std::cout << std::endl;
        } else {
            int move = parseMove(board, input);
            if (move != NO_MOVE) {
                board.pvTable.store(board.hashkey, move);
                makeMove(board, move);
                if (isBoardRepeated(board)) {
                    std::cout << "I've seen this before" << std::endl;
                } else {
                    
                }
            } else {
                std::cout << "Move was not parsed" << std::endl;
            }
        }
        fflush(stdin);
    }
}