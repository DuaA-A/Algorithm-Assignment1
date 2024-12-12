#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

class Node {
public:
    int key;
    Node** forward;

    Node(int key, int level) {
        this->key = key;
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; i++) {
            forward[i] = nullptr;
        }
    }

    ~Node() {
        delete[] forward;
    }
};

class SkipList {
private:
    int maxLevel;
    int currentLevel;
    float probability;
    Node* header;

    int randomLevel() {
        int level = 0;
        while (((float)rand() / RAND_MAX) < probability && level < maxLevel) {
            level++;
        }
        return level;
    }

public:
    SkipList(int maxLevel, float probability) {
        this->maxLevel = maxLevel;
        this->probability = probability;
        this->currentLevel = 0;
        header = new Node(-1, maxLevel);
    }

    ~SkipList() {
        Node* current = header;
        while (current) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    void insert(int key) {
        Node** update = new Node*[maxLevel + 1];
        Node* current = header;

        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current == nullptr || current->key != key) {
            int level = randomLevel();
            if (level > currentLevel) {
                for (int i = currentLevel + 1; i <= level; i++) {
                    update[i] = header;
                }
                currentLevel = level;
            }

            Node* newNode = new Node(key, level);
            for (int i = 0; i <= level; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }

        delete[] update;
    }

    void remove(int key) {
        Node** update = new Node*[maxLevel + 1];
        Node* current = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current != nullptr && current->key == key) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }

            delete current;

            while (currentLevel > 0 && header->forward[currentLevel] == nullptr) {
                currentLevel--;
            }
        }

        delete[] update;
    }

    bool search(int key) {
        Node* current = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];

        return current != nullptr && current->key == key;
    }

    void display() {
        for (int i = 0; i <= currentLevel; i++) {
            Node* node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->key << " ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }
};

int main() {
    srand(time(0));

    SkipList skipList(5, 0.5);

    skipList.insert(3);
    skipList.insert(6);
    skipList.insert(7);
    skipList.insert(9);
    skipList.insert(12);
    skipList.insert(19);

    cout << "Skip List after insertion:" << endl;
    skipList.display();

    cout << "\nSearching for 6: " << (skipList.search(6) ? "Found" : "Not Found") << endl;
    cout << "Searching for 15: " << (skipList.search(15) ? "Found" : "Not Found") << endl;

    skipList.remove(6);
    cout << "\nSkip List after deleting 6:" << endl;
    skipList.display();

    return 0;
}
