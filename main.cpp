#include <iostream>
#include <iomanip>

using namespace std;

struct Node
{
    int value;
    int depth = 1;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(const int value)
    {
        this->value = value;
    }
};

struct BST
{
    ~BST()
    {
        clear();
    }

    void display()
    {
        displayRecursive(root);
    }

    void printPreOrder()
    {
        printPreOrderRecursive(root);
        cout << endl;
    }

    void printInOrder()
    {
        printInOrderRecursive(root);
        cout << endl;
    }

    void printPostOrder()
    {
        printPostOrderRecursive(root);
        cout << endl;
    }

    bool isEmpty()
    {
        return root;
    }

    void removeEven()
    {
        root = removeEvenRecursive(root);
    }

    void pop(const int key)
    {
        root = popRecursive(root, key);
    }

    void push(const int key)
    {
        root = pushRecursive(root, key);
    }

    void clear()
    {
        destroy(root);
        root = nullptr;
    }

private:
    Node* root = nullptr;

    void displayRecursive(const Node* node, const int width = 0)
    {
        if (!node) return;
        cout << setiosflags(ios::right);
        displayRecursive(node->right, width + 5);
        cout << setw(width) << node->value;
        if (node->left || node->right) cout << '<';
        cout << endl;
        displayRecursive(node->left, width + 5);
    }

    void printPreOrderRecursive(const Node* node)
    {
        if (!node) return;
        cout << node->value << ' ';
        printPreOrderRecursive(node->left);
        printPreOrderRecursive(node->right);
    }

    void printInOrderRecursive(const Node* node)
    {
        if (!node) return;
        printInOrderRecursive(node->left);
        cout << node->value << ' ';
        printInOrderRecursive(node->right);
    }

    void printPostOrderRecursive(const Node* node)
    {
        if (!node) return;
        printPostOrderRecursive(node->left);
        printPostOrderRecursive(node->right);
        cout << node->value << ' ';
    }

    Node* removeEvenRecursive(Node* node)
    {
        if (!node) return node;
        if (node->value % 2 == 0)
            node = removeEvenRecursive(popRecursive(node, node->value));
        if (node)
        {
            node->left = removeEvenRecursive(node->left);
            node->right = removeEvenRecursive(node->right);
        }
        return node;
    }

    Node* popRecursive(Node* node, const int key)
    {
        if (!node) return node;
        if (key < node->value)
            node->left = popRecursive(node->left, key);
        else if (key > node->value)
            node->right = popRecursive(node->right, key);
        else {
            if (!node->right) return node->left;
            Node* subNode = getMax(node->left);
            subNode->left = detachMaxNode(node->left);
            subNode->right = node->right;
            delete node;
            return balance(subNode);
        }
        return balance(node);
    }

    Node* detachMaxNode(Node* node)
    {
        if (!node->right) return node->left;
        node->right = detachMaxNode(node->right);
        return balance(node);
    }

    Node* pushRecursive(Node* node, const int key)
    {
        if (!node)
            return new Node(key);
        if (key < node->value)
            node->left = pushRecursive(node->left, key);
        else if (key > node->value)
            node->right = pushRecursive(node->right, key);
        else
        {
            cerr << "Values should be unique!" << endl;
            throw invalid_argument("Values should be unique!");
        }
        return balance(node);
    }

    Node* balance(Node* node)
    {
        updateDepth(node);
        int balanceFactor = getBalance(node);
        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        else if (balanceFactor < -1) {
            if (getBalance(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* rotateLeft(Node* node)
    {
        if (!(node && node->right))
            return node;
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateDepth(node);
        updateDepth(newRoot);
        return newRoot;
    }

    Node* rotateRight(Node* node)
    {
        if (!(node && node->left))
            return node;
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateDepth(node);
        updateDepth(newRoot);
        return newRoot;
    }

    int getBalance(const Node* node)
    {
        return getDepth(node->left) - getDepth(node->right);
    }

    void updateDepth(Node* node)
    {
        if (node)
            node->depth = max(getDepth(node->left), getDepth(node->right)) + 1;
    }

    int getDepth(const Node* node)
    {
        if (!node) return 0;
        return node->depth;
    }

    Node* getMax(Node* node)
    {
        Node* curNode = node;
        while (curNode && curNode->right)
            curNode = curNode->right;
        return curNode;
    }

    void destroy(Node* node)
    {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

int main()
{
    BST tree;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    cin.ignore(1000, '\n');

    int insertValue;
    for (int i = 0; i < n; i++)
    {
        cout << "Push element << ";
        cin >> insertValue;
        cin.ignore(1000, '\n');
        tree.push(insertValue);
    }

    cout << "Your tree:\n" << endl;
    tree.display();
    cout << "\nPre-order:\n    ";
    tree.printPreOrder();
    cout << "In-order:\n    ";
    tree.printInOrder();
    cout << "Post-order:\n    ";
    tree.printPostOrder();

    tree.removeEven();
    cout << "\nOnly odd numbers:\n" << endl;
    tree.display();

    tree.clear();

    return 0;
}
