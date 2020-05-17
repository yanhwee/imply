#include <iostream>
#include <vector>
#include <tuple>
#include "sudoku.h"
using std::vector;
using std::tuple;
using Sudoku::TSize2;

int main(void)
{
    Sudoku::Solver sudoku(3);
    vector<tuple<TSize2,TSize2,TSize2>> nums {
        // {0, 2, 8}, {0, 4, 9}, {0, 6, 4}, {1, 0, 3}, {1, 2, 2}, {1, 3, 7}, {1, 4, 6}, {2, 0, 1}, {2, 4, 2}, {2, 8, 8}, {3, 0, 6}, {3, 7, 2}, {4, 4, 1}, {5, 0, 2}, {5, 3, 8}, {5, 5, 3}, {6, 3, 5}, {6, 6, 8}, {6, 8, 7}, {7, 3, 6}, {7, 8, 4}, {8, 1, 7}, {8, 4, 8}, {8, 5, 9}, {8, 8, 5}
        // {0,4,9},{1,5,5},{1,8,8},{2,3,8},{2,4,3},{2,6,4},{2,7,9},{2,8,6},{3,2,5},{3,7,6},{4,3,4},{4,6,1},{4,7,8},{5,0,9},{5,1,2},{5,5,1},{6,0,6},{6,7,3},{7,3,2},{7,7,4},{8,0,5},{8,3,6},{8,5,3}
        {0,0,8},
        {1,2,3},{1,3,6},
        {2,1,7},{2,4,9},{2,6,2},
        {3,1,5},{3,5,7},
        {4,4,4},{4,5,5},{4,6,7},
        {5,3,1},{5,7,3},
        {6,2,1},{6,7,6},{6,8,8},
        {7,2,8},{7,3,5},{7,7,1},
        {8,1,9},{8,6,4}
    };
    sudoku.print(nums);
    bool ret = sudoku.solve(nums, true);
    std::cout << "Ret: " << ret << "\n";
    sudoku.print();
    return 0;
}