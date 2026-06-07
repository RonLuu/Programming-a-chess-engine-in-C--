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

void checkMaterialPoint(Board& board) {
    std::array<int,2> materialPointsCounter = {0, 0};
    for (int sq64 = 0; sq64 < NUM_SML_SQ; sq64++) {
        int sq120 = sq64To120[sq64];
        int curPiece = board.squareToPiece[sq120];
        int colour = pieceColor[curPiece];
        materialPointsCounter[colour] += pieceToValue[curPiece];
    }

    assert(materialPointsCounter[WHITE] == board.materialPoints[WHITE] && 
           materialPointsCounter[BLACK] == board.materialPoints[BLACK]);
}
void checkNumberOfPiece(Board& board) {
    std::array<int, 13>piece_counter = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int curSq = 0; curSq < NUM_SML_SQ; curSq++) {
        int sq120 = sq64To120[curSq];
        int curPiece = board.squareToPiece[sq120];
        piece_counter[curPiece] ++;
    }

    for (int i = 0; i < NUM_UNIQUE_PIECE; i++) {
        assert(piece_counter[i] == board.numPieceOnBoard[i]);
    }
}
void checkNumberOfSpecialPiece(Board& board) {
    std::array<int,2> bigPiecesCounter = {0, 0};
    std::array<int,2> majPiecesCounter = {0, 0};
    std::array<int,2> minPiecesCounter = {0, 0};

    for (int curSq = 0; curSq < NUM_SML_SQ; curSq++) {
        int sq120 = sq64To120[curSq];
        int curPiece = board.squareToPiece[sq120];
        int color = pieceColor[curPiece];

        if (isPieceBig[curPiece]) bigPiecesCounter[color]++; 
        if (isPieceMaj[curPiece]) majPiecesCounter[color]++; 
        if (isPieceMin[curPiece]) minPiecesCounter[color]++; 
    }

    assert(bigPiecesCounter[WHITE] == board.numBigPieces[WHITE] && bigPiecesCounter[BLACK] == board.numBigPieces[BLACK]);
    assert(majPiecesCounter[WHITE] == board.numMajPieces[WHITE] && majPiecesCounter[BLACK] == board.numMajPieces[BLACK]);
    assert(minPiecesCounter[WHITE] == board.numMinPieces[WHITE] && minPiecesCounter[BLACK] == board.numMinPieces[BLACK]);
    
}
void checkPiecePosition(Board& board) {
    for (int curPiece = wP; curPiece <= bK; curPiece++) {
        for (int pieceIndex = 0; pieceIndex < board.numPieceOnBoard[curPiece]; pieceIndex++) {
            int sq120 = board.pieceSq[curPiece][pieceIndex];
            assert(board.squareToPiece[sq120] == curPiece);   
        }
    }
}
void checkPawnBit(Board& board) {
    U64 whiteBit = board.pawnBitboard[WHITE];
    U64 blackBit = board.pawnBitboard[BLACK]; 
    U64 bothBit  = board.pawnBitboard[BOTH];

    int whiteBitCount = std::popcount(whiteBit);
    int blackBitCount = std::popcount(blackBit);
    int bothBitCount  = std::popcount(bothBit);
    
    assert(whiteBitCount == board.numPieceOnBoard[wP]);
    assert(blackBitCount == board.numPieceOnBoard[bP]);
    assert(bothBitCount == board.numPieceOnBoard[wP] + board.numPieceOnBoard[bP]);


    while (whiteBit) {
        int sq64 = popBit(whiteBit);
        assert(board.squareToPiece[sq64To120[sq64]] == wP);
    }

    while (blackBit) {
        int sq64 = popBit(blackBit);
        assert(board.squareToPiece[sq64To120[sq64]] == bP);
    }
    
    while (bothBit) {
        int sq64 = popBit(bothBit);
        assert(board.squareToPiece[sq64To120[sq64]] == bP ||
               board.squareToPiece[sq64To120[sq64]] == wP);
    }
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
        assert(isSqOnBoard(enPasSq));
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

void Board::checkBoard() {
    checkPiecePosition(*this);
    checkNumberOfPiece(*this);
    checkNumberOfSpecialPiece(*this);
    checkMaterialPoint(*this);
    checkPawnBit(*this);
}

void Board::printBoard() {
    std::cout << "\nGame Board:\n";
    
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        std::cout << rank + 1 << " ";
        for (int file = FILE_A; file <= FILE_H; file++) {
            int sq120 = fileRankToSq(file, rank);
            int curPiece = squareToPiece[sq120];
            std::cout << std::setw(3) << pieceChar[curPiece];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "  ";
    for (int file = FILE_A; file <= FILE_H; file++) {
        std::cout << std::setw(3) << static_cast<char>('a' + file);
    }

    std::cout << std::endl << std::endl;
    std::cout << "Side: " << sideChar[side] << std::endl;
    std::cout << "EnPas: " << enPasSq << std::endl;
    std::cout << "Castle: "
              << (castlePermission & WKCA ? 'K' : '-')
              << (castlePermission & WQCA ? 'Q' : '-')
              << (castlePermission & BKCA ? 'k' : '-')
              << (castlePermission & BQCA ? 'q' : '-')
              << std::endl;
    std::cout << "HashKey: " << std::hex << std::uppercase << hashkey << std::dec << std::endl << std::endl;
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
