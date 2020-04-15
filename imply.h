#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

// template<typename TNodeID, typename TLinkID>
namespace Imply
{
    typedef unsigned char State;
    typedef unsigned int TNodeID;
    typedef unsigned int TLinkID;
    typedef unsigned char Equality;
    static const State FALSE = 0;
    static const State TRUE = 1;
    static const State MAYBE = 2;
    static const Equality LT = 0x00;
    static const Equality LE = 0x01;
    static const Equality GT = 0x02;
    static const Equality GE = 0x03;

    class Node
    {
    private:
        State state;
        TLinkID trueInLen, trueOutLen;
        unique_ptr<TLinkID[]> trueArray;
        TLinkID falseInLen, falseOutLen;
        unique_ptr<TLinkID[]> falseArray;
    public:
        Node();
        Node(const Node& other) = delete;
        Node& operator=(const Node& other) = delete;
        Node(Node&& other) = delete;
        Node& operator=(Node&& other) = delete;
    };

    class Link
    {
    private:
        // Shared
        TNodeID inCount, outCount;
        // Conditional
        TNodeID inLimitA, outLimitA;
        TNodeID trueOutLen, falseOutLen;
        unique_ptr<TNodeID[]> outArray;
        // Contrapositive
        TNodeID inLimitB, outLimitB;
        TNodeID trueInLen, falseInLen;
        unique_ptr<TNodeID[]> inArray;
    public:
        Link();
        Link(const Link& other) = delete;
        Link& operator=(const Link& other) = delete;
        Link(Link&& other) = delete;
        Link& operator=(Link&& other) = delete;
    };

    class Engine
    {
    private:
        vector<Node> nodeVector;
        vector<Link> linkVector;
    public:
        Engine();
        Engine(const Engine& other);
        Engine& operator=(const Engine& other);
        Engine(Engine&& other);
        Engine& operator=(Engine&& other);
    };
};