#include "csudoku.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

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
    std::cout << std::endl;
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
    file.open("sudokuempty.txt",std::ios::in);
    if(!file.is_open())
    {
        std::cout << "Unable to open file containing sudoku to solve" << std::endl;
        return;
    }
    std::string line;
    for(int i = 0; i < 9; i++)
    {
        getline(file,line);
        for(int j = 0; j < 9; j++)
        {
            grid[i][j] = line[j] - 48;;
        }
    }
    file.close();
    //
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(grid[i][j] != 0)
            {
                row_contains[i].set(grid[i][j] - 1); // PL - wypełnienie row_contains
                orginal_row_contains[i].set(grid[i][j] - 1); // PL - wypełnienie orginal_row_contains
            }
        }
    }
    //
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(grid[j][i] != 0)
            {
                column_contains[i].set(grid[j][i] - 1); // PL - wypełnienie row_contains
                orginal_column_contains[i].set(grid[j][i] - 1); // PL - wypełnienie orginal_column_contains
            }
        }
    }
    //
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(grid[i][j] != 0)
            {
                int cell_number = (3 * int(i/3)) + int(j/3);
                cell_contains[cell_number].set(grid[i][j] - 1); // PL - wypełnienie row_contains
                orginal_cell_contains[cell_number].set(grid[i][j] - 1); // PL - wypełnienie orginal_column_contains
            }
        }
    }
    //
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(grid[i][j] == 0)
            {
                int cell_number = (3 * int(i/3)) + int(j/3);
                std::bitset<9> result = (row_contains[i] | column_contains[j] | cell_contains[cell_number]).flip();
                empty_spaces.push_back(std::tuple<int,int,std::bitset<9>>{i,j,result});
                std::cout << "i: " << i << "  " << "j: " << j << "  " << "result: " << result << std::endl;
            }
        }
    }
}

void cSudoku::deletefromemptyspaces(const int row,const int column,const int number)
{
    row_contains[row].set(number-1);
    column_contains[column].set(number-1);
    int cell_number = (3 * int(row/3)) + int(column/3);
    cell_contains[cell_number].set(number-1);
}

/*
void cSudoku::fillsudoku()
{
    while(true)
    {

    }
}
*/
