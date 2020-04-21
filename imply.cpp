#include <vector>
#include <memory>
#include <cassert>
#include "imply.h"
using std::vector;
using std::make_unique;
using namespace Imply;

Node::Node(const Node& other)
    : state(other.state),
      trueInLen(other.trueInLen), trueOutLen(other.trueOutLen),
      trueArray(make_unique<TLinkID[]>(trueInLen + trueOutLen)),
      falseInLen(other.falseInLen), falseOutLen(other.falseOutLen)
{
    TLinkID trueLen = trueInLen + trueOutLen;
    TLinkID falseLen = falseInLen + falseOutLen;
    trueArray = make_unique<TLinkID[]>(trueLen);
    falseArray = make_unique<TLinkID[]>(falseLen);
    std::copy(other.trueArray.get(), other.trueArray.get() + trueLen, trueArray.get());
    std::copy(other.falseArray.get(), other.falseArray.get() + falseLen, falseArray.get());
}

Node& Node::operator=(const Node& other)
{
    state = other.state;
    trueInLen = other.trueInLen; trueOutLen = other.trueOutLen;
    falseInLen = other.falseInLen; falseOutLen = other.falseOutLen;
    TLinkID trueLen = trueInLen + trueOutLen;
    TLinkID falseLen = falseInLen + falseOutLen;
    trueArray = make_unique<TLinkID[]>(trueLen);
    falseArray = make_unique<TLinkID[]>(falseLen);
    std::copy(other.trueArray.get(), other.trueArray.get() + trueLen, trueArray.get());
    std::copy(other.falseArray.get(), other.falseArray.get() + falseLen, falseArray.get());
    return *this;
}

Node::Node(Node&& other) noexcept
    : state(other.state),
      trueInLen(other.trueInLen), trueOutLen(other.trueOutLen),
      trueArray(std::move(other.trueArray)),
      falseInLen(other.falseInLen), falseOutLen(other.falseOutLen),
      falseArray(std::move(other.falseArray)) {}

Node& Node::operator=(Node&& other) noexcept
{
    state = other.state;
    trueInLen = other.trueInLen; trueOutLen = other.trueOutLen;
    trueArray = std::move(other.trueArray);
    falseInLen = other.falseInLen; falseOutLen = other.falseOutLen;
    falseArray = std::move(other.falseArray);
    return *this;
}

Node::Node()
    : state(MAYBE),
      trueInLen(0), trueOutLen(0), trueArray(),
      falseInLen(0), falseOutLen(0), falseArray() {}

Node::Node(
    const vector<TLinkID>& trueInLinks, const vector<TLinkID>& trueOutLinks,
    const vector<TLinkID>& falseInLinks, const vector<TLinkID>& falseOutLinks)
    : state(MAYBE),
      trueInLen(trueInLinks.size()), trueOutLen(trueOutLinks.size()),
      falseInLen(falseInLinks.size()), falseOutLen(falseOutLinks.size())
{
    TLinkID trueLen = trueInLen + trueOutLen;
    TLinkID falseLen = falseInLen + falseOutLen;
    trueArray = make_unique<TLinkID[]>(trueLen);
    falseArray = make_unique<TLinkID[]>(falseLen);
    std::copy(trueInLinks.cbegin(), trueInLinks.cend(), trueArray.get());
    std::copy(trueOutLinks.cbegin(), trueOutLinks.cend(), trueArray.get() + trueInLen);
    std::copy(falseInLinks.cbegin(), falseInLinks.cend(), falseArray.get());
    std::copy(falseOutLinks.cbegin(), falseOutLinks.cend(), falseArray.get() + falseInLen);
}

