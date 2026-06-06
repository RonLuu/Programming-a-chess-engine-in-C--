#pragma once
using U64 = unsigned long long;

constexpr int NUM_BIG_SQ = 120;
constexpr int NUM_SML_SQ = 64;
constexpr int NUM_PIECE = 12;

constexpr int fileRankToSq(int file, int rank)
{
    return rank * 10 + (file + 21);
}


enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};

extern int sq120To64[NUM_BIG_SQ];
extern int sq64To120[NUM_SML_SQ];

// init.c
void allInit();
void initSq120And64();
void initBitMasks();
void initHashKeys();
void initFileRankBrd();