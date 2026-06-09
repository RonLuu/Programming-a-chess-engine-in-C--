#include "io.hpp"

void printBoard(Board &board) {
    std::cout << "\nGame Board:\n";

    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        std::cout << rank + 1 << " ";
        for (int file = FILE_A; file <= FILE_H; file++) {
            int sq120 = fileRankToSq(file, rank);
            int curPiece = board.squareToPiece[sq120];
            std::cout << std::setw(3) << pieceChar[curPiece];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "  ";
    for (int file = FILE_A; file <= FILE_H; file++) {
        std::cout << std::setw(3) << static_cast<char>('a' + file);
    }

    std::cout << std::endl << std::endl;
    std::cout << "Side: " << sideChar[board.side] << std::endl;
    std::cout << "EnPas: " << board.enPasSq << std::endl;
    std::cout << "Castle: " << (board.castlePermission & WKCA ? 'K' : '-')
              << (board.castlePermission & WQCA ? 'Q' : '-')
              << (board.castlePermission & BKCA ? 'k' : '-')
              << (board.castlePermission & BQCA ? 'q' : '-') << std::endl;
    std::cout << "HashKey: " << std::hex << std::uppercase << board.hashkey
              << std::dec << std::endl
              << std::endl;
}