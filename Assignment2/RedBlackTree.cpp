#include <iostream>
using namespace std;

enum NodeColor { RED, BLACK };

class RBNode {
public:
    int key;
    NodeColor color;
    RBNode* parent;
    RBNode* left;
    RBNode* right;

    RBNode(int key) {
        this->key = key;
        this->color = RED;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class RBTree {
private:
    RBNode* root;

    void leftRotate(RBNode* node) {
        RBNode* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rightRotate(RBNode* node) {
        RBNode* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->right) {
            node->parent->right = leftChild;
        } else {
            node->parent->left = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixInsertion(RBNode* node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            RBNode* grandparent = node->parent->parent;
            if (node->parent == grandparent->left) {
                RBNode* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    rightRotate(grandparent);
                }
            } else {
                RBNode* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    leftRotate(grandparent);
                }
            }
        }
        root->color = BLACK;
    }

    void rebalanceAfterRemoval(RBNode* node) {
        while (node != root && (node == nullptr || node->color == BLACK)) {
            if (node == node->parent->left) {
                RBNode* sibling = node->parent->right;

                if (sibling != nullptr && sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }

                if (sibling != nullptr && sibling->color == BLACK &&
                    (sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    if (node->parent->color == RED) {
                        node->parent->color = BLACK;
                        break;
                    } else {
                        node = node->parent;
                    }
                } else {
                    if (sibling != nullptr) {
                        if (sibling->right == nullptr || sibling->right->color == BLACK) {
                            if (sibling->left != nullptr) {
                                sibling->left->color = BLACK;
                            }
                            sibling->color = RED;
                            rightRotate(sibling);
                            sibling = node->parent->right;
                        }

                        if (sibling->right != nullptr) {
                            sibling->right->color = BLACK;
                        }
                        sibling->color = node->parent->color;
                        node->parent->color = BLACK;
                        leftRotate(node->parent);
                        node = root;
                    }
                }
            } else {
                RBNode* sibling = node->parent->left;

                if (sibling != nullptr && sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }

                if (sibling != nullptr && sibling->color == BLACK &&
                    (sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    if (node->parent->color == RED) {
                        node->parent->color = BLACK;
                        break;
                    } else {
                        node = node->parent;
                    }
                } else {
                    if (sibling != nullptr) {
                        if (sibling->left == nullptr || sibling->left->color == BLACK) {
                            if (sibling->right != nullptr) {
                                sibling->right->color = BLACK;
                            }
                            sibling->color = RED;
                            leftRotate(sibling);
                            sibling = node->parent->left;
                        }

                        if (sibling->left != nullptr) {
                            sibling->left->color = BLACK;
                        }
                        sibling->color = node->parent->color;
                        node->parent->color = BLACK;
                        rightRotate(node->parent);
                        node = root;
                    }
                }
            }
        }
        if (node != nullptr) {
            node->color = BLACK;
        }
    }

    void removeNode(RBNode*& root, int key) {
        RBNode* current = root;

        while (current != nullptr) {
            if (current->key == key) {
                RBNode* nodeToRemove = current;

                if (nodeToRemove->left != nullptr && nodeToRemove->right != nullptr) {
                    RBNode* predecessor = nodeToRemove->left;
                    while (predecessor->right != nullptr) {
                        predecessor = predecessor->right;
                    }
                    swap(nodeToRemove->key, predecessor->key);
                    nodeToRemove = predecessor;
                }

                RBNode* child = (nodeToRemove->left != nullptr) ? nodeToRemove->left : nodeToRemove->right;

                if (child != nullptr) {
                    if (nodeToRemove->parent == nullptr) {
                        root = child;
                    } else if (nodeToRemove == nodeToRemove->parent->left) {
                        nodeToRemove->parent->left = child;
                    } else {
                        nodeToRemove->parent->right = child;
                    }
                    child->parent = nodeToRemove->parent;

                    if (nodeToRemove->color == BLACK) {
                        rebalanceAfterRemoval(child);
                    }
                    delete nodeToRemove;
                } else {
                    if (nodeToRemove->color == BLACK) {
                        rebalanceAfterRemoval(nodeToRemove);
                    }
                    if (nodeToRemove->parent != nullptr) {
                        if (nodeToRemove == nodeToRemove->parent->left) {
                            nodeToRemove->parent->left = nullptr;
                        } else {
                            nodeToRemove->parent->right = nullptr;
                        }
                    } else {
                        root = nullptr;
                    }
                    delete nodeToRemove;
                }
                return;
            }
            current = (key < current->key) ? current->left : current->right;
        }
    }

    void inorderTraversal(RBNode* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->key << " ";
        inorderTraversal(node->right);
    }

    void searchNode(RBNode* node, int key) {
        if (node == nullptr) {
            cout << "Value " << key << " not found in the tree.\n";
            return;
        }
        if (key == node->key) {
            cout << "Found " << key << " in the tree.\n";
            return;
        }
        if (key < node->key) {
            searchNode(node->left, key);
        } else {
            searchNode(node->right, key);
        }
    }

    void destroyTree(RBNode* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    RBTree() : root(nullptr) {}

    ~RBTree() {
        destroyTree(root);
    }

    void insert(int key) {
        RBNode* newNode = new RBNode(key);
        RBNode* parent = nullptr;
        RBNode* current = root;

        while (current != nullptr) {
            parent = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        newNode->parent = parent;
        if (parent == nullptr) {
            root = newNode;
        } else if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        newNode->left = nullptr;
        newNode->right = nullptr;

        fixInsertion(newNode);
    }

    void deleteKey(int key) {
        removeNode(root, key);
    }

    void search(int key) {
        searchNode(root, key);
    }

    void inorder() {
        inorderTraversal(root);
    }

    void displayTree(RBNode* root, int space = 0, int COUNT = 10) {
        if (root == nullptr)
            return;

        space += COUNT;

        displayTree(root->right, space);

        cout << endl;
        for (int i = COUNT; i < space; i++) {
            cout << " ";
        }

        cout << root->key << "(";
        cout << (root->color == RED ? "R" : "B") << ")" << endl;

        displayTree(root->left, space);
    }

    RBNode* getRoot() {
        return root;
    }
};

int main() {
    RBTree rbt;
    cout << "Red-Black Tree Demonstration\n";
    cout << "Inserting values: 10, 20, 30, 40, 50\n";
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(40);
    rbt.insert(50);
    cout << "Tree structure after insertions:\n";
    rbt.displayTree(rbt.getRoot());
    cout << "\nSearching for 30:\n";
    rbt.search(30);
    cout << "\nSearching for 60 (not present):\n";
    rbt.search(60);
    cout << "\nDeleting value 20:\n";
    rbt.deleteKey(20);
    cout << "Tree structure after deletion:\n";
    rbt.displayTree(rbt.getRoot());
    cout << "\nInorder traversal of the final tree:\n";
    rbt.inorder();
    cout << "\n";
    cout << "\nEnd of demonstration.\n";
    return 0;
}
