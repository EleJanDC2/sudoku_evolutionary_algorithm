#include "csudoku.h"
#include <iostream>
#include <fstream>
#include <string>

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

void cSudoku::loadsudoku()
{
    std::fstream file;
    //
    file.open("sudokuempty.txt",std::ios::in);
    //
    if(!file.is_open())
    {
        std::cout << "Unable to open file containing sudoku to solve" << std::endl;
        return;
    }
    //
    std::string line;

    for(int i = 0; i < 9; i++)
    {
        getline(file,line);
        for(int j = 0; j < 9; j++)
        {
            grid[i][j] = line[j] - 48; // From ascii to int
        }
    }

}
