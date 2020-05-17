#include <vector>
#include <tuple>
#include <cmath>
#include <cassert>
#include "sudoku.h"
using std::vector;
using std::tuple;
using std::string;
using namespace Imply;
using namespace Sudoku;

Solver::Solver(TSize size)
    : size(size)
{
    const TSize2 size2 = size * size;

    vector<Link> links;
    links.reserve(2 * 4 * size2 * size2);
    vector<TNodeID> group(size2, 0);

    // Cell
    for (TSize2 row = 0; row < size2; row++) {
        for (TSize2 col = 0; col < size2; col++) {
            for (TSize2 num = 0; num < size2; num++) {
                group[num] = index(row, col, num);
            }
            links.push_back(Link({}, {}, GE, 0, group, {}, LE, 1));
            links.push_back(Link({}, {}, GE, 0, group, {}, GE, 1));
        }
    }
    // Box
    for (TSize brow = 0; brow < size; brow++) {
        for (TSize bcol = 0; bcol < size; bcol++) {
            for (TSize2 num = 0; num < size2; num++) {
                for (TSize brow2 = 0; brow2 < size; brow2++) {
                    for (TSize bcol2 = 0; bcol2 < size; bcol2++) {
                        group[brow2 * size + bcol2] = index(
                            brow * size + brow2, 
                            bcol * size + bcol2,
                            num);
                    }
                }
                links.push_back(Link({}, {}, GE, 0, group, {}, LE, 1));
                links.push_back(Link({}, {}, GE, 0, group, {}, GE, 1));
            }
        }
    }
    // Row
    for (TSize2 row = 0; row < size2; row++) {
        for (TSize2 num = 0; num < size2; num++) {
            for (TSize2 col = 0; col < size2; col++) {
                group[col] = index(row, col, num);
            }
            links.push_back(Link({}, {}, GE, 0, group, {}, LE, 1));
            links.push_back(Link({}, {}, GE, 0, group, {}, GE, 1));
        }
    }
    // Col
    for (TSize2 col = 0; col < size2; col++) {
        for (TSize2 num = 0; num < size2; num++) {
            for (TSize2 row = 0; row < size2; row++) {
                group[row] = index(row, col, num);
            }
            links.push_back(Link({}, {}, GE, 0, group, {}, LE, 1));
            links.push_back(Link({}, {}, GE, 0, group, {}, GE, 1));
        }
    }
    
    engine = Engine(std::move(links), index(size2, size2, size2) + 1);
}

bool Solver::solve(vector<tuple<TSize2,TSize2,TSize2>> rcnums, bool backtrack)
{
    vector<TNodeID> trueNodeIDs;
    trueNodeIDs.reserve(rcnums.size());
    for (auto [row, col, num] : rcnums)
        trueNodeIDs.push_back(index(row, col, num - 1));
    return (
        engine.constrain(trueNodeIDs, {}) && 
        (backtrack ? engine.backtrack() : true));
}

void Solver::print(const vector<tuple<TSize2,TSize2,TSize2>>& rcnums) const
{
    const TSize2 size2 = size * size;
    vector<TSize2> nums(size2 * size2, 0);

    for (auto [row, col, num] : rcnums)
        nums[row * size2 + col] = num;
    
    print(nums);
}

void Solver::print() const
{
    const TSize2 size2 = size * size;
    vector<TSize2> nums;
    nums.reserve(size2 * size2);

    for (TSize2 row = 0; row < size2; row++)
        for (TSize2 col = 0; col < size2; col++)
            nums.push_back(get(row, col));
    
    print(nums);
}

TSize8 Solver::index(TSize2 row, TSize2 col, TSize2 num) const noexcept
{
    const TSize2 size2 = size * size;
    return row * size2 * size2 + col * size2 + num;
}

TSize2 Solver::get(TSize2 row, TSize2 col) const noexcept
{
    for (TSize2 num = 0; num < size * size; num++) {
        if (engine.getNodeState(index(row, col, num)) == TRUE)
            return num + 1;
    }
    return 0;
}

void Solver::printDivider() const noexcept
{
    const TSize2 size2 = size * size;
    const TSize2 len = log10(size2) + 2;
    std::cout << "+";
    for (TSize bcol = 0; bcol < size; bcol++) {
        for (TSize bcol2 = 0; bcol2 < size; bcol2++) {
            for (TSize2 i = 0; i < len; i++)
                std::cout << "-";
        }
        std::cout << "-+";
    }
    std::cout << "\n";
}

void Solver::print(const vector<TSize2>& nums) const noexcept
{
    const TSize2 size2 = size * size;
    const TSize2 len = log10(size2) + 2;
    assert(nums.size() == size2 * size2);

    printDivider();
    vector<TSize2>::const_iterator numIter = nums.cbegin();
    for (TSize brow = 0; brow < size; brow++) {
        for (TSize brow2 = 0; brow2 < size; brow2++) {
            std::cout << "|";
            for (TSize bcol = 0; bcol < size; bcol++) {
                for (TSize bcol2 = 0; bcol2 < size; bcol2++) {
                    const TSize2 num = *(numIter++); assert(num >= 0);
                    const TSize2 numLen = num == 0 ? 1 : log10(num) + 1;
                    for (TSize2 space = 0; space < len - numLen; space++)
                        std::cout << " ";
                    std::cout << num;
                }
                std::cout << " |";
            }
            std::cout << "\n";
        }
        printDivider();
    }
}