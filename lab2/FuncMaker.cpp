#include "FuncMaker.hpp"
#include <iostream>
std::vector<std::string> FunctionalTree::operations = {"+", "-", "*", "/", "%", "^", "sin", "cos", "tg", "ctg", "log", "ln", "exp"};
//std::vector<uint64_t> prioritet = {};

FunctionalTreeNode::FunctionalTreeNode (NodeType type) : type(type), priority(0) {}
FunctionalTreeNode::~FunctionalTreeNode () {}

OperationNode::OperationNode (Operation op) : FunctionalTreeNode(NodeType::OPERATION), op(op) {}
OperationNode::~OperationNode () {}

ValueNode::ValueNode (double val) : FunctionalTreeNode(NodeType::VALUE), val(val) {}
ValueNode::~ValueNode () {}

VariableNode::VariableNode (Vars var) : FunctionalTreeNode(NodeType::VARIABLE), var(var) {}
VariableNode::~VariableNode () {}

std::string FunctionalTree::readWord (const std::string &func, uint64_t &i) const {
    std::string str;
    //words
    std::cout << "reading word...\n";
    while (((func[i] > 'A' && func[i] < 'Z') || (func[i] > 'a' && func[i] < 'z')) && i < func.size()) {
        str += func[i];
        //std::cout << "let: " << func[i] << "\n";
        ++i;
    }
    //+,-,*,/,%,^
    if (str.empty() && i < func.size()) {
        str += func[i];
        ++i;
    }
    return str;
}

double FunctionalTree::readNumber (const std::string &func, uint64_t &i) const {
    std::string str;
    while (((func[i] >= '0' && func[i] <= '9') || func[i] == '.') && i < func.size()) {
        str += func[i];
        ++i;
    }
    return std::atof(str.c_str());
}

std::string FunctionalTree::readOperation (const std::string &func, uint64_t &i) const {
    std::string str;
    while (i < func.size()) {
        switch (func[i]) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                str += func[i];
                ++i;
                break;
            default:
                i = func.size();
                break;
        }
    }
    return str;
}

std::string FunctionalTree::readInbrace (const std::string &func, uint64_t &i) const {
    uint64_t braceCount = 1;
    std::string str;
    ++i;
    while (i < func.size()) {
        if (func[i] == '(') {
            ++braceCount;
        } else if (func[i] == ')') {
            --braceCount;
        }
        if (braceCount != 0) {
            str += func[i];
        } else {
            break;
        }
        ++i;
    }
    ++i;
    if (braceCount != 0) {
        throw std::out_of_range("Operation \"readInbrace\" out of range. Incorrect placement of brackets");
    }
    // do {
    //     if (func[i] == '(') {
    //         ++braceCount;
    //     } else if (func[i] == ')') {
    //         --braceCount;
    //     } else if (i < func.size()) {
    //         str += func[i];
    //     } else {
    //         throw std::out_of_range("Operation \"readInbrace\" out of range. Incorrect placement of brackets");
    //     }
    //     ++i;
    // } while (braceCount != 0);
    return str;
}

Operation FunctionalTree::getOperation (const std::string &str) const {
    Operation op = Operation::NOT_AN_OPERATION;
    for (uint64_t i = 0; i < operations.size(); ++i) {
        if (str == operations[i]) {
            op = static_cast<Operation>(i);
            break;
        }
    }
    return op;
}

uint64_t FunctionalTree::getPriority (Operation op) const {
    switch (op) {
        case Operation::POW:
            return 1;
        case Operation::PLUS:
        case Operation::MINUS:
            return 3;
        default:
            return 2;
    }
}

double FunctionalTree::useOperation (Operation op, double x, double y) const {
    switch (op) {
        case Operation::PLUS:
            return x + y;
        case Operation::MINUS:
            return x - y;
        case Operation::MUL:
            return x * y;
        case Operation::DIV:
            return x / y;
        case Operation::MOD:
            return std::fmod(x, y);
        case Operation::LOG:
            return std::log10(x);
        case Operation::LN:
            return std::log(x);
        case Operation::SIN:
            return std::sin(x);
        case Operation::COS:
            return std::cos(x);
        case Operation::TAN:
            return std::tan(x);
        case Operation::CTG:
            return 1.0 / std::tan(x);
        case Operation::POW:
            return std::pow(x, y);
        case Operation::EXP:
            return std::exp(x);
        default:
            return 0;
    }
}

double FunctionalTree::getVal (const NodePtr &node, double x) const {
    if (!node->left.get() && !node->right.get()) {
        if (node->type == NodeType::VALUE) {
            ValueNode* value = (ValueNode*) node.get();
            return value->val;
        } else {
            return x;
        }
    }
    OperationNode* operation = (OperationNode*) node.get();
    if (node->left && !node->right) {
        return useOperation(operation->op, getVal(operation->left, x), 0);
    }
    if (!node->left && node->right) {
        return useOperation(operation->op, getVal(operation->right, x), 0);
    }
    double a = getVal(node->left, x);
    double b = getVal(node->right, x);
    return useOperation(operation->op, a, b);
}