Link::Link(const Link& other)
    : inCount(other.inCount), outCount(other.outCount),
      inLimitA(other.inLimitA), outLimitA(other.outLimitA),
      trueOutLen(other.trueOutLen), falseOutLen(other.falseOutLen),
      inLimitB(other.inLimitB), outLimitB(other.outLimitB),
      trueInLen(other.trueInLen), falseInLen(other.falseInLen)
{
    TNodeID outLen = trueOutLen + falseOutLen;
    TNodeID inLen = trueInLen + falseInLen;
    outArray = make_unique<TNodeID[]>(outLen);
    inArray = make_unique<TNodeID[]>(inLen);
    std::copy(other.outArray.get(), other.outArray.get() + outLen, outArray.get());
    std::copy(other.inArray.get(), other.inArray.get() + inLen, inArray.get());
}

Link& Link::operator=(const Link& other)
{
    inCount = other.inCount; outCount = other.outCount;
    inLimitA = other.inLimitA; outLimitA = other.outLimitA;
    trueOutLen = other.trueOutLen; falseOutLen = other.falseOutLen;
    inLimitB = other.inLimitB; outLimitB = other.outLimitB;
    trueInLen = other.trueInLen; falseInLen = other.falseInLen;
    TNodeID outLen = trueOutLen + falseOutLen;
    TNodeID inLen = trueInLen + falseInLen;
    outArray = make_unique<TNodeID[]>(outLen);
    inArray = make_unique<TNodeID[]>(inLen);
    std::copy(other.outArray.get(), other.outArray.get() + outLen, outArray.get());
    std::copy(other.inArray.get(), other.inArray.get() + inLen, inArray.get());
    return *this;
}

Link::Link(Link&& other) noexcept
    : inCount(other.inCount), outCount(other.outCount),
      inLimitA(other.inLimitA), outLimitA(other.outLimitA),
      trueOutLen(other.trueOutLen), falseOutLen(other.falseOutLen),
      outArray(std::move(other.outArray)),
      inLimitB(other.inLimitB), outLimitB(other.outLimitB),
      trueInLen(other.trueInLen), falseInLen(other.falseInLen),
      inArray(std::move(other.inArray)) {}

Link& Link::operator=(Link&& other) noexcept
{
    inCount = other.inCount; 
    outCount = other.outCount;
    inLimitA = other.inLimitA; 
    outLimitA = other.outLimitA;
    trueOutLen = other.trueOutLen; 
    falseOutLen = other.falseOutLen;
    outArray = std::move(other.outArray);    
    inLimitB = other.inLimitB;
    outLimitB = other.outLimitB;
    trueInLen = other.trueInLen;
    falseInLen = other.falseInLen;
    inArray = std::move(other.inArray);
    return *this;
}

Link::Link()
    : inCount(0), outCount(0),
      inLimitA(0), outLimitA(0),
      trueOutLen(0), falseOutLen(0), outArray(),
      inLimitB(0), outLimitB(0),
      trueInLen(0), falseInLen(0), inArray() {}

