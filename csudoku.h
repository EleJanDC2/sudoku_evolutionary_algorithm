#ifndef CSUDOKU_H
#define CSUDOKU_H


class cSudoku
{
public:
    int grid[9][9];
    cSudoku();
    bool canbeset(int row, int column, int number);
};

#endif // CSUDOKU_H
