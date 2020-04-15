#include <vector>
#include <memory>
#include "imply.h"
using std::vector;
using std::make_unique;
using namespace Imply;

Node::Node()
    : state(MAYBE),
      trueInLen(0), trueOutLen(0),
      trueArray(make_unique<TLinkID[]>(0)),
      falseInLen(0), falseOutLen(0),
      falseArray(make_unique<TLinkID[]>(0)) {}

Link::Link()
    : inCount(0), outCount(0),
      inLimitA(0), outLimitA(0),
      trueOutLen(0), falseOutLen(0),
      outArray(make_unique<TLinkID[]>(0)),
      inLimitB(0), outLimitB(0),
      trueInLen(0), falseInLen(0),
      inArray(make_unique<TLinkID[]>(0)) {}

Engine::Engine() {}

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