Link::Link(
    const vector<TNodeID>& trueInNodes, 
    const vector<TNodeID>& falseInNodes,
    Equality inEquality, TNodeID inLimit,
    const vector<TNodeID>& trueOutNodes, 
    const vector<TNodeID>& falseOutNodes,
    Equality outEquality, TNodeID outLimit)
    : inCount(0), outCount(0)
{
    // Conditional
    TNodeID inLen = trueInNodes.size() + falseInNodes.size();
    Link::inArray = make_unique<TNodeID[]>(inLen);
    if (inEquality & IS_GREATER) {
        Link::trueInLen = trueInNodes.size();
        Link::falseInLen = falseInNodes.size();
        std::copy(trueInNodes.cbegin(), trueInNodes.cend(), Link::inArray.get());
        std::copy(falseInNodes.cbegin(), falseInNodes.cend(), Link::inArray.get() + Link::trueInLen);
    } else {
        Link::trueInLen = falseInNodes.size();
        Link::falseInLen = trueInNodes.size();
        std::copy(falseInNodes.cbegin(), falseInNodes.cend(), Link::inArray.get());
        std::copy(trueInNodes.cbegin(), trueInNodes.cend(), Link::inArray.get() + Link::falseInLen);
        inLimit = inLen - inLimit;
    }
    if (!(inEquality & IS_EQUAL)) inLimit += 1;
    Link::inLimitA = inLimit;
    Link::inLimitB = (inLen - Link::inLimitA) + 1;
    // Contrapositive
    TNodeID outLen = trueOutNodes.size() + falseOutNodes.size();
    Link::outArray = make_unique<TNodeID[]>(outLen);
    if (!(outEquality & IS_GREATER)) {
        Link::trueOutLen = trueOutNodes.size();
        Link::falseOutLen = falseOutNodes.size();
        std::copy(trueOutNodes.cbegin(), trueOutNodes.cend(), Link::outArray.get());
        std::copy(falseOutNodes.cbegin(), falseOutNodes.cend(), Link::outArray.get() + Link::trueOutLen);
    } else {
        Link::trueOutLen = falseOutNodes.size();
        Link::falseOutLen = trueOutNodes.size();
        std::copy(falseOutNodes.cbegin(), falseOutNodes.cend(), Link::outArray.get());
        std::copy(trueOutNodes.cbegin(), trueOutNodes.cend(), Link::outArray.get() + Link::falseOutLen);
        outLimit = outLen - outLimit;
    }
    if (!(outEquality & IS_EQUAL)) outLimit += 1;
    Link::outLimitA = outLimit;
    Link::outLimitB = Link::outLimitA + 1;
}

bool Link::isJustConditional() const
{
    bool g_e = inCount > inLimitA && outCount == outLimitA;
    bool e_ge = inCount == inLimitA && outCount >= outLimitA;
    return g_e || e_ge;
}

bool Link::isJustContrapositive() const
{
    bool g_e = inCount > inLimitB && outCount == outLimitB;
    bool e_ge = inCount == inLimitB && outCount >= outLimitB;
    return g_e || e_ge;
}

bool Link::isJustNotConditional() const
{
    bool l_e = inCount < inLimitA && outCount == outLimitA;
    bool e_le = inCount == inLimitA && outCount <= outLimitA;
    return l_e && e_le;
}

bool Link::isJustNotContrapositive() const
{
    bool l_e = inCount < inLimitB && outCount == outLimitB;
    bool e_le = inCount == inLimitB && outCount <= outLimitB;
    return l_e && e_le;
}

Engine::Engine()
    : nodeVector(), linkVector(),
      nodeIDArray(),
      nodeIDArrayPtrEnd(nodeIDArray.get() + nodeVector.size()),
      trueNodeIDPtr(nodeIDArray.get()),
      falseNodeIDPtr(nodeIDArrayPtrEnd)  {}

Engine::Engine(const Engine& other)
    : nodeVector(other.nodeVector),
      linkVector(other.linkVector)
{
    nodeIDArray = make_unique<TNodeID[]>(nodeVector.size());
    nodeIDArrayPtrEnd = nodeIDArray.get() + (other.nodeIDArray.get() - other.nodeIDArrayPtrEnd);
    trueNodeIDPtr = nodeIDArray.get() + (other.nodeIDArray.get() - other.trueNodeIDPtr);
    falseNodeIDPtr = nodeIDArray.get() + (other.nodeIDArray.get() - other.falseNodeIDPtr);
    std::copy(other.nodeIDArray.get(), other.trueNodeIDPtr, nodeIDArray.get());
    std::copy(other.falseNodeIDPtr, other.nodeIDArrayPtrEnd, falseNodeIDPtr);
}

