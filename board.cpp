#include "board.hpp"

std::string_view parsePosition(std::string_view fen, Board& board) {
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

std::string_view parseSide(std::string_view fen, Board& board) {
    assert(fen[0] == 'w' || fen[0] == 'b');
    board.side = (fen[0] == 'w') ? WHITE : BLACK;
    fen.remove_prefix(2);
    return fen;
}

std::string_view parseCastlePermission(std::string_view fen, Board& board) {
    for (int i = 0; i < 4; i++)
    {
        if (fen[0] == ' ') {
            break;
        }

        switch(fen[0]) {
            case 'K': board.castlePermission |= WKCA; break;
            case 'k': board.castlePermission |= BKCA; break;
            case 'Q': board.castlePermission |= WQCA; break;
            case 'q': board.castlePermission |= BQCA; break;
            default: break;
        }
        fen.remove_prefix(1);
    }
    fen.remove_prefix(1);

    assert(0 <= board.castlePermission && board.castlePermission <= 15);

    return fen;
}

std::string_view parseEnPassant(std::string_view fen, Board& board) {
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

void hashPieces(U64& key, Board&board) {
    for (int curSq = 0; curSq < NUM_SML_SQ; curSq++)
    {
        int sq120 = sq64To120[curSq];
        int curPiece = board.squareToPiece[sq120];
        if (curPiece != EMPTY && curPiece != NO_SQ && curPiece != OFFBOARD) {
            assert(wP <= curPiece && curPiece <= bK);
            key ^= pieceHashKeys[curPiece][sq120];
        }
    }
}

void hashSide(U64& key, Board& board) {
    if (board.side == WHITE) {
        key ^= sideHashKey;
    }
}

void hashEnPassant(U64& key, Board& board) {
    int enPasSq = board.enPasSq;
    if (enPasSq != NO_SQ) {
        assert(A1 <= enPasSq && enPasSq <= H8);
        assert(sqToRank[enPasSq] == RANK_3 || sqToRank[enPasSq] == RANK_6);
        key ^= pieceHashKeys[EMPTY][enPasSq];
    }
}

void hashCastlePerm(U64& key, Board& board) {
    assert(0 <= board.castlePermission && board.castlePermission <= 15);
    key ^= castleHashKeys[board.castlePermission];
}

void updateListMaterial(Board& board) {
    int curPiece;
    int color;

    for (int sq64 = 0; sq64 < NUM_SML_SQ; sq64++) {
        int sq120 = sq64To120[sq64];
        curPiece = board.squareToPiece[sq120];
        if (curPiece != EMPTY) {
            color = pieceColor[curPiece];

            if (isPieceBig[curPiece]) board.numBigPieces[color] ++;
            if (isPieceMaj[curPiece]) board.numMajPieces[color] ++;
            if (isPieceMin[curPiece]) board.numMinPieces[color] ++;

            board.materialPoints[color] += pieceToValue[curPiece];

            board.pieceSq[curPiece][board.numPieceOnBoard[curPiece]++] = sq120;

            if (curPiece == wK) board.kingSq[WHITE] = sq120;
            if (curPiece == bK) board.kingSq[BLACK] = sq120;

            if (curPiece == wP) {
                setBit(board.pawnBitboard[WHITE], sq64);
                setBit(board.pawnBitboard[BOTH], sq64);
            }
            else if (curPiece == bP) {
                setBit(board.pawnBitboard[BLACK], sq64);
                setBit(board.pawnBitboard[BOTH], sq64);
            }

        }
    }
}

U64 generateHashKey(Board&board) {
    U64 key = 0;
    hashPieces(key, board);
    hashSide(key, board);
    hashEnPassant(key, board);
    hashCastlePerm(key, board);
    return key;
}

void Board::printBoard() {
    int sq, file, rank, pieceIndex;
    printf("\nGame Board:\n");
    for (rank = RANK_8; rank >= RANK_1; rank--)
    {
        printf("%d ", rank+1);
        for (file = FILE_A; file <= FILE_H; file++)
        {
            sq = fileRankToSq(file, rank);
            pieceIndex = squareToPiece[sq];
            printf("%3c", pieceChar[pieceIndex]);
        }
        printf("\n");
    }

    printf("\n  ");
    for (file = FILE_A; file <= FILE_H; file++)
    {
        printf("%3c", 'a' + file);
    }
    printf("\n\n");
    printf("Side: %c\n", sideChar[side]);
    printf("EnPas: %d\n", enPasSq);
    printf("Castle: %c%c%c%c\n", 
        castlePermission & WKCA ? 'K' : '-', 
        castlePermission & WQCA ? 'Q' : '-', 
        castlePermission & BKCA ? 'k' : '-', 
        castlePermission & BQCA ? 'q' : '-');

    printf("HashKey: %llX\n\n", hashkey);
}

void Board::resetBoard() {
    // Set all the square to null piece
    for (int i = 0; i < NUM_BIG_SQ; i++)
    {
        squareToPiece[i] = NULL_PIECE;
    }
    
    // Set all the INNER square to empyt piece
    for (int i = 0; i < NUM_SML_SQ; i++)
    {
        int sq120 = sq64To120[i];
        squareToPiece[sq120] = EMPTY;
    }
    
    // Set all pawns bit positions to be zero
    // Add one for both
    for (int i = 0; i < NUM_OF_SIDE+1; i++)
    {
        pawnBitboard[i] = 0LL;
    }

    // Set all king positions to be off board
    for (int i = 0; i < NUM_OF_SIDE; i++)
    {
        kingSq[i] = NO_SQ;
    }

    side = BOTH;

    enPasSq = NO_SQ;

    fiftyMove = 0;

    ply = 0;
    
    historyIndex = 0;
    
    hashkey = 0LL;
    
    for (int i = 0; i < NUM_UNIQUE_PIECE; i++)
    {
        numPieceOnBoard[i] = 0;
    }
    
    castlePermission = 0;


    // Set all the number of all types of pieces to be 0
    // Set all material points to be 0
    for (int i = 0; i < NUM_OF_SIDE; i++)
    {
        numBigPieces[i] = 0;
        numMajPieces[i] = 0;
        numMinPieces[i] = 0;
        materialPoints[i] = 0;
    }

    for (int i = 0; i < NUM_UNIQUE_PIECE; i++)
    {
        for (int j = 0; j < MAX_NUM_PIECE; j++)
        {
            pieceSq[i][j] = NO_SQ;
        }
        
    }
}

void Board::parseFen(std::string_view fen) {
    resetBoard();

    fen = parsePosition(fen, *this);
    fen = parseSide(fen, *this);
    fen = parseCastlePermission(fen, *this);
    fen = parseEnPassant(fen, *this);

    hashkey = generateHashKey(*this);

    updateListMaterial(*this);
}