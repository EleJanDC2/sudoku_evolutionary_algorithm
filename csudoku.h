#ifndef CSUDOKU_H
#define CSUDOKU_H

#include <array>
#include <bitset>

class cSudoku
{
public:
    int grid[9][9];
    int empty_spaces = 81;
    static std::array<std::bitset<9>,9> orginal_row_contains;
    static std::array<std::bitset<9>,9> orginal_column_contains;
    static std::array<std::bitset<9>,9> orginal_cell_contains;
    std::array<std::bitset<9>,9> row_contains;
    std::array<std::bitset<9>,9> column_contains;
    std::array<std::bitset<9>,9> cell_contains;
    cSudoku();
    bool canbeset(const int row,const int column,const int number);
    void drawsudoku();
    void loadsudoku();
    // void fillsudoku();
};

#endif // CSUDOKU_H
