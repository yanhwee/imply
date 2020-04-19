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

Node::Node(Node&& other)
    : state(other.state),
      trueInLen(other.trueInLen), trueOutLen(other.trueOutLen),
      trueArray(std::move(other.trueArray)),
      falseInLen(other.falseInLen), falseOutLen(other.falseOutLen),
      falseArray(std::move(other.falseArray)) {}

Node& Node::operator=(Node&& other)
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

Link::Link(Link&& other)
    : inCount(other.inCount), outCount(other.outCount),
      inLimitA(other.inLimitA), outLimitA(other.outLimitA),
      trueOutLen(other.trueOutLen), falseOutLen(other.falseOutLen),
      outArray(std::move(other.outArray)),
      inLimitB(other.inLimitB), outLimitB(other.outLimitB),
      trueInLen(other.trueInLen), falseInLen(other.falseInLen),
      inArray(std::move(other.inArray)) {}

Link& Link::operator=(Link&& other)
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
      falseNodeIDPtr(nodeIDArrayPtrEnd) {}

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

Engine::Engine(Engine&& other)
    : nodeVector(std::move(other.nodeVector)),
      linkVector(std::move(other.linkVector)),
      nodeIDArray(std::move(other.nodeIDArray)),
      nodeIDArrayPtrEnd(other.nodeIDArrayPtrEnd),
      trueNodeIDPtr(other.trueNodeIDPtr),
      falseNodeIDPtr(other.falseNodeIDPtr) {}

Engine& Engine::operator=(Engine&& other)
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
      nodeIDVector(nodes.size()) {}

template<typename L>
Engine::Engine(L&& links, TNodeID nodeSize)
    : linkVector(links),
      nodeVector(nodeSize),
      nodeIDVector(nodes.size())
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
        node.trueArray = make_unique<TLink[]>(node.trueInLen + node.trueOutLen);
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
    assert(trueNodeIDPtr == nodeIDArray.get());
    assert(falseNodeIDPtr == nodeIDArray.get() + nodeVector.size());
}

void Engine::constrain(TNodeID nodeID, State state)
{
    while (true) {
        for ( ; trueNodeIDPtr >= nodeIDArray.get(); trueNodeIDPtr--) {
            updateNodeArray(*trueNodeIDPtr, TRUE);
        }
        if (!(falseNodeIDPtr < nodeIDArrayPtrEnd)) break;
        for ( ; falseNodeIDPtr < nodeIDArrayPtrEnd; falseNodeIDPtr++) {
            updateNodeArray(*falseNodeIDPtr, FALSE);
        }
        if (!(trueNodeIDPtr >= nodeIDArray.get())) break;
    }
}

void Engine::updateNodeArray(const TNodeID nodeID, State state)
{
    assert(state == TRUE || state == FALSE);
    const Node& node = nodeVector[nodeID];
    if (state == TRUE)
        updateNodeArray(node.trueArray, node.trueInLen, node.trueOutLen);
    else if (state == FALSE)
        updateNodeArray(node.falseArray, node.falseInLen, node.falseOutLen);
}

void Engine::resetNodeArray(const TNodeID nodeID, State state)
{
    assert(state == TRUE || state == FALSE);
    const Node& node = nodeVector[nodeID];
    if (state == TRUE)
        resetNodeArray(node.trueArray, node.trueInLen, node.trueOutLen);
    else if (state == FALSE)
        resetNodeArray(node.falseArray, node.falseInLen, node.falseOutLen);
}

void Engine::updateNodeArray(const unique_ptr<TLinkID[]>& nodeArray, const TLinkID inLen, const TLinkID outLen)
{
    TLinkID* ptr = nodeArray.get();
    for (TLinkID* inPtr = ptr + inLen; ptr < inPtr; ptr++)
        updateLink(*ptr, IN);
    for (TLinkID* outPtr = ptr + outLen; ptr < outPtr; ptr++)
        updateLink(*ptr, OUT);
}

void Engine::resetNodeArray(const unique_ptr<TLinkID[]>& nodeArray, const TLinkID inLen, const TLinkID outLen)
{
    TLinkID* ptr = nodeArray.get();
    for (TLinkID* inPtr = ptr + inLen; ptr < inPtr; ptr++)
        resetLink(*ptr, IN);
    for (TLinkID* outPtr = ptr + outLen; ptr < outPtr; ptr++)
        resetLink(*ptr, OUT);
}

void Engine::updateLink(const TLinkID linkID, Side side) {
    assert(side == IN || side == OUT);
    Link& link = linkVector[linkID];
    if (side == IN)
        link.inCount++;
    else if (side == OUT)
        link.outCount++;
    updateLinkArray(link);
}

void Engine::resetLink(const TLinkID linkID, Side side)
{
    assert(side == IN || side == OUT);
    Link& link = linkVector[linkID];
    if (side == IN)
        link.inCount--;
    else if (side == OUT)
        link.outCount--;
    resetLinkArray(link);
}

