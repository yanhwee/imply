#include <iostream>
#include "imply.h"
using namespace std;
using namespace Imply;

int main(void)
{
    // Link link = Link({0,1}, {}, GE, 1, {2}, {}, GE, 1);
    vector<Link> links {
        {{0, 1}, {}, GE, 1, {2}, {}, GE, 1}
    };

    Engine engine(std::move(links), (TNodeID) 3);

    cout << "Before: " << (int)engine.getNodeState(0) << " " << (int)engine.getNodeState(1) << "\n";

    bool ret = engine.constrain({
        {2, false}
        // {2, false}
    });

    cout << "After: " << (int)engine.getNodeState(0) << " " << (int)engine.getNodeState(1) << "\n";

    cout << "Ret" << ret << "\n";
    return 0;
}