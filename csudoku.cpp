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

cSudoku::cSudoku(const cSudoku &parent1,const cSudoku &parent2,const cSudoku &progenitor)
{
    instance++;
    ID = instance;
    // PL - Kopiowanie orginalnej pustej planszy do nowego potomstwa
    for(int i = 0; i< 9;i++)
    {
        for(int j = 0; j <9 ;j++)
        {
            grid[i][j] = progenitor.grid[i][j];
        }
    }
    //
    this->row_contains = progenitor.row_contains;
    this->orginal_row_contains = progenitor.row_contains;
    this->column_contains = progenitor.column_contains;
    this->orginal_column_contains = progenitor.column_contains;
    this->cell_contains = progenitor.cell_contains;
    this->orginal_cell_contains = progenitor.cell_contains;
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
    //
    if(CONSOLE_INFO) std::cout << "checkpoint1" << std::endl;
    //
    int tryof = 0;
    bool turn = 0; //0 - parents 1, 1 - parents 2
    const cSudoku * Parent;
    while(true)
    {
        if(turn == 0) Parent = &parent1;
        else Parent = &parent2;
        //
        while(true)
        {
            int empty_spaces_size = empty_spaces.size();
            //
            if(empty_spaces_size == 0) break;
            //
            int field = rand() % empty_spaces_size;
            //
            int i = std::get<0>(empty_spaces[field]);
            int j = std::get<1>(empty_spaces[field]);
            std::bitset<9> bs = std::get<2>(empty_spaces[field]);
            int tofill = Parent->grid[i][j];
            if(Parent->grid[i][j] != 0 && canbeset(i,j,tofill))
            {
                grid[i][j] = Parent->grid[i][j];
                deletefromemptyspaces(i,j,grid[i][j]);
                empty_spaces.erase(empty_spaces.begin()+field);
                turn = !turn;
                tryof = 0;
                break;
            }
            else
            {
                tryof++;
            }
            if(!bs.any()) break;
            if(tryof >= 300) break;
        }
        bool still = false;
        int empty_spaces_size = empty_spaces.size();
        for(int i = 0; i < empty_spaces_size; i++)
        {
            if(std::get<2>(empty_spaces[i]).any()) still = true;
        }
        if(still == false) break;
        if(tryof >= 300) break;
        //

        //
    }
    fillsudoku();
}

bool cSudoku::operator == (const cSudoku &other) const
{
    bool identical = true;
    //
    for(int i = 0; i <9 ;i++)
    {
        for(int j = 0; j < 9 ;j++)
        {
            if(this->grid[i][j] != other.grid[i][j] ) identical = false;
        }
    }
    //
    return identical;
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
    if(empty_spaces_size != 0)
    {
        std::cout << "empty_spaces: " << empty_spaces_size << std::endl;
        for(int i = 0; i < empty_spaces_size; i++)
        {
            std::cout << "i: " << std::get<0>(empty_spaces[i]) << "  " << "j: " << std::get<1>(empty_spaces[i]) << "  " << "result: " << std::get<2>(empty_spaces[i]) << std::endl;
        }
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
    int tryoftriger = 0;
    while(true)
    {
        int empty_spaces_size = empty_spaces.size();
        //
        if(empty_spaces_size == 0) break;
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
                tryof = 0;
                //
                break;
            }
            else tryof++;
            //
            if(tryof >= 1000)
            {
                tryoftriger++;
                break;
            }
        }
        //
        bool still = false;
        for(int i = 0; i < empty_spaces_size; i++)
        {
            if(std::get<2>(empty_spaces[i]).any()) still = true;
        }
        if(still == false) break;
        if(tryoftriger >= 2) break;
    }
    if(CONSOLE_INFO) this->drawsudoku();
}

