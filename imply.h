#include <vector>
#include <memory>
#include <iostream>

// template<typename TNodeID, typename TLinkID>
namespace Imply
{
    using std::vector;
    using std::unique_ptr;
    using std::pair;
    typedef unsigned char State;
    typedef unsigned char Side;
    typedef unsigned int TNodeID;
    typedef unsigned int TLinkID;
    typedef unsigned char Equality;
    const State FALSE = 0;
    const State TRUE = 1;
    const State MAYBE = 2;
    const Side IN = 0;
    const Side OUT = 1;
    const Equality IS_EQUAL   = 0b00000001;
    const Equality IS_GREATER = 0b00000010;
    const Equality LE = 0          | IS_EQUAL;
    const Equality LT = 0          | 0;
    const Equality GE = IS_GREATER | IS_EQUAL;
    const Equality GT = IS_GREATER | 0;

    class Node
    {
    private:
        friend class Engine;
        State state;
        TLinkID trueInLen, trueOutLen;
        unique_ptr<TLinkID[]> trueArray;
        TLinkID falseInLen, falseOutLen;
        unique_ptr<TLinkID[]> falseArray;
    public:
        Node(const Node& other);
        Node& operator=(const Node& other);
        Node(Node&& other) noexcept;
        Node& operator=(Node&& other) noexcept;

        Node() noexcept;
        Node(
            const vector<TLinkID>& trueInLinks,
            const vector<TLinkID>& trueOutLinks,
            const vector<TLinkID>& falseInLinks,
            const vector<TLinkID>& falseOutLinks);
    };

    class Link
    {
    private:
        friend class Engine;
        // Shared
        TNodeID inCount, outCount;
        TNodeID inLimit, outLimit;
        // Conditional
        TNodeID trueOutLen, falseOutLen;
        unique_ptr<TNodeID[]> outArray;
        // Contrapositive
        TNodeID trueInLen, falseInLen;
        unique_ptr<TNodeID[]> inArray;
    public:
        Link(const Link& other);
        Link& operator=(const Link& other);
        Link(Link&& other) noexcept;
        Link& operator=(Link&& other) noexcept;

        Link() noexcept;
        Link(
            const vector<TNodeID>& trueInNodes,
            const vector<TNodeID>& falseInNodes,
            Equality inEquality, TNodeID inLimit,
            const vector<TNodeID>& trueOutNodes,
            const vector<TNodeID>& falseOutNodes,
            Equality outEquality, TNodeID outLimit);
    private:
        bool isJustConditional() const noexcept;
        bool isJustContrapositive() const noexcept;
        bool isJustNotConditional() const noexcept;
        bool isJustNotContrapositive() const noexcept;
    };

    class Engine
    {
    private:
        struct Bound
        {
            friend class Engine;
            TNodeID* trueNodeIDPtr;
            TNodeID* falseNodeIDPtr;
            State state;
            Bound() noexcept;
            Bound(TNodeID* trueNodeIDPtr, TNodeID* falseNodeIDPtr, State state) noexcept;
        };
    private:
        vector<Node> nodeVector;
        vector<Link> linkVector;
        unique_ptr<TNodeID[]> nodeIDArray;
        unique_ptr<Bound[]> boundArray;
    public:
        Engine() noexcept;
        Engine(const Engine& other);
        Engine& operator=(const Engine& other);
        Engine(Engine&& other) noexcept;
        Engine& operator=(Engine&& other) noexcept;

        Engine(const vector<Link>& links, TNodeID nodeSize);
        Engine(vector<Link>&& links, TNodeID nodeSize);

        State getNodeState(TNodeID nodeID) const noexcept { return nodeVector[nodeID].state; }

        bool constrain(const vector<pair<TNodeID,bool>>& nodeStates) noexcept;
        bool constrain(const vector<TNodeID>& trueNodeIDs, const vector<TNodeID>& falseNodeIDs) noexcept;
        bool backtrack() noexcept;
    private:
        // Backtrack
        bool backtrack_findMaybe(TNodeID& nodeID) noexcept;
        // Constrain & Undo
        bool constrain(
            TNodeID* trueNodeIDPtrStart, TNodeID* falseNodeIDPtrStart, 
            TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd) noexcept;
        void undo(
            TNodeID* trueNodeIDPtrStart, TNodeID* trueNodeIDPtrMid, TNodeID* trueNodeIDPtrEnd, 
            TNodeID* falseNodeIDPtrStart, TNodeID* falseNodeIDPtrMid, TNodeID* falseNodeIDPtrEnd) noexcept;
        bool constrain_updateLinkArray(
            TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
            const Node& node, State state, bool reset, bool propagate) noexcept;
        bool constrain_updateLinkArray(
            TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
            const unique_ptr<TLinkID[]>& nodeArray, TLinkID inLen, TLinkID outLen, bool reset, bool propagate) noexcept;
        bool constrain_updateLink(
            TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
            TLinkID linkID, Side side, bool reset, bool propagate) noexcept;
        bool constrain_updateNodeArray(
            TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
            const Link& link, bool reset) noexcept;
        bool constrain_updateNodeArray(
            TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
            const unique_ptr<TNodeID[]>& linkArray, TNodeID trueLen, TNodeID falseLen, TNodeID exLimit, bool reset) noexcept;
        bool constrain_updateNode(
            TNodeID*& trueNodeIDPtrEnd, TNodeID*& falseNodeIDPtrEnd, 
            TNodeID nodeID, State state, bool reset) noexcept;
    };
};