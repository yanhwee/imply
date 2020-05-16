#include <iostream>
#include "imply.h"
using namespace std;
using namespace Imply;

int main(void)
{
    // Link link = Link({0,1}, {}, GE, 1, {2}, {}, GE, 1);
    vector<Link> links {
        {{0, 1}, {}, GE, 2, {2, 3}, {}, GE, 2}
    };

    int n = 4;
    Engine engine(std::move(links), n);

    cout << "Before:";
    for (int i = 0; i < n; i++) cout << " " << (int) engine.getNodeState(i);
    cout << "\n";

    bool retA = engine.constrain({
        {2, false}
    });

    bool retB = engine.backtrack();

    cout << "After:";
    for (int i = 0; i < n; i++) cout << " " << (int) engine.getNodeState(i);
    cout << "\n";

    cout << "RetA: " << retA << "\n";
    cout << "RetB: " << retB << "\n";
    return 0;
}