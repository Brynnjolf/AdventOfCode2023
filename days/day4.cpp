#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <filesystem>
#include <utility>
#include <vector>

typedef std::vector<std::pair<std::vector<int>,std::vector<int>>> Game;

void parseLine(std::string line, Game& game) {
    int left = line.find(":");
    int middle = line.find("|");
    std::string winningNumsStr = line.substr(left+2, middle-left-3);
    std::string playerNumsStr = line.substr(middle+2);

    std::stringstream ss(winningNumsStr);
    std::stringstream ss2(playerNumsStr);
    int item;

    std::vector<int> winningNums = {};
    std::vector<int> playerNums = {};
        
    while(ss >> item) {
        winningNums.push_back(item);
    }
    while(ss2 >> item) {
        playerNums.push_back(item);
    }

    game.push_back(std::make_pair(winningNums, playerNums));
}

int processCard(Game game, int card) {
    std::vector<int> winningNums = game[card].first;
    std::vector<int> playerNums = game[card].second;

    int newCards = 0;
    for(int curr : playerNums) {
        if(std::find(winningNums.begin(), winningNums.end(), curr) != winningNums.end()) {
            newCards++;
        }
    }

    return newCards;
}

int solve(std::filesystem::path filePath) {
    std::ifstream file(filePath);
    std::string line;

    Game game;
    int result = 0;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            parseLine(line, game);
        }
    } else {
        std::cout << "failed to open file!\n";
    }

    std::vector<int> numberCounts(game.size(), 1);

    for(int i = 0; i < game.size(); i++) {
        std::vector<int>& winningNums = game[i].first;
        std::vector<int>& playerNums = game[i].second;

        for(int j = 0; j < numberCounts[i]; j++) {
            int offset = 1;
            for(int curr : playerNums) {
                if((i+offset) < game.size() && std::find(winningNums.begin(), winningNums.end(), curr) != winningNums.end()) {
                    numberCounts[i+offset]++;
                    offset++;
                }
            }

        }
    }

    return std::accumulate(numberCounts.begin(), numberCounts.end(), 0);
}

int main() {
    std::cout << solve("../../inputDay4.txt") << std::endl;
    return 0;
}
