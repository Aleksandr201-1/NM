#ifndef FUNCTIONAL_TREE_HPP
#define FUNCTIONAL_TREE_HPP

#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <algorithm>

//PRIORITY
//val,() 0
//^ 1
//*,/,%,sin,cos,...
//+- 3 
enum class NodeType {
    OPERATION,
    VALUE,
    VARIABLE
};

enum class Operation {
    PLUS,   // +
    MINUS,  // -
    MUL,    // *
    DIV,    // /
    MOD,    // %
    POW,    // ^
    SIN,    // sin
    COS,    // cos
    TAN,    // tan
    CTG,    // ctg
    LOG,    // log_10
    LN,     // log_e, ln
    EXP,    // exp
    NOT_AN_OPERATION
};

// enum class Vars {
//     X,
//     Y
// };

class FunctionalTree;

class FunctionalTreeNode {
    public:
        FunctionalTreeNode (NodeType type);
        virtual ~FunctionalTreeNode ();
        friend FunctionalTree;
    protected:
        NodeType type;
        uint64_t priority;
        std::unique_ptr<FunctionalTreeNode> left, right;
};

class OperationNode : public FunctionalTreeNode {
    public:
        OperationNode (Operation op);
        ~OperationNode ();
        friend FunctionalTree; 
    private:
        Operation op;
        //uint64_t priority;
};

class ValueNode : public FunctionalTreeNode {
    public:
        ValueNode (double val);
        ~ValueNode ();
        friend FunctionalTree;
    private:
        double val;
};

class VariableNode : public FunctionalTreeNode {
    public:
        VariableNode (uint64_t idx);
        ~VariableNode ();
        friend FunctionalTree;
    private:
        uint64_t idx;
};

//класс для представления строки в функцию
class FunctionalTree {
    private:
        using NodePtr = std::unique_ptr<FunctionalTreeNode>;
    private:
        void inputCheck (const std::string &func, const std::vector<std::string> &vars) const; 
        std::string readOperation (const std::string &func, uint64_t &i) const;
        std::string readWord (const std::string &func, uint64_t &i) const;
        double readNumber (const std::string &func, uint64_t &i) const;
        std::string readInbrace (const std::string &func, uint64_t &i) const;
        Operation getOperation (const std::string &str) const;
        uint64_t getPriority (Operation op) const;
        double useOperation (Operation op, double x, double y = 0.0) const;
        double getVal (const NodePtr &node, const std::vector<double> &X) const;
        void addToTree (NodePtr &root, NodePtr &toAdd);
        NodePtr buildTree (const std::string &func, const std::vector<std::string> &vars);
        void printTree (const NodePtr &tmp) const;
    public:
        FunctionalTree (const std::string &func, const std::vector<std::string> &vars);
        //FunctionalTree (const FunctionalTree &image);
        FunctionalTree (FunctionalTree &&image);
        ~FunctionalTree ();
        double func (double x) const;
        double func (const std::vector<double> &X) const;
        void printTree () const;
        //void simplify ();
        //FunctionalTree& operator= (const FunctionalTree &image);
        FunctionalTree &operator= (FunctionalTree &&tree);
    private:
        static std::vector<std::string> operations;
        static const uint64_t VARIABLE_LIMIT = 3;
        NodePtr root;
};

#endif