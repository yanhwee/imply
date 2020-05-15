#include <vector>
#include <memory>
#include <cassert>
#include "imply.h"
using std::vector;
using std::make_unique;
using std::pair;
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

Engine::Bound::Bound(TNodeID* trueNodeIDPtr, TNodeID* falseNodeIDPtr, State state)
    : trueNodeIDPtr(trueNodeIDPtr), falseNodeIDPtr(falseNodeIDPtr), state(state) {}

Engine::Engine()
    : nodeVector(), linkVector(),
      nodeIDArray(), boundArray() {}

Engine::Engine(const Engine& other)
    : nodeVector(other.nodeVector),
      linkVector(other.linkVector)
{
    nodeIDArray = make_unique<TNodeID[]>(nodeVector.size());
    std::copy(other.nodeIDArray.get(), other.nodeIDArray.get() + other.nodeVector.size(), nodeIDArray.get());
    std::copy(other.boundArray.get(), other.boundArray.get() + other.nodeVector.size(), boundArray.get());
}

Engine& Engine::operator=(const Engine& other)
{
    nodeVector = other.nodeVector;
    linkVector = other.linkVector;
    nodeIDArray = make_unique<TNodeID[]>(nodeVector.size());
    std::copy(other.nodeIDArray.get(), other.nodeIDArray.get() + other.nodeVector.size(), nodeIDArray.get());
    std::copy(other.boundArray.get(), other.boundArray.get() + other.nodeVector.size(), boundArray.get());
    return *this;
}

Engine::Engine(Engine&& other) noexcept
    : nodeVector(std::move(other.nodeVector)),
      linkVector(std::move(other.linkVector)),
      nodeIDArray(std::move(other.nodeIDArray)),
      boundArray(std::move(other.boundArray)) {}

Engine& Engine::operator=(Engine&& other) noexcept
{
    nodeVector = std::move(other.nodeVector);
    linkVector = std::move(other.linkVector);
    nodeIDArray = std::move(other.nodeIDArray);
    boundArray = std::move(other.boundArray);
    return *this;
}

template<typename L, typename N>
Engine::Engine(L&& links, N&& nodes)
    : linkVector(links),
      nodeVector(nodes),
      nodeIDArray(nodeVector.size()),
      boundArray(nodeVector.size()) {}

template<typename L>
Engine::Engine(L&& links, TNodeID nodeSize)
    : linkVector(links),
      nodeVector(nodeSize),
      nodeIDArray(nodeVector.size()),
      boundArray(nodeVector.size())
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

bool Engine::constrain(vector<pair<TNodeID,bool>> nodeStates)
{
    TNodeID* trueNodeIDPtrStart = nodeIDArray.get();
    TNodeID* falseNodeIDPtrStart = nodeIDArray.get() + nodeVector.size() - 1;
    TNodeID* trueNodeIDPtrEnd = trueNodeIDPtrStart;
    TNodeID* falseNodeIDPtrEnd = falseNodeIDPtrStart;
    for (pair<TNodeID,bool> nodeState : nodeStates) {
        TNodeID nodeID = nodeState.first;
        bool state = nodeState.second;
        assert(nodeID < nodeVector.size());

        if (state) *(trueNodeIDPtrEnd++)  = nodeID;
        else       *(falseNodeIDPtrEnd--) = nodeID;
    }
    return constrain(
        trueNodeIDPtrStart, falseNodeIDPtrStart, 
        trueNodeIDPtrEnd, falseNodeIDPtrEnd);
}

bool Engine::constrain(vector<TNodeID> trueNodeIDs, vector<TNodeID> falseNodeIDs)
{
    TNodeID* trueNodeIDPtrStart = nodeIDArray.get();
    TNodeID* falseNodeIDPtrStart = nodeIDArray.get() + nodeVector.size() - 1;
    TNodeID* trueNodeIDPtrEnd = trueNodeIDPtrStart;
    TNodeID* falseNodeIDPtrEnd = falseNodeIDPtrStart;
    for (TNodeID nodeID : trueNodeIDs) {
        assert(nodeID < nodeVector.size());
        *(trueNodeIDPtrEnd++) = nodeID;
    }
    for (TNodeID nodeID : falseNodeIDs) {
        assert(nodeID < nodeVector.size());
        *(falseNodeIDPtrEnd++) = nodeID;
    }
    return constrain(
        trueNodeIDPtrStart, falseNodeIDPtrStart, 
        trueNodeIDPtrEnd, falseNodeIDPtrEnd);
}

