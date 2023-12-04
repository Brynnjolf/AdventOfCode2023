#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <vector>

int getPointValue(std::string line) {
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

    int points = 0;
    for(int currNum : playerNums) {
        if(std::find(winningNums.begin(), winningNums.end(), currNum) != winningNums.end()) {
            if(points == 0) {
                points++;
            } else {
                points *= 2;
            }
        }
    }

    return points;
}

int solve(std::filesystem::path filePath) {
    std::ifstream file(filePath);
    std::string line;

    int result = 0;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            result += getPointValue(line);
        }
    } else {
        std::cout << "failed to open file!\n";
    }

    return result;
}

int main() {
    
    std::cout << solve("../../inputDay4.txt") << std::endl;
    return 0;
}
