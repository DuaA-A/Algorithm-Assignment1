#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Player {
public:
    int player_id;
    int score;
    Player** forward;

    Player(int player_id, int level) {
        this->player_id = player_id;
        this->score = level;  // Set score to level
        forward = new Player*[level + 1];
        for (int i = 0; i <= level; i++) forward[i] = nullptr;
    }

    ~Player() { delete[] forward; }
};

class SkipList {
public:
    int maxLevel;
    int currentLevel;
    float probability;
    Player* header;

    int randomLevel() {
        int level = 0;
        while (((float)rand() / RAND_MAX) < probability && level < maxLevel)
            level++;
        return level;
    }

public:
    SkipList(int maxLevel, float probability)
        : maxLevel(maxLevel), probability(probability), currentLevel(0) {
        header = new Player(-1, maxLevel);
    }

    ~SkipList() { delete header; }

    void insert(int player_id) {
        Player* current = header;
        vector<Player*> update(maxLevel + 1);

        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr &&
                    current->forward[i]->player_id < player_id) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current == nullptr || current->player_id != player_id) {
            int level = randomLevel();
            if (level > currentLevel) {
                for (int i = currentLevel + 1; i <= level; i++) {
                    update[i] = header;
                }
                currentLevel = level;
            }

            Player* newNode = new Player(player_id, level);
            for (int i = 0; i <= level; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    void remove(int player_id) {
        Player* current = header;
        vector<Player*> update(maxLevel + 1);

        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->player_id < player_id)
                current = current->forward[i];
            update[i] = current;
        }

        current = current->forward[0];
        if (current != nullptr && current->player_id == player_id) {
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

    Player* search(int player_id) {
        Player* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->player_id < player_id)
                current = current->forward[i];
        }
        current = current->forward[0];
        if (current != nullptr && current->player_id == player_id) {
            return current;
        }
        return nullptr;
    }

    void display() {
        for (int i = 0; i <= currentLevel; i++) {
            Player* node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << "(" << node->player_id << ", " << node->score << ") ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }

    void updateScore(int player_id, int newLevel) {
        Player* player = search(player_id);
        if (player) {
            remove(player_id);
            insert(player_id);
        }
    }
};

#endif
