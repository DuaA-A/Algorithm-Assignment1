#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

template <typename T>
struct Node {
    T value;
    vector<Node*> forward;
    Node(T value, int level) : value(value), forward(level + 1, nullptr) {}
};

template <typename T>
class SkipList {
private:
    int maxLevel;
    float probability;
    int currentLevel;
    Node<T>* header;
    int randomLevel() {
        int level = 0;
        while (((float)rand() / RAND_MAX) < probability && level < maxLevel) 
            level++;
        return level;
    }

public:
    SkipList(int maxLevel, float probability)
        : maxLevel(maxLevel), probability(probability), currentLevel(0) {
        T dummy = {}; 
        header = new Node<T>(dummy, maxLevel);
    }
    ~SkipList() {
        Node<T>* current = header;
        while (current) {
            Node<T>* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    void insert(T value) {
        vector<Node<T>*> update(maxLevel + 1);
        Node<T>* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) 
                current = current->forward[i];
            update[i] = current;
        }
        current = current->forward[0];
        if (!current || !(current->value == value)) {
            int level = randomLevel();
            if (level > currentLevel) 
                for (int i = currentLevel + 1; i <= level; i++) 
                    update[i] = header;
                currentLevel = level;
            Node<T>* newNode = new Node<T>(value, level);
            for (int i = 0; i <= level; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    void remove(T value) {
        vector<Node<T>*> update(maxLevel + 1);
        Node<T>* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) 
                current = current->forward[i];
            update[i] = current;
        }
        current = current->forward[0];
        if (current && current->value == value) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != current) break;
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            while (currentLevel > 0 && !header->forward[currentLevel])
                currentLevel--;
        }
    }
    T* search(T value) {
        Node<T>* current = header;
        for (int i = currentLevel; i >= 0; i--) 
            while (current->forward[i] && current->forward[i]->value < value) 
                current = current->forward[i];
        current = current->forward[0];
        if (current && current->value == value) 
            return &current->value;
        return nullptr;
    }

    vector<T> getAllValues() {
        vector<T> values;
        Node<T>* current = header->forward[0];
        while (current) {
            values.push_back(current->value);
            current = current->forward[0];
        }
        return values;
    }
};

struct Player {
    int playerId;
    int score;
    // bool operator<(const Player& other) const {
    //     return score < other.score; 
    // }
    bool operator<(const Player& other) const {
        return playerId < other.playerId; 
    }
    bool operator==(const Player& other) const {
        return playerId == other.playerId;
    }
};

class Game {
private:
    SkipList<Player> leaderboard;

public:
    Game(int maxLevel, float probability) : leaderboard(maxLevel, probability) {}

    void addPlayer(int playerId, int score) {
        if (leaderboard.search({playerId, score})) {
        cout << "Player " << playerId << " already exists.\n";
            return;
        }
        Player player = {playerId, score};
        leaderboard.insert(player);
        cout << "Player " << playerId << " added with score " << score << ".\n";
    }

    void updatePlayerScore(int playerId, int newScore) {
        Player* player = leaderboard.search({playerId, 0});
        if (!player) {
            cout << "Player " << playerId << " not found.\n";
            return;
        }
        leaderboard.remove(*player);
        Player updatedPlayer = {playerId, newScore};
        leaderboard.insert(updatedPlayer);
        cout << "Player " << playerId << " score updated to " << newScore << ".\n";
    }

    void deletePlayer(int playerId) {
        Player* player = leaderboard.search({playerId, 0});
        if (!player) {
            cout << "Player " << playerId << " not found.\n";
            return;
        }
        leaderboard.remove(*player);
        cout << "Player " << playerId << " removed.\n";
    }

    void getTopPlayers(int N) {
        vector<Player> players = leaderboard.getAllValues();
        sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
            return b.score < a.score; 
        });
        cout << "Top " << N << " players:\n";
        for (int i = 0; i < min(N, (int)players.size()); i++) {
            cout << "Player ID: " << players[i].playerId << ", Score: " << players[i].score << "\n";
        }
    }
};

int main() {
    srand(time(0));
    Game game(10, 0.5);
    game.addPlayer(1, 50);
    game.addPlayer(2, 30);
    game.addPlayer(3, 70);
    game.addPlayer(4, 70);
    game.addPlayer(5, 60);
    game.addPlayer(7, 10);
    game.addPlayer(6, 60);
    game.addPlayer(9, 160);
    game.getTopPlayers(3);
    game.updatePlayerScore(2, 80);
    game.updatePlayerScore(5, 100);
    game.getTopPlayers(5);
    game.deletePlayer(1);
    game.getTopPlayers(3);

    return 0;
}
