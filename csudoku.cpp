#include "csudoku.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

cSudoku::cSudoku()
{
    instance++;
    ID = instance;
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
    int empty_spaces_size = empty_spaces.size();
    std::cout << "empty_spaces: " << empty_spaces_size << std::endl;
    for(int i = 0; i < empty_spaces_size; i++)
    {
        std::cout << "i: " << std::get<0>(empty_spaces[i]) << "  " << "j: " << std::get<1>(empty_spaces[i]) << "  " << "result: " << std::get<2>(empty_spaces[i]) << std::endl;
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
                //std::cout << "i: " << i << "  " << "j: " << j << "  " << "result: " << result << std::endl;
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
    for(auto && tuple : empty_spaces)
    {
        if(std::get<0>(tuple) == row)
        {
            std::get<2>(tuple).reset(number-1);
        }
        //
        if(std::get<1>(tuple) == column)
        {
            std::get<2>(tuple).reset(number-1);
        }
        //
        int cell_number_tested = (3 * int(std::get<0>(tuple)/3)) + int(std::get<1>(tuple)/3);
        if(cell_number_tested == cell_number)
        {
            std::get<2>(tuple).reset(number-1);
        }
    }
}

void cSudoku::fillsudoku()
{
    while(true)
    {
        int empty_spaces_size = empty_spaces.size();
        //
        int field = rand() % empty_spaces_size;

        int tryof = 0;
        //
        while(true)
        {
            int numbertofill = rand() % 9 + 1;
            std::bitset<9> hg = std::get<2>(empty_spaces[field]);
            if(!hg.any()) break;
            // std::cout << "numbertofill: " << numbertofill << "    " << "i: " << std::get<0>(empty_spaces[field]) << "    " << "j: " << std::get<1>(empty_spaces[field]) << std::endl;
            if(hg.test(numbertofill-1) && canbeset(std::get<0>(empty_spaces[field]),std::get<1>(empty_spaces[field]),numbertofill))
            {
                grid[std::get<0>(empty_spaces[field])][std::get<1>(empty_spaces[field])] = numbertofill;
                deletefromemptyspaces(std::get<0>(empty_spaces[field]),std::get<1>(empty_spaces[field]),numbertofill);
                //
                //Delete from empty_spaces.
                empty_spaces.erase(empty_spaces.begin()+field);
                //
                break;
            }
            else tryof++;
            //
            if(tryof >= 100)
            {
                std::cout << "EXIT IN fillsudoku()" << std::endl;
                exit(1);
            }
        }
        //
        bool still = false;
        for(int i = 0; i < empty_spaces_size; i++)
        {
            if(std::get<2>(empty_spaces[i]).any()) still = true;
        }
        if(still == false) break;
    }
    if(CONSOLE_INFO) this->drawsudoku();
}