Engine& Engine::operator=(const Engine& other)
{
    nodeVector = other.nodeVector;
    linkVector = other.linkVector;
    nodeIDArray = make_unique<TNodeID[]>(nodeVector.size());
    nodeIDArrayPtrEnd = nodeIDArray.get() + (other.nodeIDArray.get() - other.nodeIDArrayPtrEnd);
    trueNodeIDPtr = nodeIDArray.get() + (other.nodeIDArray.get() - other.trueNodeIDPtr);
    falseNodeIDPtr = nodeIDArray.get() + (other.nodeIDArray.get() - other.falseNodeIDPtr);
    std::copy(other.nodeIDArray.get(), other.trueNodeIDPtr, nodeIDArray.get());
    std::copy(other.falseNodeIDPtr, other.nodeIDArrayPtrEnd, falseNodeIDPtr);

    return *this;
}

Engine::Engine(Engine&& other) noexcept
    : nodeVector(std::move(other.nodeVector)),
      linkVector(std::move(other.linkVector)),
      nodeIDArray(std::move(other.nodeIDArray)),
      nodeIDArrayPtrEnd(other.nodeIDArrayPtrEnd),
      trueNodeIDPtr(other.trueNodeIDPtr),
      falseNodeIDPtr(other.falseNodeIDPtr) {}

Engine& Engine::operator=(Engine&& other) noexcept
{
    nodeVector = std::move(other.nodeVector);
    linkVector = std::move(other.linkVector);
    nodeIDArray = std::move(other.nodeIDArray);
    nodeIDArrayPtrEnd = other.nodeIDArrayPtrEnd;
    trueNodeIDPtr = other.trueNodeIDPtr;
    falseNodeIDPtr = other.falseNodeIDPtr;
    return *this;
}

template<typename L, typename N>
Engine::Engine(L&& links, N&& nodes)
    : linkVector(links),
      nodeVector(nodes),
      nodeIDArray(nodeVector.size()) {}

template<typename L>
Engine::Engine(L&& links, TNodeID nodeSize)
    : linkVector(links),
      nodeVector(nodeSize),
      nodeIDArray(nodeVector.size())
{
    // Find Lengths
    for (const Link& link : linkVector) {
        const TNodeID* inPtr = link.inArray.get();
        const TNodeID* outPtr = link.outArray.get();
        for (const TNodeID* trueInPtr = inPtr + link.trueInLen; inPtr < trueInPtr; inPtr++)
            nodeVector[*inPtr].trueInLen++;
        for (const TNodeID* falseInPtr = inPtr + link.falseInLen; inPtr < falseInPtr; inPtr++)
            nodeVector[*inPtr].falseInLen++;
        for (const TNodeID* trueOutPtr = outPtr + link.trueOutLen; outPtr < trueOutPtr; outPtr++)
            nodeVector[*outPtr].trueOutLen++;
        for (const TNodeID* falseOutPtr = outPtr + link.falseOutLen; outPtr < falseOutPtr; outPtr++)
            nodeVector[*outPtr].falseOutLen++;
    }
    for (Node& node : nodeVector) {
        // Allocate Array
        node.trueArray = make_unique<TLinkID[]>(node.trueInLen + node.trueOutLen);
        node.falseArray = make_unique<TLinkID[]>(node.falseInLen + node.falseOutLen);
        // Lengths as Indices
        node.trueOutLen = node.trueInLen;
        node.falseOutLen = node.falseInLen;
        node.trueInLen = 0;
        node.falseInLen = 0;
    }
    // Fill Array
    for (TLinkID i = 0; i < linkVector.size(); i++) {
        const Link& link = linkVector[i];
        const TNodeID* inPtr = link.inArray.get();
        const TNodeID* outPtr = link.outArray.get();
        for (const TNodeID* trueInPtr = inPtr + link.trueInLen; inPtr < trueInPtr; inPtr++) {
            Node& node = nodeVector[*inPtr];
            node.trueArray[node.trueInLen++] = i;
        }
        for (const TNodeID* falseInPtr = inPtr + link.falseInLen; inPtr < falseInPtr; inPtr++) {
            Node& node = nodeVector[*inPtr];
            node.falseArray[node.falseInLen++] = i;
        }
        for (const TNodeID* trueOutPtr = outPtr + link.trueOutLen; outPtr < trueOutPtr; outPtr++) {
            Node& node = nodeVector[*outPtr];
            node.trueArray[node.trueOutLen++] = i;
        }
        for (const TNodeID* falseOutPtr = outPtr + link.falseOutLen; outPtr < falseOutPtr; outPtr++) {
            Node& node = nodeVector[*outPtr];
            node.falseArray[node.falseOutLen++] = i;
        }
    }
    // Indices to Lengths
    for (Node& node : nodeVector) {
        node.trueOutLen -= node.trueInLen;
        node.falseOutLen -= node.falseInLen;
    }
}

