#include "csudoku.h"
#include <iostream>

cSudoku::cSudoku()
{

}

bool cSudoku::canbeset(const int row,const int column,const int number)
{
    bool canbesetbool = true;
    //
    if(number < 1 || number > 9) canbesetbool = false;
    //
    for(int i = 0; i < 9; i++)
    {
        if(grid[row][i] == number) canbesetbool = false;
    }
    //
    for(int i = 0; i < 9; i++)
    {
        if(grid[i][column] == number) canbesetbool = false;
    }
    //
    return canbesetbool;
}

void cSudoku::drawsudoku()
{
    std::cout << "--------------------------------------------------";
    //
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    //
    std::cout << "--------------------------------------------------";
}
