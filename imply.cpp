#include <vector>
#include "imply.h"
using std::vector;
using namespace Imply;

Node::Node()
    : state(MAYBE),
      trueInLen(0), trueOutLen(0), trueArray(nullptr),
      falseInLen(0), falseOutLen(0), falseArray(nullptr) {}

Node::~Node()
{
    delete[] trueArray;
    delete[] falseArray;
}

Node::Node(const Node& other)
    : state(other.state),
      trueInLen(other.trueInLen), trueOutLen(other.trueOutLen),
      falseInLen(other.falseInLen), falseOutLen(other.falseOutLen)
{
    TLinkID trueLen = trueInLen + trueOutLen;
    TLinkID falseLen = falseInLen + falseOutLen;
    trueArray = new TLinkID[trueLen];
    falseArray = new TLinkID[falseLen];
    std::copy(other.trueArray, other.trueArray + trueLen, trueArray);
    std::copy(other.falseArray, other.falseArray + falseLen, falseArray);
}

Node& Node::operator=(const Node& other)
{
    Node temp(other);
    swap(*this, temp);
    return *this;
}

Node::Node(Node&& other): Node()
{
    swap(*this, other);
}

Node& Node::operator=(Node&& other)
{
    swap(*this, other);
    return *this;
}

void Node::swap(Node& first, Node& second)
{
    std::swap(first.state, second.state);
    std::swap(first.trueInLen, second.trueInLen);
    std::swap(first.trueOutLen, second.trueOutLen);
    std::swap(first.trueArray, second.trueArray);
    std::swap(first.falseInLen, second.falseInLen);
    std::swap(first.falseOutLen, second.falseOutLen);
    std::swap(first.falseArray, second.falseArray);
}

Link::Link()
    : inCount(0), outCount(0),
      inLimitA(0), outLimitA(0),
      trueOutLen(0), falseOutLen(0), outArray(nullptr),
      inLimitB(0), outLimitB(0),
      trueInLen(0), falseInLen(0), inArray(nullptr) {}

Link::~Link()
{
    delete[] outArray;
    delete[] inArray;
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
    outArray = new TNodeID[outLen];
    inArray = new TNodeID[inLen];
    std::copy(other.outArray, other.outArray + outLen, outArray);
    std::copy(other.inArray, other.inArray + inLen, inArray);
}

Link& Link::operator=(const Link& other)
{
    Link temp(other);
    swap(*this, temp);
    return *this;
}

Link::Link(Link&& other): Link()
{
    swap(*this, other);
}

Link& Link::operator=(Link&& other)
{
    swap(*this, other);
    return *this;
}

void Link::swap(Link& first, Link& second)
{
    std::swap(first.inCount, second.inCount);
    std::swap(first.outCount, second.outCount);
    std::swap(first.inLimitA, second.inLimitA);
    std::swap(first.outLimitA, second.outLimitA);
    std::swap(first.trueOutLen, second.trueOutLen);
    std::swap(first.falseOutLen, second.falseOutLen);
    std::swap(first.outArray, second.outArray);
    std::swap(first.inLimitB, second.inLimitB);
    std::swap(first.outLimitB, second.outLimitB);
    std::swap(first.trueInLen, second.trueInLen);
    std::swap(first.falseInLen, second.falseInLen);
    std::swap(first.inArray, second.inArray);
}

Engine::Engine() {}

Engine::~Engine() {}

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

// void Engine::swap(Engine& first, Engine& second)
// {
//     std::swap(first.nodeSize, second.nodeSize);
//     std::swap(first.linkSize, second.linkSize);
//     std::swap(first.nodeArray, second.nodeArray);
//     std::swap(first.linkArray, second.linkArray);
// }

// Compiler::Statement::Statement(
//     const vector<TNodeID> trueInNodes, 
//     const vector<TNodeID> falseInNodes, 
//     const Equality inEquality, const TNodeID inLimit,
//     const vector<TNodeID> trueOutNodes, 
//     const vector<TNodeID> falseOutNodes, 
//     const Equality outEquality, const TNodeID outLimit):
//     trueInNodes(trueInNodes),   falseInNodes(falseInNodes),
//     inEquality(inEquality),     inLimit(inLimit),
//     trueOutNodes(trueOutNodes), falseOutNodes(falseOutNodes),
//     outEquality(outEquality),   outLimit(outLimit) {}

// void Compiler::add(
//     const vector<TNodeID> trueInNodes, 
//     const vector<TNodeID> falseInNodes, 
//     const Equality inEquality, const TNodeID inLimit,
//     const vector<TNodeID> trueOutNodes, 
//     const vector<TNodeID> falseOutNodes, 
//     const Equality outEquality, const TNodeID outLimit)
// {
//     statementSize++;
//     statementList.emplace_front(
//         trueInNodes, falseInNodes, inEquality, inLimit, 
//         trueOutNodes, falseOutNodes, outEquality, outLimit);
// }

// void Compiler::compile(Engine& engine)
// {
//     engine = Engine();

// }

// _Link::_Link(
//     TNodeID BnLimitA, TNodeID outLimitA, 
//     TNodeID tBueOutLen, TNodeID falseOutLen, TNodeID* outArray,
//     TNodeID inLimitB, TNodeID outLimitB, 
//     TNodeID trueInLen, TNodeID  falseInLen, TNodeID* inArray)
// {
//     _Link::inLimitA = inLimitA;
//     _Link::outLimitA = outLimitA;
//     _Link::trueOutLen = trueOutLen;
//     _Link::falseOutLen = falseOutLen;
//     _Link::outArray = outArray;
//     _Link::inLimitB = inLimitB;
//     _Link::outLimitB = outLimitB;
//     _Link::trueInLen = trueInLen;
//     _Link::falseInLen = falseInLen;
//     _Link::inArray = inArray;
// }

// Imply()
// {
//     nodeSize = 0;
//     linkSize = 0;
//     nodeArray = nullptr;
//     linkArray = nullptr;
// }

// ~Imply()
// {
//     if (nodeArray != nullptr) delete[] nodeArray;
//     if (linkArray != nullptr) delete[] linkArray;
// }

// void add(
//     vector<TNodeID> trueInNodes, vector<TNodeID> falseInNodes, 
//     Equality inEquality, TNodeID inLimit, 
//     vector<TNodeID> trueOutNodes, vector<TNodeID> falseOutNodes,
//     Equality outEquality, TNodeID outLimit)
// {
//     TNodeID inSize = trueInNodes.size() + falseInNodes.size();
//     TNodeID outSize = trueOutNodes.size() + falseOutNodes.size();
//     equalizeLimit(inEquality, inSize, inLimit);
//     equalizeLimit(outEquality, outSize, outLimit);
    
// }

// void equalizeLimit(Equality equality, TNodeID maxSize, TNodeID& limit) {
//     switch (equality) {
//     case LT:
//         limit -= 1;
//         limit = maxSize - limit;
//         break;
//     case LE:
//         limit = maxSize - limit;
//         break;
//     case GT:
//         limit += 1;
//         break;
//     }
// }