void Engine::selfAssert(bool strong) {
    if (strong) {
        assert(nodeVector.size() == nodeVector.capacity());
        assert(linkVector.size() == linkVector.capacity());
    }
    // assert(trueNodeIDPtr == nodeIDArray.get());
    // assert(falseNodeIDPtr == nodeIDArray.get() + nodeVector.size());
}

// bool Engine::constrain(const TNodeID nodeID, const State state, const bool reset)
// {
//     int _debug = 0;
//     bool _reset = reset;
//     while (true) {
//         if (!updateNode(nodeID, state, _reset)) return false;
//         while (true) {
//             for ( ; trueNodeIDPtr >= nodeIDArray.get(); trueNodeIDPtr--)
//                 if (!updateNodeArray(*trueNodeIDPtr, TRUE, _reset)) break;

//             if (!(falseNodeIDPtr < nodeIDArrayPtrEnd)) return reset == _reset;

//             for ( ; falseNodeIDPtr < nodeIDArrayPtrEnd; falseNodeIDPtr++)
//                 if (!updateNodeArray(*falseNodeIDPtr, FALSE, _reset)) break;

//             if (!(trueNodeIDPtr >= nodeIDArray.get())) return reset == _reset;
//         }
//         _reset = !_reset;
//         assert(_debug++ == 0);
//     }
// }

// Bug to fix:
// If someone called on this function param reset with true and then with false
// Functions are meant to be self contained!
// However this creates a problem with backtrack as memory is allocated and freed too easily
bool Engine::constrain(const TNodeID nodeID, const State state, const bool reset)
{
    TNodeID* truePtrStart = trueNodeIDPtr;
    TNodeID* truePtr = truePtrStart;
    if (!updateNode(nodeID, state, reset)) return false;
    TNodeID* falsePtrStart = falseNodeIDPtr;
    TNodeID* falsePtr = falsePtrStart;

    while (true) {
        for ( ; truePtr < trueNodeIDPtr; truePtr++) {
            if (!updateNodeArray(*truePtr, TRUE, reset, true)) {
                for ( ; truePtr >= truePtrStart; truePtr--) {
                    updateNodeArray(*truePtr, TRUE, !reset, false);
                }
                trueNodeIDPtr--;
                for ( ; trueNodeIDPtr >= truePtrStart; trueNodeIDPtr--) {
                    if (reset)
                        nodeVector[*truePtr].state = TRUE;
                    else
                        nodeVector[*truePtr].state = MAYBE;
                }
                trueNodeIDPtr++;
                return false;
            }
        }
        if (!(falsePtr >= falseNodeIDPtr)) break;

        for ( ; falsePtr >= falseNodeIDPtr; falsePtr--) {
            if (!updateNodeArray(*falsePtr, FALSE, reset, true)) {
                for ( ; falsePtr < falsePtrStart; falsePtr--) {
                    updateNodeArray(*falsePtr, FALSE, !reset, false);
                }
                for ( ; falseNodeIDPtr < falsePtrStart; falseNodeIDPtr--) {
                    if (reset)
                        nodeVector[*falsePtr].state = FALSE;
                    else
                        nodeVector[*falsePtr].state = MAYBE;
                }
                return false;
            }
        }
        if (!(truePtr < trueNodeIDPtr)) break;
    }

    trueNodeIDPtr = trueNodeIDPtr + 1;
    falseNodeIDPtr = falseNodeIDPtr - 1;
    return true;
}

