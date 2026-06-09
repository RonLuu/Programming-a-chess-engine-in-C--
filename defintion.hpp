#pragma once

#include <array>
#include <bit>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string_view>

using U64 = unsigned long long;

enum { WHITE, BLACK, BOTH };
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 };
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK, NULL_PIECE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum
{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    NO_SQ, OFFBOARD
};

constexpr int NUM_OF_SIDE = 2;
constexpr int NUM_BIG_SQ = 120;
constexpr int NUM_SML_SQ = 64;
constexpr int NUM_UNIQUE_PIECE = 13;
constexpr int MAX_NUM_PIECE = 10;
constexpr int ILLEGAL_MOVE = 0;
constexpr int MAX_MOVE_GENERATED = 256;

constexpr int NO_FLAG         = 0;
constexpr int CAPTURE_FLAG    = 0x7C000;
constexpr int EN_PASSANT_FLAG = 0x40000;
constexpr int PAWN_START_FLAG = 0x80000;
constexpr int PROMOTE_FLAG    = 0xF00000;
constexpr int CASTLE_FLAG     = 0x1000000;

constexpr int pieceToValue[13] = {0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000};
constexpr int pieceColor[13] = {BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};

constexpr bool isPieceBig[13] = {false, false, true, true, true, true, true, false, true, true, true, true, true};
constexpr bool isPieceMaj[13] = {false, false, false, false, true, true, true, false, false, false, true, true, true};
constexpr bool isPieceMin[13] = {false, false, true, true, false, false, false, false, true, true, false, false, false};

constexpr bool isPawn[13] = {false, true,  false, false, false, false, false, true,  false, false, false, false, false};
constexpr bool isKnight[13] = {false, false, true,  false, false, false, false, false, true,  false, false, false, false};
constexpr bool isKing[13] = {false, false, false, false, false, false, true, false, false, false, false, false, true};
constexpr bool isRookQueen[13] = {false, false, false, false, true, true, false, false, false, false, true,  true, false};
constexpr bool isBishopQueen[13] = {false, false, false, true,  false, true, false, false, false, true,  false, true,  false};

constexpr bool isPieceSlidingPiece[13] = {false, false, false, true, true, true, false, false, false, true,  true, true, false};

constexpr std::string_view sideChar = "wb-";
constexpr std::string_view rankChar = "12345678";
constexpr std::string_view fileChar = "abcdefgh";
constexpr std::string_view pieceChar = ".PNBRQKpnbrqk";
constexpr std::string_view START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

struct UNDO {
    int move;
    int castlePermission;
    int enPasSq;
    int fiftyMove;
    U64 hashkey;
};

struct MOVE {
    int move;
    int score;
};

struct MOVELIST {
    std::array<MOVE, MAX_MOVE_GENERATED> moves;
    int currentSize = 0;
};

// init.c
extern int sq120To64[NUM_BIG_SQ];
extern int sq64To120[NUM_SML_SQ];
extern int sqToRank[NUM_BIG_SQ];
extern int sqToFile[NUM_BIG_SQ];
extern U64 setMask[NUM_SML_SQ];
extern U64 clrMask[NUM_SML_SQ];
extern U64 pieceHashKeys[NUM_UNIQUE_PIECE][NUM_BIG_SQ];
extern U64 sideHashKey;
extern U64 castleHashKeys[16];

void allInit();
void initSq120And64();
void initBitMasks();
void initHashKeys();
void initFileRankBrd();


constexpr int fileRankToSq(int file, int rank) {
    return rank * 10 + (file + 21);
}
constexpr bool isSqOnBoard(int sq) {
    return A1 <= sq && sq <= H8;
}
constexpr bool isPieceValid(int piece) {
    return wP <= piece && piece <= bK;
}
constexpr bool isSideValid(int side) {
    return (side == WHITE || side == BLACK);
}
constexpr int moveToFrom(int move) {
    return move & 0x7F;
}
constexpr int moveToTo(int move) {
    return (move >> 7) & 0x7F;
}
constexpr int moveToPromotedPiece(int move) {
    return (move >> 20) & 0xF;
}

inline int popBit(U64& bb) {
    int sq = std::countr_zero(bb);
    bb &= bb - 1;
    return sq;
}
inline void setBit(U64& bb, int sq) {
    bb |= setMask[sq];
}
inline void clrBit(U64& bb, int sq) {
    bb &= clrMask[sq];
}
