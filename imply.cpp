#include <vector>
#include <memory>
#include <cassert>
#include "imply.h"
using std::vector;
using std::pair;
using namespace Imply;

Node::Node(const Node& other)
    : state(other.state),
      trueInLen(other.trueInLen), trueOutLen(other.trueOutLen),
      falseInLen(other.falseInLen), falseOutLen(other.falseOutLen)
{
    TLinkID trueLen = trueInLen + trueOutLen;
    TLinkID falseLen = falseInLen + falseOutLen;
    trueArray = std::make_unique<TLinkID[]>(trueLen);
    falseArray = std::make_unique<TLinkID[]>(falseLen);
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
    trueArray = std::make_unique<TLinkID[]>(trueLen);
    falseArray = std::make_unique<TLinkID[]>(falseLen);
    std::copy(other.trueArray.get(), other.trueArray.get() + trueLen, trueArray.get());
    std::copy(other.falseArray.get(), other.falseArray.get() + falseLen, falseArray.get());
    return *this;
}

Node::Node(Node&& other) noexcept
    : state(other.state),
      trueInLen(other.trueInLen), trueOutLen(other.trueOutLen),
      falseInLen(other.falseInLen), falseOutLen(other.falseOutLen),
      trueArray(std::move(other.trueArray)),
      falseArray(std::move(other.falseArray)) {}

Node& Node::operator=(Node&& other) noexcept
{
    state = other.state;
    trueInLen = other.trueInLen; trueOutLen = other.trueOutLen;
    falseInLen = other.falseInLen; falseOutLen = other.falseOutLen;
    trueArray = std::move(other.trueArray);
    falseArray = std::move(other.falseArray);
    return *this;
}

Node::Node() noexcept
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
    trueArray = std::make_unique<TLinkID[]>(trueLen);
    falseArray = std::make_unique<TLinkID[]>(falseLen);
    std::copy(trueInLinks.cbegin(), trueInLinks.cend(), trueArray.get());
    std::copy(trueOutLinks.cbegin(), trueOutLinks.cend(), trueArray.get() + trueInLen);
    std::copy(falseInLinks.cbegin(), falseInLinks.cend(), falseArray.get());
    std::copy(falseOutLinks.cbegin(), falseOutLinks.cend(), falseArray.get() + falseInLen);
}

Link::Link(const Link& other)
    : inCount(other.inCount), outCount(other.outCount),
      inLimit(other.inLimit), outLimit(other.outLimit),
      trueOutLen(other.trueOutLen), falseOutLen(other.falseOutLen),
      trueInLen(other.trueInLen), falseInLen(other.falseInLen)
{
    TNodeID outLen = trueOutLen + falseOutLen;
    TNodeID inLen = trueInLen + falseInLen;
    outArray = std::make_unique<TNodeID[]>(outLen);
    inArray = std::make_unique<TNodeID[]>(inLen);
    std::copy(other.outArray.get(), other.outArray.get() + outLen, outArray.get());
    std::copy(other.inArray.get(), other.inArray.get() + inLen, inArray.get());
}

Link& Link::operator=(const Link& other)
{
    inCount = other.inCount; outCount = other.outCount;
    inLimit = other.inLimit; outLimit = other.outLimit;
    trueOutLen = other.trueOutLen; falseOutLen = other.falseOutLen;
    trueInLen = other.trueInLen; falseInLen = other.falseInLen;
    TNodeID outLen = trueOutLen + falseOutLen;
    TNodeID inLen = trueInLen + falseInLen;
    outArray = std::make_unique<TNodeID[]>(outLen);
    inArray = std::make_unique<TNodeID[]>(inLen);
    std::copy(other.outArray.get(), other.outArray.get() + outLen, outArray.get());
    std::copy(other.inArray.get(), other.inArray.get() + inLen, inArray.get());
    return *this;
}

Link::Link(Link&& other) noexcept
    : inCount(other.inCount), outCount(other.outCount),
      inLimit(other.inLimit), outLimit(other.outLimit),
      trueOutLen(other.trueOutLen), falseOutLen(other.falseOutLen),
      trueInLen(other.trueInLen), falseInLen(other.falseInLen),
      outArray(std::move(other.outArray)),
      inArray(std::move(other.inArray)) {}

