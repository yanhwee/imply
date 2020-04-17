#include <vector>
#include <memory>
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
      trueInLen(0), trueOutLen(0),
      trueArray(make_unique<TLinkID[]>(0)),
      falseInLen(0), falseOutLen(0),
      falseArray(make_unique<TLinkID[]>(0)) {}

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
    Link(std::move(other));
    return *this;
}

Link::Link()
    : inCount(0), outCount(0),
      inLimitA(0), outLimitA(0),
      trueOutLen(0), falseOutLen(0),
      outArray(make_unique<TLinkID[]>(0)),
      inLimitB(0), outLimitB(0),
      trueInLen(0), falseInLen(0),
      inArray(make_unique<TLinkID[]>(0)) {}

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

Engine::Engine()
    : nodeVector(vector<Node>()),
      linkVector(vector<Link>()) {}

Engine::Engine(const Engine& other)
    : nodeVector(nodeVector), 
      linkVector(linkVector) {}

Engine& Engine::operator=(const Engine& other)
{
    nodeVector = other.nodeVector;
    linkVector = other.linkVector;
    return *this;
}

Engine::Engine(Engine&& other)
    : nodeVector(std::move(other.nodeVector)),
      linkVector(std::move(other.linkVector)) {}

Engine& Engine::operator=(Engine&& other)
{
    nodeVector = std::move(other.nodeVector);
    linkVector = std::move(other.linkVector);
    return *this;
}

template<typename L, typename N>
Engine::Engine(L&& linkVector, N&& nodeVector)
    : linkVector(linkVector), nodeVector(nodeVector) {}

template<typename L>
Engine::Engine(L&& linkVector, TNodeID nodeSize)
    : linkVector(linkVector), nodeVector(nodeSize)
{
    
}