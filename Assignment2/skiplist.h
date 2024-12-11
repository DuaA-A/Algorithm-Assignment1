#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Node {
public:
    int key;
    int value;
    vector<Node*> forward;
    Node(int key, int value, int level)
        : key(key), value(value), forward(level + 1, nullptr) {}
};

class SkipList {
private:
    int maxLevel;
    float probability;
    int currentLevel;
    Node* header;
    int randomLevel() {
        int level = 0;
        while (((float)rand() / RAND_MAX) < probability && level < maxLevel) 
            level++;
        return level;
    }

public:
    SkipList(int maxLevel, float probability)
        : maxLevel(maxLevel), probability(probability), currentLevel(0) {
        header = new Node(-1, -1, maxLevel);
        srand((unsigned)time(0)); 
    }

    ~SkipList() {
        Node* current = header;
        while (current) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    void insert(int key, int value) {
        vector<Node*> update(maxLevel + 1, nullptr);
        Node* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) 
                current = current->forward[i];
            update[i] = current;
        }
        current = current->forward[0];
        if (current == nullptr || current->key != key) {
            int level = randomLevel();
            if (level > currentLevel) {
                for (int i = currentLevel + 1; i <= level; i++) 
                    update[i] = header;
                currentLevel = level;
            }
            Node* newNode = new Node(key, value, level);
            for (int i = 0; i <= level; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    void remove(int key, int value) {
        vector<Node*> update(maxLevel + 1, nullptr);
        Node* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) 
                current = current->forward[i];
            update[i] = current;
        }
        current = current->forward[0];
        if (current && current->key == key && current->value == value) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != current) 
                    break;
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            while (currentLevel > 0 && header->forward[currentLevel] == nullptr) 
                currentLevel--;
        }
    }

    vector<pair<int, int>> getTopN(int N) {
        vector<pair<int, int>> result;
        Node* current = header->forward[0];
        while (current && N > 0) {
            result.emplace_back(current->key, current->value);
            current = current->forward[0];
            N--;
        }
        return result;
    }
};

#endif 