Link& Link::operator=(Link&& other) noexcept
{
    inCount = other.inCount; outCount = other.outCount;
    inLimit = other.inLimit; outLimit = other.outLimit;
    trueOutLen = other.trueOutLen; falseOutLen = other.falseOutLen;
    trueInLen = other.trueInLen; falseInLen = other.falseInLen;
    outArray = std::move(other.outArray);
    inArray = std::move(other.inArray);
    return *this;
}

Link::Link() noexcept
    : inCount(0), outCount(0),
      inLimit(0), outLimit(0),
      trueOutLen(0), falseOutLen(0), outArray(),
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
    // In
    TNodeID inLen = trueInNodes.size() + falseInNodes.size();
    Link::inArray = std::make_unique<TNodeID[]>(inLen);
    if (inEquality & IS_GREATER) {
        Link::trueInLen = trueInNodes.size();
        Link::falseInLen = falseInNodes.size();
        std::copy(trueInNodes.cbegin(), trueInNodes.cend(), Link::inArray.get());
        std::copy(falseInNodes.cbegin(), falseInNodes.cend(), Link::inArray.get() + trueInNodes.size());
    } else {
        Link::trueInLen = falseInNodes.size();
        Link::falseInLen = trueInNodes.size();
        std::copy(falseInNodes.cbegin(), falseInNodes.cend(), Link::inArray.get());
        std::copy(trueInNodes.cbegin(), trueInNodes.cend(), Link::inArray.get() + falseInNodes.size());
        inLimit = inLen - inLimit;
    }
    // if (!(inEquality & IS_EQUAL)) inLimit += 1;
    // Link::inLimit = inLimit - 1;
    if (inEquality & IS_EQUAL) inLimit -= 1;
    Link::inLimit = inLimit;
    // Out
    TNodeID outLen = trueOutNodes.size() + falseOutNodes.size();
    Link::outArray = std::make_unique<TNodeID[]>(outLen);
    if (!(outEquality & IS_GREATER)) {
        Link::trueOutLen = trueOutNodes.size();
        Link::falseOutLen = falseOutNodes.size();
        std::copy(trueOutNodes.cbegin(), trueOutNodes.cend(), Link::outArray.get());
        std::copy(falseOutNodes.cbegin(), falseOutNodes.cend(), Link::outArray.get() + trueOutNodes.size());
    } else {
        Link::trueOutLen = falseOutNodes.size();
        Link::falseOutLen = trueOutNodes.size();
        std::copy(falseOutNodes.cbegin(), falseOutNodes.cend(), Link::outArray.get());
        std::copy(trueOutNodes.cbegin(), trueOutNodes.cend(), Link::outArray.get() + falseOutNodes.size());
        outLimit = outLen - outLimit;
    }
    if (!(outEquality & IS_EQUAL)) outLimit -= 1;
    Link::outLimit = outLimit;
}

bool Link::isJustConditional() const noexcept
{
    // Just Conditional
    bool e_ge = inCount == inLimit + 1 && outCount >= outLimit;
    bool ge_e = inCount >= inLimit + 1 && outCount == outLimit;
    return e_ge || ge_e;
}

bool Link::isJustContrapositive() const noexcept
{
    // Just Contrapositive
    bool e_ge = inCount == inLimit && outCount >= outLimit + 1;
    bool ge_e = inCount >= inLimit && outCount == outLimit + 1;
    return e_ge || ge_e;
}

bool Link::isJustNotConditional() const noexcept
{
    // Just Not Conditional
    bool e_ge = inCount == inLimit && outCount <= outLimit - 1;
    bool ge_e = inCount <= inLimit && outCount == outLimit - 1;
    return e_ge || ge_e;
}

bool Link::isJustNotContrapositive() const noexcept
{
    // Just Not Contrapositive
    bool e_ge = inCount == inLimit - 1 && outCount <= outLimit;
    bool ge_e = inCount <= inLimit - 1 && outCount == outLimit;
    return e_ge || ge_e;
}

Engine::Bound::Bound() noexcept
    : trueNodeIDPtr(nullptr), falseNodeIDPtr(nullptr), state(TRUE) {}

