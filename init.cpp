// A file to initialise the game
#include "defintion.hpp"
// #include "helper.hpp"
#include <iostream>
#include <bitset>
#include <random>

int sq120To64[NUM_BIG_SQ];
int sq64To120[NUM_SML_SQ];

int sqToRank[NUM_BIG_SQ];
int sqToFile[NUM_BIG_SQ];

U64 setMask[NUM_SML_SQ];
U64 clrMask[NUM_SML_SQ];

U64 pieceHashKeys[NUM_PIECE][NUM_BIG_SQ];
U64 sideHashKey;
U64 castleHashKeys[16];

std::mt19937_64 rng(std::random_device{}());

void allInit() {
    initSq120And64();
    initBitMasks();
    initHashKeys();
    initFileRankBrd();
}

void initSq120And64() {
    int index_64 = 0;

    for (int i = 0; i < NUM_BIG_SQ; i ++) {
        sq120To64[i] = NUM_SML_SQ;
    }

    for (int rank = RANK_1; rank <= RANK_8; rank++) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            int index_120 = fileRankToSq(file, rank);
            sq120To64[index_120] = index_64;
            sq64To120[index_64] = index_120;
            index_64++;
        }
    }
}

void initBitMasks() {
    for (int index = 0; index < NUM_SML_SQ; index++) {
        setMask[index] = 0ULL;
        clrMask[index] = 0ULL;
    }
    
    for (int index = 0; index < NUM_SML_SQ; index++) {
        setMask[index] |= (1ULL << index);
        clrMask[index] |= ~(1ULL << index);
    }
}

void initHashKeys() {
    for (int p = 0; p < NUM_PIECE; p++)
    {
        for (int sq = 0; sq < NUM_BIG_SQ; sq++)
        {
            pieceHashKeys[p][sq] = rng();
        }
    }

    sideHashKey = rng();
    for (int index = 0; index < 16; index++)
    {
        castleHashKeys[index] = rng();
    }
}

void initFileRankBrd() {
    for (int i = 0; i < NUM_BIG_SQ; i++)
    {
        sqToRank[i] = RANK_NONE;
        sqToFile[i] = FILE_NONE;
    }
    
    for (int i = 0; i < NUM_BIG_SQ; i++)
    {
        int sq64 = sq120To64[i];
        if (sq64 != NUM_SML_SQ) {
            sqToRank[i] = sq64 / 8;
            sqToFile[i] = sq64 % 8;
        }
    }        
}