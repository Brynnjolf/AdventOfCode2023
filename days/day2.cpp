#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>


bool checkCubes(std::string numString, std::string color) {
    int num = std::stoi(numString);
    if(color == "blue" && num > 14) {
       return false; 
    } else if(color == "red" && num > 12) {
        return false;
    } else if(color == "green" && num > 13) {
        return false;
    }
    return true;
}

int isGamePossible(std::string& line) {
    //parse game Id vs game
    int delim = line.find(":");
    std::string idStr = line.substr(0, delim);
    std::string gameStr = line.substr(delim+1, line.size());

    std::vector<std::string> turns = {};

    std::stringstream gameSS(gameStr);
    std::string item;
    while(std::getline(gameSS, item, ';')) {
        turns.push_back(item);
    }

    int maxRed = 0;
    int maxBlue = 0;
    int maxGreen = 0;
    
    for(auto& turn : turns) {
        std::stringstream turnss(turn);
        while(std::getline(turnss, item, ',')) {
            int spaceDelim = item.find(" ", 1);
            std::string numStr = item.substr(1, spaceDelim-1);
            std::string color  = item.substr(spaceDelim+1, item.size());

            int num = std::stoi(numStr);
            if(color == "red") {
                maxRed = std::max(num, maxRed);
            } else if(color == "blue") {
                maxBlue = std::max(num, maxBlue);
            }else if(color == "green") {
                maxGreen = std::max(num, maxGreen);
            }
        }
    }
    
    return maxRed * maxGreen * maxBlue;
}

int solve(std::filesystem::path filePath) {
    std::ifstream file(filePath);
    std::string line;

    int result = 0;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            result += isGamePossible(line);
        }
    } else {
        std::cout << "error opening file\n";
    }
    return result;
}


int main() {
    std::cout << solve("../../inputDay2.txt") << std::endl;
    return 0;
}