void FunctionalTree::addToTree (NodePtr &tree, NodePtr &toAdd) {
    if (!tree.get()) {
        tree.swap(toAdd);
        //tree = toAdd;
        //tree = toAdd.get();
        return;
    }
    //OperationNode *t = (OperationNode *)tree.get(), *a = (OperationNode *)toAdd.get();
    switch (toAdd->type) {
        case NodeType::OPERATION:
            if (tree->type == NodeType::OPERATION) {
                if (tree->priority <= toAdd->priority) {
                    toAdd->left.swap(tree);
                    tree.swap(toAdd);
                } else {
                    if (!tree->left.get()) {
                        tree->left.swap(toAdd);
                    } else {
                        if (tree->right.get()) {
                            toAdd->left.swap(tree->right);
                        }
                        tree->right.swap(toAdd);
                    }
                }
            } else {
                // toAdd->left.swap(tree->right);
                // tree->right.swap(toAdd);
                toAdd->left.swap(tree);
                tree.swap(toAdd);
            }
            // if (toAdd->left || toAdd->right) {
            //     tree->right.swap(toAdd);
            // } else if (tree->type == NodeType::OPERATION) {
            //     if (tree->priority <= toAdd->priority) {
            //         toAdd->left.swap(tree);
            //         tree.swap(toAdd);
            //     } else {
            //         toAdd->left.swap(tree->right);
            //         tree->right.swap(toAdd);
            //     }
            // } else {
            //     toAdd->left.swap(tree);
            //     tree.swap(toAdd);
            // }
            break;
        case NodeType::VALUE:
        case NodeType::VARIABLE:
            if (!tree->left.get()) {
                tree->left.swap(toAdd);
            } else {
                auto tmp = tree.get();
                while (tmp->right.get()) {
                    tmp = tmp->right.get();
                }
                if (!tmp->left.get()) {
                    tmp->left.swap(toAdd);
                } else {
                    tmp->right.swap(toAdd);
                }
                //tree->right.swap(toAdd);
            }
            break;
        default:
            break;
    }
}

FunctionalTree::NodePtr FunctionalTree::buildTree (const std::string &func) {
    std::cout << "Our func: " << func << "\n";
    std::string tmp;
    uint64_t i = 0;
    double number;
    Operation op;
    NodePtr currentNode, node;
    while (i < func.size()) {
        std::cout << "new step: i = " << i << "\n";
        if (func[i] == ' ') {
            ++i;
            continue;
        }
        if ((func[i] >= '0' && func[i] <= '9') || func[i] == '.') {
            number = readNumber(func, i);
            currentNode.reset(new ValueNode(number));
            std::cout << "got num: " << number << "!\n";
        } else if (func[i] == '(') {
            tmp = readInbrace(func, i);
            std::cout << "inbraced: " << tmp << "! Building new tree\n";
            currentNode = buildTree(tmp);
            //if (currentNode->type == NodeType::OPERATION) {
                //((OperationNode *)currentNode.get())->priority = 0;
            currentNode->priority = 0;
           //}
        } else {
            //tmp = readOperation(func, i);
            tmp = readWord(func, i);
            op = getOperation(tmp);
            if (op == Operation::NOT_AN_OPERATION) {
                Vars var = Vars::X;
                currentNode.reset(new VariableNode(var));
                std::cout << "got var: " << tmp << "!\n";
            } else {
                currentNode.reset(new OperationNode(op));
                currentNode->priority = getPriority(op);
                std::cout << "got operation: " << tmp << "!\n";
                //((OperationNode *)currentNode.get())->priority = getPriority(op);
            }
        }
        //std::cout << "read: " << tmp << "!\n";
        addToTree(node, currentNode);
    }
    return node;
}

FunctionalTree::FunctionalTree (const std::string &func) {
    root = buildTree(func);
}

FunctionalTree::FunctionalTree (FunctionalTree &&tree) {
    root = std::move(tree.root);
}

FunctionalTree::~FunctionalTree () {}

double FunctionalTree::func (double x) const {
    return getVal(root, x);
}

void FunctionalTree::printTree (const NodePtr &tmp) const {
    if (!tmp.get()) {
        return;
    }
    switch (tmp->type) {
        case NodeType::VALUE:
            std::cout << ((ValueNode *) tmp.get())->val;
            break;
        case NodeType::VARIABLE:
            std::cout << "x";
            break;
        case NodeType::OPERATION:
            std::cout << operations[static_cast<uint64_t>(((OperationNode *) tmp.get())->op)];
            break;
    }
    std::cout << "\n";
    if (tmp->left.get()) {
        printTree(tmp->left);
    } else {
        std::cout << "no left node\n";
    }
    if (tmp->right.get()) {
        printTree(tmp->right);
    } else {
        std::cout << "no right node\n";
    }
}

void FunctionalTree::printTree () const {
    printTree(root);
}

//void FunctionalTree::simplify () {}

FunctionalTree &FunctionalTree::operator= (FunctionalTree &&tree) {
    if (this == &tree) {
        return *this;
    }
    root = std::move(tree.root);
    return *this;
}