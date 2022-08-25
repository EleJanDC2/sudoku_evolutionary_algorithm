#include <iostream>
#include <cstdlib>
#include <time.h>
#include "csudoku.h"
#include <algorithm>

#define POPULATION 400
#define BESTOFPOPULATION 20
#define MAXGENERATION 15

void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
    system("clear");
#endif
}

//PL - Inicjalizacja zmiennych statycznych
std::array<std::bitset<9>,9> cSudoku::orginal_row_contains = {};
std::array<std::bitset<9>,9> cSudoku::orginal_column_contains = {};
std::array<std::bitset<9>,9> cSudoku::orginal_cell_contains = {};
int cSudoku::instance = 0;

int main()
{
    srand(time(0));
    //
    int family = 0;
    int generation = 0;
    //
    while(true)
    {
        family++;
        generation = 1;
        //
        Clear();
        std::cout << "FAMILY: " << family << std::endl;
        //
        cSudoku firstparents;
        firstparents.loadsudoku();
        std::vector<cSudoku> seriesofsudokuparents;
        std::vector<cSudoku> seriesofsudokuchildren;
        seriesofsudokuparents.clear();
        seriesofsudokuchildren.clear();
        //
        for(int i =0; i < POPULATION; i++)
        {
            seriesofsudokuchildren.push_back(firstparents);
            seriesofsudokuchildren[i].fillsudoku();
        }
        //
        std::sort(seriesofsudokuchildren.begin(),seriesofsudokuchildren.end());
        seriesofsudokuparents = seriesofsudokuchildren;
        //
        int tryof = 0;
        while(true)
        {
            generation++;
            //
            int individuals = 0;
            bool flag = true;
            bool populationcreation = true;
            seriesofsudokuchildren.clear();
            //
            while(flag)
            {
                int i = rand() % BESTOFPOPULATION;
                int j = rand() % BESTOFPOPULATION;
                tryof++;
                if(i != j && flag == true && !(seriesofsudokuparents[i] == seriesofsudokuparents[j]))
                {
                    individuals++;
                    cSudoku child(seriesofsudokuparents[i],seriesofsudokuparents[j],firstparents);
                    seriesofsudokuchildren.push_back(child);
                    //
                    tryof = 0;
                    if(individuals >= POPULATION) flag = false;
                }
                if(tryof >= 300)
                {
                    populationcreation = false;
                    flag = false;
                }
            }

            if(populationcreation)
            {
                std::sort(seriesofsudokuchildren.begin(),seriesofsudokuchildren.end());
                //

                if(seriesofsudokuchildren[0].empty_spaces.size() == 0)
                {
                    std::cout << "ZNALEZIONO ROZWIAZANIE: " << std::endl;
                    std::cout << "RODZINA: " << family << std::endl;
                    std::cout << "GENERACJA: " << generation << std::endl;
                    seriesofsudokuchildren[0].drawsudoku();
                    exit(1);
                }
                else
                {
                    //                std::cout << "SZUKANIE ROZWIAZANIA: " << std::endl;
                    //                std::cout << "RODZINA: " << family << std::endl;
                    //                std::cout << "GENERACJA: " << generation << std::endl;

                }
                //
                seriesofsudokuparents.clear();
                seriesofsudokuparents = seriesofsudokuchildren;
                //
                if(generation >= MAXGENERATION) break;
            }
            else
            {
                seriesofsudokuparents.clear();
                break;
            }
        }
    }
    return 0;
}








//std::cout << "GENERATION " << generation << ": " << std::endl;
