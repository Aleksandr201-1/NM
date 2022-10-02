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

VariableNode::VariableNode (uint64_t idx) : FunctionalTreeNode(NodeType::VARIABLE), idx(idx) {}
VariableNode::~VariableNode () {}

void FunctionalTree::inputCheck (const std::string &func, const std::vector<std::string> &vars) const {
    if (vars.size() > VARIABLE_LIMIT) {
        throw std::logic_error("Operation \"inputCheck\": count of vars limited by " + std::to_string(VARIABLE_LIMIT));
    }
    for (uint64_t i = 0; i < vars.size(); ++i) {
        std::vector<std::string>::const_iterator it = std::find(operations.cbegin(), operations.cend(), vars[i]);
        uint64_t idx = std::distance(operations.cbegin(), it);
        if (idx != operations.size()) {
            throw std::logic_error("Operation \"inputCheck\": used var name \"" + vars[i] + "\" which is a name of operation");
        }
    }
    for (uint64_t i = 0; i < vars.size(); ++i) {
        uint64_t count = std::count(vars.cbegin(), vars.cend(), vars[i]);
        if (count != 1) {
            throw std::logic_error("Operation \"inputCheck\": var name \"" + vars[i] + "\" used more than 1 time");
        }
    }
}

std::string FunctionalTree::readOperation (const std::string &func, uint64_t &i) const {
    std::string str;
    bool flag = true;
    while (i < func.size() && flag) {
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
                //i = func.size();
                flag = false;
                break;
        }
    }
    return str;
}

std::string FunctionalTree::readWord (const std::string &func, uint64_t &i) const {
    std::string str;
    //words
    //std::cout << "reading word...\n";
    while (((func[i] > 'A' && func[i] < 'Z') || (func[i] > 'a' && func[i] < 'z')) && i < func.size()) {
        str += func[i];
        //std::cout << "let: " << func[i] << "\n";
        ++i;
    }
    //+,-,*,/,%,^
    if (str.empty() && i < func.size()) {
        str = readOperation(func, i);
        //str += func[i];
        //++i;
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
        throw std::out_of_range("Operation \"readInbrace\": out of range. Incorrect placement of brackets");
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
    if (str == "**") {
        return Operation::POW;
    }
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

double FunctionalTree::getVal (const NodePtr &node, const std::vector<double> &X) const {
    if (!node->left.get() && !node->right.get()) {
        if (node->type == NodeType::VALUE) {
            ValueNode* value = (ValueNode*) node.get();
            return value->val;
        } else {
            VariableNode* var = (VariableNode*) node.get();
            return X[var->idx];
        }
    }
    OperationNode* operation = (OperationNode*) node.get();
    if (node->left && !node->right) {
        return useOperation(operation->op, getVal(operation->left, X), 0);
    }
    if (!node->left && node->right) {
        return useOperation(operation->op, getVal(operation->right, X), 0);
    }
    double a = getVal(node->left, X);
    double b = getVal(node->right, X);
    return useOperation(operation->op, a, b);
}

void FunctionalTree::addToTree (NodePtr &tree, NodePtr &toAdd) {
    if (!tree.get()) {
        tree.swap(toAdd);
        return;
    }
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
            }
            break;
        default:
            break;
    }
}

FunctionalTree::NodePtr FunctionalTree::buildTree (const std::string &func, const std::vector<std::string> &vars) {
    //std::cout << "Our func: " << func << "\n";
    std::string tmp;
    uint64_t i = 0;

    double num;
    Operation op;
    uint64_t idx;
    NodePtr currentNode, node;
    while (i < func.size()) {
        //std::cout << "new step: i = " << i << "\n";
        if (func[i] == ' ') {
            ++i;
            continue;
        }
        if ((func[i] >= '0' && func[i] <= '9') || func[i] == '.') {
            num = readNumber(func, i);
            currentNode.reset(new ValueNode(num));
            //std::cout << "got num: " << number << "!\n";
        } else if (func[i] == '(') {
            tmp = readInbrace(func, i);
            //std::cout << "inbraced: " << tmp << "! Building new tree\n";
            currentNode = buildTree(tmp, vars);
            //if (currentNode->type == NodeType::OPERATION) {
                //((OperationNode *)currentNode.get())->priority = 0;
            currentNode->priority = 0;
           //}
        } else {
            //tmp = readOperation(func, i);
            tmp = readWord(func, i);
            op = getOperation(tmp);
            if (op == Operation::NOT_AN_OPERATION) {
                std::vector<std::string>::const_iterator it = std::find(vars.cbegin(), vars.cend(), tmp);
                idx = std::distance(vars.begin(), it);
                if (idx == vars.size()) {
                    throw std::logic_error("Operation \"buildTree\": var \"" + tmp + "\" not found in var list");;
                }
                currentNode.reset(new VariableNode(idx));
                //std::cout << "got var: " << tmp << "!\n";
            } else {
                currentNode.reset(new OperationNode(op));
                currentNode->priority = getPriority(op);
                //std::cout << "got operation: " << tmp << "!\n";
                //((OperationNode *)currentNode.get())->priority = getPriority(op);
            }
        }
        //std::cout << "read: " << tmp << "!\n";
        addToTree(node, currentNode);
    }
    return node;
}

FunctionalTree::FunctionalTree (const std::string &func, const std::vector<std::string> &vars) {
    inputCheck(func, vars);
    root = buildTree(func, vars);
}

FunctionalTree::FunctionalTree (FunctionalTree &&tree) {
    root = std::move(tree.root);
}

FunctionalTree::~FunctionalTree () {}

double FunctionalTree::func (double x) const {
    return getVal(root, {x});
}

double FunctionalTree::func (const std::vector<double> &X) const {
    return getVal(root, X);
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