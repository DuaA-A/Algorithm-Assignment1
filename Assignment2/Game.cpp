#include <iostream>
#include <unordered_map>
#include <vector>
#include "SkipList.h"  

using namespace std;

class Game {
private:
    SkipList leaderboard;
    unordered_map<int,int> players;

public:
    Game(int maxLevel,float probability):leaderboard(maxLevel,probability){}

    void addOrUpdatePlayer(int playerId,int score){
        if (players.find(playerId)!=players.end()) {
            leaderboard.remove(playerId,players[playerId]);
        }
        players[playerId] = score;
        leaderboard.insert(playerId, score);
    }

    void changePlayerScore(int playerId, int delta) {
        if (players.find(playerId)!=players.end()){
            int newScore=players[playerId]+delta;
            leaderboard.remove(playerId,players[playerId]);
            players[playerId]=newScore;
            leaderboard.insert(playerId,newScore);
        } 
        else
            cout<<"player not found\n";
    }

    void removePlayer(int playerId){
        if (players.find(playerId)!=players.end()){
            leaderboard.remove(playerId,players[playerId]);
            players.erase(playerId);
        } 
        else 
            cout<<"player not found\n";
    }

    void getTopNPlayers(int N) {
        vector<pair<int,int>> topPlayers=leaderboard.getTopN(N);
        if (topPlayers.empty()) {
            cout<<"no players found!\n";
            return;
        }
        cout<<"top "<<N<<" Players:\n";
        for (const auto& player : topPlayers) 
            cout<<"Player ID: "<<player.first<<" | Score: "<<player.second<<"\n";
    }

    void getPlayerScore(int playerId) {
        if(players.find(playerId)!=players.end()) 
            cout<<"Player ID: "<<playerId<<" | Score: "<<players[playerId]<<"\n";
        else
            cout<<"player not found\n";
    }
};

void getInput(int& value, const string& prompt) {
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again.\n" << prompt;
    }
}

int main() {
    Game game(10,0.5); 
    int choice;

    do {
        cout<<"\n1. Add/Update Player\n2. Remove Player\n3. Change Player Score\n4. Get Top N Players\n5. Get Player Score\n0. Exit\nChoice: ";
        cin>>choice;

        if (choice==1){
            int playerId, score;
            getInput(playerId, "Enter Player ID: ");
            getInput(score, "Enter Score: ");
            game.addOrUpdatePlayer(playerId, score);
        }
        else if (choice==2){
            int playerId;
            getInput(playerId, "Enter Player ID to Remove: ");
            game.removePlayer(playerId);
        }
        else if (choice==3) {
            int playerId, delta;
            getInput(playerId, "Enter Player ID: ");
            getInput(delta, "Enter Score Change (+/-): ");
            game.changePlayerScore(playerId, delta);
        } 
        else if (choice==4) {
            int N;
            getInput(N, "Enter N: ");
            game.getTopNPlayers(N);
        } 
        else if (choice==5) {
            int playerId;
            getInput(playerId, "Enter Player ID: ");
            game.getPlayerScore(playerId);
        } 
        else if (choice==0)    break;
        else 
            cout << "Invalid. Try again.\n";
    }while(choice != 0);

    return 0;
}