bool Engine::backtrack()
{
    Bound* boundPtr = boundArray.get();
    boundPtr->trueNodeIDPtr = nodeIDArray.get();
    boundPtr->falseNodeIDPtr = nodeIDArray.get() + nodeVector.size() - 1;
    boundPtr->state = TRUE;

    TNodeID nodeID = 0;

    while (true) {
        TNodeID* trueNodeIDPtrStart = boundPtr->trueNodeIDPtr;
        TNodeID* falseNodeIDPtrStart = boundPtr->falseNodeIDPtr;
        TNodeID* trueNodeIDPtrEnd;
        TNodeID* falseNodeIDPtrEnd;

        switch (boundPtr->state) {
        case TRUE: 
            if (!backtrack_findMaybe(nodeID)) return true;
            *trueNodeIDPtrStart = nodeID;
            nodeVector[nodeID].state = TRUE;

            trueNodeIDPtrEnd = trueNodeIDPtrStart + 1;
            falseNodeIDPtrEnd = falseNodeIDPtrStart;
            if (constrain(trueNodeIDPtrStart, falseNodeIDPtrStart, trueNodeIDPtrEnd, falseNodeIDPtrEnd)) {
                boundPtr->state = FALSE;
                *(++boundPtr) = Bound(trueNodeIDPtrEnd, falseNodeIDPtrEnd, TRUE);
                continue;
            }
        case FALSE:
            nodeID = *trueNodeIDPtrStart;
            *falseNodeIDPtrStart = nodeID;
            nodeVector[nodeID].state = FALSE;

            trueNodeIDPtrEnd = trueNodeIDPtrStart;
            falseNodeIDPtrEnd = falseNodeIDPtrStart - 1;
            if (constrain(trueNodeIDPtrStart, falseNodeIDPtrStart, trueNodeIDPtrEnd, falseNodeIDPtrEnd)) {
                boundPtr->state = MAYBE;
                *(++boundPtr) = Bound(trueNodeIDPtrEnd, falseNodeIDPtrEnd, TRUE);
                continue;
            }
        case MAYBE:
            if (boundPtr <= boundArray.get()) return false;
            boundPtr--;
            undo(
                boundPtr->trueNodeIDPtr, trueNodeIDPtrStart, trueNodeIDPtrStart,
                boundPtr->falseNodeIDPtr, falseNodeIDPtrStart, falseNodeIDPtrStart);
        }
    }
}

bool Engine::backtrack_findMaybe(TNodeID& nodeID)
{
    for ( ; nodeID < nodeVector.size(); nodeID++)
        if (nodeVector[nodeID].state == MAYBE) return true;
    return false;
}

bool Engine::constrain(
    TNodeID* trueNodeIDPtrStart, TNodeID* falseNodeIDPtrStart, 
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd)
{
    TNodeID* trueNodeIDPtr = trueNodeIDPtrStart;
    TNodeID* falseNodeIDPtr = falseNodeIDPtrStart;

    while (true) {
        for ( ; trueNodeIDPtr < trueNodeIDPtrEnd; trueNodeIDPtr++) {
            if (!constrain_updateLinkArray(
                    trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                    nodeVector[*trueNodeIDPtr], TRUE, false, true)) {
                undo(
                    trueNodeIDPtrStart, trueNodeIDPtr, trueNodeIDPtrEnd, 
                    falseNodeIDPtrStart, falseNodeIDPtr, falseNodeIDPtrEnd);
                return false;
            }
        }
        if (!(falseNodeIDPtr > falseNodeIDPtrEnd)) return true;

        for ( ; falseNodeIDPtr > falseNodeIDPtrEnd; falseNodeIDPtr--) {
            if (!constrain_updateLinkArray(
                    trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                    nodeVector[*falseNodeIDPtr], FALSE, false, true)) {
                undo(
                    trueNodeIDPtrStart, trueNodeIDPtr, trueNodeIDPtrEnd, 
                    falseNodeIDPtrStart, falseNodeIDPtr, falseNodeIDPtrEnd);
                return false;
            }
        }
        if (!(trueNodeIDPtr < trueNodeIDPtrEnd)) return true;
    }
}

