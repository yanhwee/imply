#include <vector>
#include <tuple>
#include "imply.h"
using namespace Imply;

namespace Sudoku
{
    using std::vector;
    using std::tuple;
    typedef unsigned char TSize;
    typedef unsigned short TSize2;
    typedef unsigned int TSize4;
    typedef unsigned long TSize8;
    class Solver
    {
    private:
        const TSize size;
        Engine engine;
    public:
        Solver(const Solver& other) = default;
        Solver& operator=(const Solver& other) = default;
        Solver(Solver&& other) = default;
        Solver& operator=(Solver&& other) = default;

        Solver(TSize size);
        bool solve(vector<tuple<TSize2,TSize2,TSize2>> rcnums, bool backtrack = false);
        void print(const vector<tuple<TSize2,TSize2,TSize2>>& number) const;
        void print() const;
    private:
        TSize8 index(TSize2 row, TSize2 col, TSize2 num) const noexcept;
        TSize2 get(TSize2 row, TSize2 col) const noexcept;
        void printDivider() const noexcept;
        void print(const vector<TSize2>& nums) const noexcept;
    };
};