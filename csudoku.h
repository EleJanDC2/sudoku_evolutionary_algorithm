#ifndef CSUDOKU_H
#define CSUDOKU_H


class cSudoku
{
public:
    int grid[9][9];
    cSudoku();
    bool canbeset(const int row,const int column,const int number);
};

#endif // CSUDOKU_H