void Engine::undo(
    TNodeID* trueNodeIDPtrStart, TNodeID* trueNodeIDPtrMid, TNodeID* trueNodeIDPtrEnd,
    TNodeID* falseNodeIDPtrStart, TNodeID* falseNodeIDPtrMid, TNodeID* falseNodeIDPtrEnd)
{
    for ( ; trueNodeIDPtrStart <= trueNodeIDPtrMid; trueNodeIDPtrStart++) {
        Node& node = nodeVector[*trueNodeIDPtrStart];
        node.state = MAYBE;
        constrain_updateLinkArray(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            node, TRUE, true, false);
    }
    for ( ; trueNodeIDPtrStart < trueNodeIDPtrEnd; trueNodeIDPtrStart++)
        nodeVector[*trueNodeIDPtrStart].state = MAYBE;

    for ( ; falseNodeIDPtrStart >= falseNodeIDPtrMid; falseNodeIDPtrStart--) {
        Node& node = nodeVector[*falseNodeIDPtrStart];
        node.state = MAYBE;
        constrain_updateLinkArray(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            node, FALSE, true, false);
    }
    for ( ; falseNodeIDPtrStart > falseNodeIDPtrEnd; falseNodeIDPtrStart--)
        nodeVector[*falseNodeIDPtrStart].state = MAYBE;
}

bool Engine::constrain_updateLinkArray(
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
    const Node& node, const State state, const bool reset, const bool propagate)
{
    assert(state == TRUE || state == FALSE);
    if (state == TRUE)
        return constrain_updateLinkArray(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            node.trueArray, node.trueInLen, node.trueOutLen, reset, propagate);
    else
        return constrain_updateLinkArray(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            node.falseArray, node.falseInLen, node.falseOutLen, reset, propagate);
}

bool Engine::constrain_updateLinkArray(
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
    const unique_ptr<TLinkID[]>& nodeArray, const TLinkID inLen, const TLinkID outLen, const bool reset, const bool propagate)
{
    TLinkID* ptr = nodeArray.get();
    for (TLinkID* inPtr = ptr + inLen; ptr < inPtr; ptr++)
        if (!constrain_updateLink(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            *ptr, IN, reset, propagate)) return false;
    for (TLinkID* outPtr = ptr + outLen; ptr < outPtr; ptr++)
        if (!constrain_updateLink(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            *ptr, OUT, reset, propagate)) return false;
    return true;
}

bool Engine::constrain_updateLink(
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
    const TLinkID linkID, const Side side, const bool reset, const bool propagate)
{
    assert(side == IN || side == OUT);
    Link& link = linkVector[linkID];
    if (side == IN) {
        if (reset) link.inCount--;
        else       link.inCount++;
    } else {
        if (reset) link.outCount--;
        else       link.outCount++;
    }
    return propagate ? constrain_updateNodeArray(trueNodeIDPtrEnd, falseNodeIDPtrEnd, link, reset) : true;
}

bool Engine::constrain_updateNodeArray(
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
    const Link& link, const bool reset)
{
    if (reset) {
        if (link.isJustNotConditional())
            return constrain_updateNodeArray(
                trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                link.outArray, link.trueOutLen, link.falseOutLen, reset);
        else if (link.isJustNotContrapositive())
            return constrain_updateNodeArray(
                trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                link.inArray, link.trueInLen, link.falseInLen, reset);
    } else {
        if (link.isJustConditional())
            return constrain_updateNodeArray(
                trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                link.outArray, link.trueOutLen, link.falseOutLen, reset);
        else if (link.isJustContrapositive())
            return constrain_updateNodeArray(
                trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                link.inArray, link.trueInLen, link.falseInLen, reset);
    }
    return true;
}

bool Engine::constrain_updateNodeArray(
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
    const unique_ptr<TNodeID[]>& linkArray, const TNodeID trueLen, const TNodeID falseLen, const bool reset)
{
    const TNodeID* ptr = linkArray.get();
    for (const TNodeID* truePtr = ptr + trueLen; ptr < truePtr; ptr++)
        if (!constrain_updateNode(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            *ptr, TRUE, reset)) return false;
    for (const TNodeID* falsePtr = ptr + falseLen; ptr < falsePtr; ptr++)
        if (!constrain_updateNode(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            *ptr, FALSE, reset)) return false;
    return true;
}

bool Engine::constrain_updateNode(
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
    const TNodeID nodeID, const State state, const bool reset)
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
            *(trueNodeIDPtrEnd++) = nodeID;
        else
            *(falseNodeIDPtrEnd--) = nodeID;
    }
    return true;
}