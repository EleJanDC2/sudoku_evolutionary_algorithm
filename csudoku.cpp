#include "csudoku.h"

cSudoku::cSudoku()
{

}

bool cSudoku::canbeset(int row, int column,int number)
{
    bool canbesetbool = true;
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