Engine::Bound::Bound(TNodeID* trueNodeIDPtr, TNodeID* falseNodeIDPtr, State state) noexcept
    : trueNodeIDPtr(trueNodeIDPtr), falseNodeIDPtr(falseNodeIDPtr), state(state) {}

Engine::Engine() noexcept
    : nodeVector(), linkVector(),
      nodeIDArray(), boundArray() {}

Engine::Engine(const Engine& other)
    : nodeVector(other.nodeVector),
      linkVector(other.linkVector)
{
    nodeIDArray = std::make_unique<TNodeID[]>(nodeVector.size());
    std::copy(other.nodeIDArray.get(), other.nodeIDArray.get() + other.nodeVector.size(), nodeIDArray.get());
    std::copy(other.boundArray.get(), other.boundArray.get() + other.nodeVector.size(), boundArray.get());
}

Engine& Engine::operator=(const Engine& other)
{
    nodeVector = other.nodeVector;
    linkVector = other.linkVector;
    nodeIDArray = std::make_unique<TNodeID[]>(nodeVector.size());
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

Engine::Engine(const vector<Link>& links, TNodeID nodeSize)
    : Engine(vector<Link>(links), nodeSize) {}

Engine::Engine(vector<Link>&& links, TNodeID nodeSize)
    : linkVector(std::move(links)),
      nodeVector(nodeSize),
      nodeIDArray(std::make_unique<TNodeID[]>(nodeSize)),
      boundArray(std::make_unique<Bound[]>(nodeSize))
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
        node.trueArray = std::make_unique<TLinkID[]>(node.trueInLen + node.trueOutLen);
        node.falseArray = std::make_unique<TLinkID[]>(node.falseInLen + node.falseOutLen);
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

bool Engine::constrain(const vector<pair<TNodeID,bool>>& nodeStates) noexcept
{
    TNodeID* trueNodeIDPtrStart = nodeIDArray.get();
    TNodeID* falseNodeIDPtrStart = nodeIDArray.get() + nodeVector.size() - 1;
    TNodeID* trueNodeIDPtrEnd = trueNodeIDPtrStart;
    TNodeID* falseNodeIDPtrEnd = falseNodeIDPtrStart;
    for (pair<TNodeID,bool> nodeState : nodeStates) {
        TNodeID nodeID = nodeState.first;
        bool state = nodeState.second;
        assert(nodeID < nodeVector.size());

        Node& node = nodeVector[nodeID];
        assert(node.state == MAYBE);
        if (state) {
            node.state = TRUE;
            *(trueNodeIDPtrEnd++) = nodeID;
        } else {
            node.state = FALSE;
            *(falseNodeIDPtrEnd--) = nodeID;
        }
    }
    return constrain(
        trueNodeIDPtrStart, falseNodeIDPtrStart, 
        trueNodeIDPtrEnd, falseNodeIDPtrEnd);
}

bool Engine::constrain(const vector<TNodeID>& trueNodeIDs, const vector<TNodeID>& falseNodeIDs) noexcept
{
    TNodeID* trueNodeIDPtrStart = nodeIDArray.get();
    TNodeID* falseNodeIDPtrStart = nodeIDArray.get() + nodeVector.size() - 1;
    TNodeID* trueNodeIDPtrEnd = trueNodeIDPtrStart;
    TNodeID* falseNodeIDPtrEnd = falseNodeIDPtrStart;
    for (TNodeID nodeID : trueNodeIDs) {
        assert(nodeID < nodeVector.size());
        Node& node = nodeVector[nodeID];
        assert(node.state == MAYBE);
        node.state = TRUE;
        *(trueNodeIDPtrEnd++) = nodeID;
    }
    for (TNodeID nodeID : falseNodeIDs) {
        assert(nodeID < nodeVector.size());
        Node& node = nodeVector[nodeID];
        assert(node.state == MAYBE);
        node.state = FALSE;
        *(falseNodeIDPtrEnd--) = nodeID;
    }
    return constrain(
        trueNodeIDPtrStart, falseNodeIDPtrStart, 
        trueNodeIDPtrEnd, falseNodeIDPtrEnd);
}

bool Engine::backtrack() noexcept
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

bool Engine::backtrack_findMaybe(TNodeID& nodeID) noexcept
{
    for ( ; nodeID < nodeVector.size(); nodeID++)
        if (nodeVector[nodeID].state == MAYBE) return true;
    return false;
}

bool Engine::constrain(
    TNodeID* trueNodeIDPtrStart, TNodeID* falseNodeIDPtrStart, 
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd) noexcept
{
    TNodeID* trueNodeIDPtr = trueNodeIDPtrStart;
    TNodeID* falseNodeIDPtr = falseNodeIDPtrStart;

    while (true) {
        for ( ; trueNodeIDPtr < trueNodeIDPtrEnd; trueNodeIDPtr++) {
            if (!constrain_updateLinkArray(
                    trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                    nodeVector[*trueNodeIDPtr], TRUE, false, true)) {
                undo(
                    trueNodeIDPtrStart, trueNodeIDPtr + 1, trueNodeIDPtrEnd, 
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
                    falseNodeIDPtrStart, falseNodeIDPtr - 1, falseNodeIDPtrEnd);
                return false;
            }
        }
        if (!(trueNodeIDPtr < trueNodeIDPtrEnd)) return true;
    }
}

void Engine::undo(
    TNodeID* trueNodeIDPtrStart, TNodeID* trueNodeIDPtrMid, TNodeID* trueNodeIDPtrEnd,
    TNodeID* falseNodeIDPtrStart, TNodeID* falseNodeIDPtrMid, TNodeID* falseNodeIDPtrEnd) noexcept
{
    for ( ; trueNodeIDPtrStart < trueNodeIDPtrMid; trueNodeIDPtrStart++) {
        Node& node = nodeVector[*trueNodeIDPtrStart];
        node.state = MAYBE;
        constrain_updateLinkArray(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            node, TRUE, true, false);
    }
    for ( ; trueNodeIDPtrStart < trueNodeIDPtrEnd; trueNodeIDPtrStart++)
        nodeVector[*trueNodeIDPtrStart].state = MAYBE;

    for ( ; falseNodeIDPtrStart > falseNodeIDPtrMid; falseNodeIDPtrStart--) {
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
    const Node& node, const State state, const bool reset, const bool propagate) noexcept
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
    const unique_ptr<TLinkID[]>& nodeArray, const TLinkID inLen, const TLinkID outLen, const bool reset, const bool propagate) noexcept
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
    const TLinkID linkID, const Side side, const bool reset, const bool propagate) noexcept
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
    const Link& link, const bool reset) noexcept
{
    if (reset) {
        if (link.isJustNotConditional())
            return constrain_updateNodeArray(
                trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                link.outArray, link.trueOutLen, link.falseOutLen, link.outLimit, reset);
        else if (link.isJustNotContrapositive())
            return constrain_updateNodeArray(
                trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                link.inArray, link.trueInLen, link.falseInLen, link.inLimit, reset);
    } else {
        if (link.isJustConditional())
            return constrain_updateNodeArray(
                trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                link.outArray, link.trueOutLen, link.falseOutLen, link.outLimit, reset);
        else if (link.isJustContrapositive())
            return constrain_updateNodeArray(
                trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
                link.inArray, link.trueInLen, link.falseInLen, link.inLimit, reset);
    }
    return true;
}

bool Engine::constrain_updateNodeArray(
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
    const unique_ptr<TNodeID[]>& linkArray, const TNodeID trueLen, const TNodeID falseLen, const TNodeID exLimit, const bool reset) noexcept
{
    TNodeID count = 0;
    const TNodeID* ptr = linkArray.get();
    for (const TNodeID* truePtr = ptr + trueLen; ptr < truePtr; ptr++)
        if (!constrain_updateNode(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            *ptr, FALSE, reset) && ++count > exLimit) return false;
    for (const TNodeID* falsePtr = ptr + falseLen; ptr < falsePtr; ptr++)
        if (!constrain_updateNode(
            trueNodeIDPtrEnd, falseNodeIDPtrEnd, 
            *ptr, TRUE, reset) && ++count > exLimit) return false;
    assert(count == exLimit);
    return true;
}

bool Engine::constrain_updateNode(
    TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
    const TNodeID nodeID, const State state, const bool reset) noexcept
{
    assert(state == TRUE || state == FALSE);
    Node& node = nodeVector[nodeID];
    if (node.state == (1 - state)) return false;
    State checkState, newState;
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