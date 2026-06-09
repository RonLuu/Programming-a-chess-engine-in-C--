#include "io.hpp"

std::string_view parsePosition(std::string_view fen, Board &board) {
    int rank = RANK_8;
    int file = FILE_A;
    int curPiece = 0;
    int emptySq = 0;
    while (rank >= RANK_1 && !fen.empty()) {
        // Read the current character
        switch (fen[0]) {
        case 'r':
            curPiece = bR;
            break;
        case 'n':
            curPiece = bN;
            break;
        case 'b':
            curPiece = bB;
            break;
        case 'q':
            curPiece = bQ;
            break;
        case 'k':
            curPiece = bK;
            break;
        case 'p':
            curPiece = bP;
            break;
        case 'R':
            curPiece = wR;
            break;
        case 'N':
            curPiece = wN;
            break;
        case 'B':
            curPiece = wB;
            break;
        case 'Q':
            curPiece = wQ;
            break;
        case 'K':
            curPiece = wK;
            break;
        case 'P':
            curPiece = wP;
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            curPiece = EMPTY;
            emptySq = fen[0] - '0';
            break;
        case '/':
            rank--;
            file = FILE_A;
            fen.remove_prefix(1);
            continue;
        case ' ':
            fen.remove_prefix(1);
            return fen;
        default:
            std::cout << "FEN error" << std::endl;
            exit(-1);
        }

        // Place a piece on the board
        if (curPiece != EMPTY) {
            int sq120 = sq64To120[rank * 8 + file];
            board.squareToPiece[sq120] = curPiece;
            file++;
        } else {
            for (int curCol = 0; curCol < emptySq; curCol++) {
                file++;
            }
        }

        fen.remove_prefix(1);
    }

    return fen;
}
std::string_view parseSide(std::string_view fen, Board &board) {
    assert(fen[0] == 'w' || fen[0] == 'b');
    board.side = (fen[0] == 'w') ? WHITE : BLACK;
    fen.remove_prefix(2);
    return fen;
}
std::string_view parseCastlePermission(std::string_view fen, Board &board) {
    for (int i = 0; i < 4; i++) {
        if (fen[0] == ' ') {
            break;
        }

        switch (fen[0]) {
        case 'K':
            board.castlePermission |= WKCA;
            break;
        case 'k':
            board.castlePermission |= BKCA;
            break;
        case 'Q':
            board.castlePermission |= WQCA;
            break;
        case 'q':
            board.castlePermission |= BQCA;
            break;
        default:
            break;
        }
        fen.remove_prefix(1);
    }
    fen.remove_prefix(1);

    assert(0 <= board.castlePermission && board.castlePermission <= 15);

    return fen;
}
std::string_view parseEnPassant(std::string_view fen, Board &board) {
    int rank;
    int file;
    if (fen[0] != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        assert(FILE_A <= file && file <= FILE_H);
        assert(RANK_1 <= rank && rank <= RANK_8);

        board.enPasSq = fileRankToSq(file, rank);
    }
    fen.remove_prefix(1);
    return fen;
}

void parseFen(Board &board, std::string_view fen) {
    board.resetBoard();

    fen = parsePosition(fen, board);
    fen = parseSide(fen, board);
    fen = parseCastlePermission(fen, board);
    fen = parseEnPassant(fen, board);

    board.hashkey = board.generateHashKey();

    board.updateListMaterial();
}

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