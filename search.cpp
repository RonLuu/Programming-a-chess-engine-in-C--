#include "search.hpp"

bool isBoardRepeated(Board &board) {
    // Performance trick: start serach from the last fifty move was set
    for (int index = board.historyIndex - board.fiftyMove;
         index < board.historyIndex - 1; index++) {
        if (board.hashkey == board.history[index].hashkey) {
            return true;
        }
    }
    return false;
}