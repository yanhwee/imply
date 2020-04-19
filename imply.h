#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

// template<typename TNodeID, typename TLinkID>
namespace Imply
{
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

        Node();
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
        // Conditional
        TNodeID inLimitA, outLimitA;
        TNodeID trueOutLen, falseOutLen;
        unique_ptr<TNodeID[]> outArray;
        // Contrapositive
        TNodeID inLimitB, outLimitB;
        TNodeID trueInLen, falseInLen;
        unique_ptr<TNodeID[]> inArray;
    public:
        Link(const Link& other);
        Link& operator=(const Link& other);
        Link(Link&& other) noexcept;
        Link& operator=(Link&& other) noexcept;

        Link();
        Link(
            const vector<TNodeID>& trueInNodes, 
            const vector<TNodeID>& falseInNodes,
            Equality inEquality, TNodeID inLimit,
            const vector<TNodeID>& trueOutNodes, 
            const vector<TNodeID>& falseOutNodes,
            Equality outEquality, TNodeID outLimit);
    private:
        bool isJustConditional() const;
        bool isJustContrapositive() const;
        bool isJustNotConditional() const;
        bool isJustNotContrapositive() const;
    };

    class Engine
    {
    private:
        vector<Node> nodeVector;
        vector<Link> linkVector;
        unique_ptr<TNodeID[]> nodeIDArray;
        TNodeID* nodeIDArrayPtrEnd;
        TNodeID* trueNodeIDPtr;
        TNodeID* falseNodeIDPtr;
    public:
        Engine();
        Engine(const Engine& other);
        Engine& operator=(const Engine& other);
        Engine(Engine&& other) noexcept;
        Engine& operator=(Engine&& other) noexcept;

        template<typename L, typename N>
        Engine(L&& links, N&& nodes);
        template<typename L>
        Engine(L&& links, TNodeID nodeSize);

        void selfAssert(bool strong = false);
        void constrain(TNodeID nodeID, State state);

    private:
        void updateNodeArray(TNodeID nodeID, State state);
        void resetNodeArray(TNodeID nodeID, State state);
        void updateNodeArray(const unique_ptr<TLinkID[]>& nodeArray, TLinkID inLen, TLinkID outLen);
        void resetNodeArray(const unique_ptr<TLinkID[]>& nodeArray, TLinkID inLen, TLinkID outLen);
        
        void updateLink(TLinkID linkID, Side side);
        void resetLink(TLinkID linkID, Side side);

        void updateLinkArray(const Link& link);
        void resetLinkArray(const Link& link);
        void updateLinkArray(const unique_ptr<TNodeID[]>& linkArray, TNodeID trueLen, TNodeID falseLen);
        void resetLinkArray(const unique_ptr<TNodeID[]>& linkArray, TNodeID trueLen, TNodeID falseLen);

        void updateNode(TNodeID nodeID, State state);
        void resetNode(TNodeID nodeID, State state);

        // void updateNodeArray(const Node& node, State state);

        // void updateLinkArray(const Link& link, Side side);
        // void resetLinkArray(const Link& link, Side side);
    };
};;