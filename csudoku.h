#ifndef CSUDOKU_H
#define CSUDOKU_H

#include <array>
#include <bitset>
#include <vector>
#include <tuple>

class cSudoku
{
public:
    int grid[9][9];
    std::vector<std::tuple<int,int,std::bitset<9>>> empty_spaces;
    //std::vector<std::array<int,2>> empty_spaces;
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
    void deletefromemptyspaces(const int row,const int column,const int number);
    void fillsudoku();
    // void fillsudoku();
};

#endif // CSUDOKU_H