bool Engine::backtrack()
{
    for (TNodeID* ptr = nodeIDArray.get(); ptr < nodeIDArrayPtrEnd; ) {
        const Node& node = nodeVector[*ptr];
        if (node.state != MAYBE) continue;
        if (constrain(*ptr, TRUE, false) || constrain(*ptr, FALSE, false)) {
            ptr++;            
        } else {
            ptr--;
        }
    }
    return true;
}

bool Engine::updateNodeArray(const TNodeID nodeID, const State state, const bool reset, const bool propagate)
{
    assert(state == TRUE || state == FALSE);
    const Node& node = nodeVector[nodeID];
    if (state == TRUE)
        return updateNodeArray(node.trueArray, node.trueInLen, node.trueOutLen, reset, propagate);
    else
        return updateNodeArray(node.falseArray, node.falseInLen, node.falseOutLen, reset, propagate);
}

bool Engine::updateNodeArray(const unique_ptr<TLinkID[]>& nodeArray, const TLinkID inLen, const TLinkID outLen, const bool reset, const bool propagate)
{
    TLinkID* ptr = nodeArray.get();
    for (TLinkID* inPtr = ptr + inLen; ptr < inPtr; ptr++)
        if (!updateLink(*ptr, IN, reset, propagate) && propagate) return false;
    for (TLinkID* outPtr = ptr + outLen; ptr < outPtr; ptr++)
        if (!updateLink(*ptr, OUT, reset, propagate) && propagate) return false;
    return true;
}

bool Engine::updateLink(const TLinkID linkID, const Side side, const bool reset, const bool propagate) {
    assert(side == IN || side == OUT);
    Link& link = linkVector[linkID];
    if (side == IN) {
        if (reset)
            link.inCount--;
        else
            link.inCount++;
    } else {
        if (reset)
            link.outCount--;
        else
            link.outCount++;
    }
    return propagate ? updateLinkArray(link, reset) : true;
}

bool Engine::updateLinkArray(const Link& link, const bool reset)
{
    if (reset) {
        if (link.isJustNotConditional())
            return updateLinkArray(link.outArray, link.trueOutLen, link.falseOutLen, reset);
        else if (link.isJustNotContrapositive())
            return updateLinkArray(link.inArray, link.trueInLen, link.falseInLen, reset);
    } else {
        if (link.isJustConditional())
            return updateLinkArray(link.outArray, link.trueOutLen, link.falseOutLen, reset);
        else if (link.isJustContrapositive())
            return updateLinkArray(link.inArray, link.trueInLen, link.falseInLen, reset);
    }
    return true;
}

bool Engine::updateLinkArray(const unique_ptr<TNodeID[]>& linkArray, const TNodeID trueLen, const TNodeID falseLen, const bool reset)
{
    const TNodeID* ptr = linkArray.get();
    for (const TNodeID* truePtr = ptr + trueLen; ptr < truePtr; ptr++)
        if (!updateNode(*ptr, TRUE, reset)) return false;
    for (const TNodeID* falsePtr = ptr + falseLen; ptr < falsePtr; ptr++)
        if (!updateNode(*ptr, FALSE, reset)) return false;
    return true;
}

bool Engine::updateNode(const TNodeID nodeID, const State state, const bool reset)
{
    assert(state == TRUE || state == FALSE);
    Node& node = nodeVector[nodeID];
    if (node.state == (1 - state)) return false;
    bool checkState, newState;
    if (reset) {
        checkState = state;
        newState = MAYBE;
    } else {
        checkState = MAYBE;
        newState = state;
    }
    if (node.state == checkState) {
        node.state = newState;
        if (state == TRUE)
            *(trueNodeIDPtr++) = nodeID;
        else
            *(--falseNodeIDPtr) = nodeID;
    }
    return true;
}