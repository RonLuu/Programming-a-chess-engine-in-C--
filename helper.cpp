#include "defintion.hpp"
#include <iostream>
#include <iomanip>
#include <bitset>

void print_120_converter() {
    for (int i = 0; i < NUM_BIG_SQ; i++)
    {
        std::cout << std::setw(4) << sq120To64[i];
        if (i % 10 == 9)
            std::cout << std::endl << std::endl;
    }
}

void print_64_converter() {
    for (int i = 0; i < NUM_SML_SQ; i++)
    {
        std::cout << std::setw(4) << sq64To120[i];
        if (i % 8 == 7)
            std::cout << std::endl << std::endl;
    }
}

void print_in_binary(U64 num) {
    std::cout << std::bitset<64>(num) << "\n";
}