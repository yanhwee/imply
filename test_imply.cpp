#include <iostream>
#include "imply.h"
using namespace std;
using namespace Imply;

int main(void)
{
    // Link link = Link({0,1}, {}, GE, 1, {2}, {}, GE, 1);
    vector<Link> links {
        {{}, {}, GE, 0, {0,1,2}, {}, GE, 1}
    };

    int n = 3;
    Engine engine(std::move(links), n);

    cout << "Before:";
    for (int i = 0; i < n; i++) cout << " " << (int) engine.getNodeState(i);
    cout << "\n";

    bool retA = engine.constrain({
        {0, false},
        {1, false}
    });

    // bool retB = engine.backtrack();

    cout << "After:";
    for (int i = 0; i < n; i++) cout << " " << (int) engine.getNodeState(i);
    cout << "\n";

    cout << "RetA: " << retA << "\n";
    // cout << "RetB: " << retB << "\n";
    return 0;
}