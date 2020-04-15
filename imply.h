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
        ~Node();
        Node(const Node& other);
        Node& operator=(const Node& other);
        Node(Node&& other);
        Node& operator=(Node&& other);
        void swap(Node& first, Node& second);
    };

    class Link
    {
    private:
        // Shared
        TNodeID inCount, outCount;
        // Conditional
        TNodeID inLimitA, outLimitA;
        TNodeID trueOutLen, falseOutLen, *outArray;
        // Contrapositive
        TNodeID inLimitB, outLimitB;
        TNodeID trueInLen, falseInLen, *inArray;
    public:
        Link();
        ~Link();
        Link(const Link& other);
        Link& operator=(const Link& other);
        Link(Link&& other);
        Link& operator=(Link&& other);
        void swap(Link& first, Link& second);
    };

    class Engine
    {
    private:
        vector<Node> nodeVector;
        vector<Link> linkVector;
    public:
        Engine();
        ~Engine();
        Engine(const Engine& other);
        Engine& operator=(const Engine& other);
        Engine(Engine&& other);
        Engine& operator=(Engine&& other);
        void swap(Engine& first, Engine& second);
    };
};

// class Compiler
// {
// private:
//     struct Statement
//     {
//         const vector<TNodeID> trueInNodes;
//         const vector<TNodeID> falseInNodes;
//         const Equality inEquality;
//         const TNodeID inLimit;
//         const vector<TNodeID> trueOutNodes;
//         const vector<TNodeID> falseOutNodes;
//         const Equality outEquality;
//         const TNodeID outLimit;
//         Statement(
//             const vector<TNodeID> trueInNodes, 
//             const vector<TNodeID> falseInNodes, 
//             const Equality inEquality, TNodeID inlimit, 
//             const vector<TNodeID> trueOutNodes, 
//             const vector<TNodeID> falseOutNodes, 
//             const Equality outEquality, TNodeID outLimit);
//     };

// public:
//     void add(
//         const vector<TNodeID> trueInNodes, 
//         const vector<TNodeID> falseInNodes, 
//         const Equality inEquality, TNodeID inlimit, 
//         const vector<TNodeID> trueOutNodes, 
//         const vector<TNodeID> falseOutNodes, 
//         const Equality outEquality, TNodeID outLimit);

//     void compile(Engine& engine);

// private:

// };

// struct Link
// {
//     TNodeID inLimitA, outLimitA;
//     TNodeID trueOutLen, falseOutLen, *outArray;
//     TNodeID inLimitB, outLimitB;
//     TNodeID trueInLen, falseInLen, *inArray;
//     Link(
//         TNodeID inLimitA, TNodeID outLimitA, 
//         vector<TNodeID> trueInNodes, vector<TNodeID> falseInNodes,
//         TNodeID inLimitB, TNodeID outLimitB, 
//         vector<TNodeID> trueOutNodes, vector<TNodeID> falseOutNodes);
//     ~Link();
// };

// Compile Time
// forward_list<_Link> linkList;
// vector<_Node> nodeVector;

// Run Time

// public:
//     Imply();
//     ~Imply();

//     void add(
//         vector<TNodeID> trueInNodes, vector<TNodeID> falseInNodes, 
//         Equality inEquality, TNodeID inLimit, 
//         vector<TNodeID> trueOutNodes, vector<TNodeID> falseOutNodes,
//         Equality outEquality, TNodeID outLimit
//     );

//     void compile();

// private:
//     void equalizeLimit(Equality equality, TNodeID maxSize, TNodeID& limit);