void Engine::updateLinkArray(const Link& link)
{
    if (link.isJustConditional())
        updateLinkArray(link.outArray, link.trueOutLen, link.falseOutLen);
    else if (link.isJustContrapositive())
        updateLinkArray(link.inArray, link.trueInLen, link.falseInLen);
}

void Engine::resetLinkArray(const Link& link)
{
    if (link.isJustNotConditional())
        resetLinkArray(link.outArray, link.trueOutLen, link.falseOutLen);
    else if (link.isJustNotContrapositive())
        resetLinkArray(link.inArray, link.trueInLen, link.falseInLen);
}

void Engine::updateLinkArray(const unique_ptr<TNodeID[]>& linkArray, TNodeID trueLen, TNodeID falseLen)
{
    const TNodeID* ptr = linkArray.get();
    for (const TNodeID* truePtr = ptr + trueLen; ptr < truePtr; ptr++)
        updateNode(*ptr, TRUE);
    for (const TNodeID* falsePtr = ptr + falseLen; ptr < falsePtr; ptr++)
        updateNode(*ptr, FALSE);
}

void Engine::resetLinkArray(const unique_ptr<TNodeID[]>& linkArray, TNodeID trueLen, TNodeID falseLen)
{
    const TNodeID* ptr = linkArray.get();
    for (const TNodeID* truePtr = ptr + trueLen; ptr < truePtr; ptr++)
        resetNode(*ptr, TRUE);
    for (const TNodeID* falsePtr = ptr + falseLen; ptr < falsePtr; ptr++)
        resetNode(*ptr, FALSE);
}

void Engine::updateNode(const TNodeID nodeID, const State state)
{
    assert(state == TRUE || state == FALSE);
    Node& node = nodeVector[nodeID];
    assert(node.state != (1 - state));
    if (node.state == MAYBE) {
        node.state = state;
        if (state == TRUE)
            *(trueNodeIDPtr++) = nodeID;
        else if (state == FALSE)
            *(falseNodeIDPtr--) = nodeID;
    }
}

void Engine::resetNode(const TNodeID nodeID, const State state)
{
    assert(state == TRUE || state == FALSE);
    Node& node = nodeVector[nodeID];
    assert(node.state != (1 - state));
    if (node.state == state) {
        node.state == MAYBE;
        if (state == TRUE)
            *(trueNodeIDPtr++) = nodeID;
        else if (state == FALSE)
            *(falseNodeIDPtr--) = nodeID;
    }
}

// void Engine::updateNodeArray(const Node& node, State state)
// {
//     assert(state == TRUE || state == FALSE);
//     if (state == TRUE)
//         updateNodeArray(node.trueArray, node.trueInLen, node.trueOutLen);
//     else if (state == FALSE)
//         updateNodeArray(node.falseArray, node.falseInLen, node.falseOutLen);
// }

// void Engine::constrain(TNodeID nodeID, State state)
// {
//     while (true) {
//         for ( ; trueNodeIDPtr >= nodeIDArray.get(); trueNodeIDPtr--) {
//             const Node& node = nodeVector[*trueNodeIDPtr];
//             TLinkID* truePtr = node.trueArray.get();
//             for (TLinkID* trueInPtr = truePtr + node.trueInLen; truePtr < trueInPtr; truePtr++) {
//                 Link& link = linkVector[*truePtr];
//                 link.inCount++;
//                 // Conditional
//                 if (link.inCount > link.inLimitA && link.outCount == link.outLimitA || 
//                     link.inCount == link.inLimitA && link.outCount >= link.outLimitA) {
//                     const TNodeID* outPtr = link.outArray.get();
//                     for (const TNodeID* trueOutPtr = outPtr + link.trueOutLen; outPtr < trueOutPtr; outPtr++) {
//                         const TNodeID nodeID = *outPtr;
//                         Node& node = nodeVector[nodeID];
//                         assert(node.state != FALSE);
//                         if (node.state == MAYBE) {
//                             node.state = TRUE;
//                             *(trueNodeIDPtr++) = nodeID;
//                         }
//                     }
//                     for (const TNodeID* falseOutPtr = outPtr + link.falseOutLen; outPtr < falseOutPtr; outPtr++) {
//                         const TNodeID nodeID = *outPtr;
//                         Node& node = nodeVector[nodeID];
//                         assert(node.state != TRUE);
//                         if (node.state == MAYBE) {
//                             node.state = FALSE;
//                             *(falseNodeIDPtr--) = nodeID;
//                         }
//                     }
//                 }
//                 // Contrapositive
//                 if (link.inCount > link.inLimitB && link.outCount == link.outLimitB || 
//                     link.inCount == link.inLimitB && link.outCount >= link.outLimitB) {
                    
//                 }
//             }
//         }
//     }
// }