#include <algorithm>
#include <iostream>
#include <vector>
#include "SkipList.h"

using namespace std;

class Game {
private:
    SkipList leaderboard;

public:
    Game(int maxLevel, float probability) : leaderboard(maxLevel, probability) {}

    void addPlayer(int playerId) {
        if (leaderboard.search(playerId)) {
            cout << "Player " << playerId << " already exists.\n";
            return;
        }
        leaderboard.insert(playerId);
        cout << "Player " << playerId << " added with initial score 1.\n";
    }

    void removePlayer(int playerId) {
        Player* player = leaderboard.search(playerId);
        if (player) {
            leaderboard.remove(playerId);
            cout << "Player " << playerId << " removed.\n";
        } else {
            cout << "Player " << playerId << " not found.\n";
        }
    }

    void getTopNPlayers(int N) {
        vector<Player*> players;
        Player* current = leaderboard.header->forward[0];
        while (current != nullptr) {
            players.push_back(current);
            current = current->forward[0];
        }

        sort(players.begin(), players.end(), [](const Player* a, const Player* b) {
            return a->score > b->score;
        });

        cout << "Top " << N << " players:\n";
        for (int i = 0; i < min(N, (int)players.size()); i++) {
            cout << "Player " << players[i]->player_id << ", Score: " << players[i]->score << "\n";
        }
    }

    void getPlayerScore(int playerId) {
        Player* player = leaderboard.search(playerId);
        if (player) {
            cout << "Player " << playerId << " has score " << player->score << ".\n";
        } else {
            cout << "Player " << playerId << " not found.\n";
        }
    }
};

int main() {
    srand(time(0)); 
    Game game(100, 0.5);

    game.addPlayer(1);
    game.addPlayer(2);
    game.addPlayer(3);
    game.addPlayer(5);
    game.addPlayer(7);
    game.addPlayer(4);
    game.addPlayer(13);
    game.addPlayer(10);
    game.addPlayer(14);
    game.addPlayer(17);
    game.getTopNPlayers(6);
    game.getPlayerScore(1);
    game.removePlayer(2);
    game.removePlayer(3);
    game.removePlayer(5);
    game.getTopNPlayers(6);

    return 0;
}
