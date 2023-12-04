#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>


std::string numbers = "0123456789";
std::map<std::pair<int,int>, std::vector<int>> gearLocations = {};

bool check(std::vector<std::string>& schematic, int row, int col, int rootNum) {
    if(row < 0 || row >= schematic.size() || col < 0 || col >= schematic[0].size()) {
        return false;
    }
    if(std::isdigit(schematic[row][col])) {
        return false;
    }
    if(schematic[row][col] == '.') {
        return false;
    }

    if(schematic[row][col] == '*') {
        if(gearLocations.count({row,col}) > 0) {
            gearLocations.at({row,col}).push_back(rootNum);
        } else {
            std::pair<int,int> coords = {row,col};
            std::vector<int> numasvec = {rootNum};
            gearLocations.emplace(coords, numasvec);
        }
    }

    return true;
}

bool checkPerimeter(std::vector<std::string>& schematic, int row, int left, int right) {
    std::vector<std::vector<int>> coordsToCheck = {};

    coordsToCheck.push_back({row, left-1});
    coordsToCheck.push_back({row-1, left-1});
    coordsToCheck.push_back({row+1, left-1});

    for(int i = left; i < right; i++) {
        coordsToCheck.push_back({row-1, i});
        coordsToCheck.push_back({row+1, i});
    }

    coordsToCheck.push_back({row, right});
    coordsToCheck.push_back({row-1, right});
    coordsToCheck.push_back({row+1, right});


    std::string substr = schematic[row].substr(left, right-left);
    int num = std::stoi(substr);

    for(auto& coord : coordsToCheck) {
        if(check(schematic, coord[0], coord[1], num)) {
            return true;
        }
    }

    return false;
}

void solve(std::filesystem::path filePath, int& result, int& gear_ratio) {
    std::ifstream file(filePath);
    std::string inputLine;

    std::vector<std::string> schematic = {};

    if(file.is_open()) {
        while(std::getline(file, inputLine)) {
            schematic.push_back(inputLine);
        }
    } else {
        std::cout << "failed to open file\n";
    }


    for(int i = 0; i < schematic.size(); i++) {
        int left = schematic[i].find_first_of(numbers);
        int right = schematic[i].find_first_not_of(numbers, left);
        while(left != std::string::npos) {
            if(checkPerimeter(schematic, i, left,right)) {
                std::string substr = schematic[i].substr(left, right-left);
                result += std::stoi(substr);
            }
            left = schematic[i].find_first_of(numbers, right);
            right = schematic[i].find_first_not_of(numbers, left);
        }

    }

    for(auto& [gearCoords, gearNumbers] : gearLocations) {
       if(gearNumbers.size() == 2)  {
           gear_ratio += gearNumbers[0] * gearNumbers[1];
       }
    }
}

int main() {
    int result = 0;
    int gear_ratio = 0;
    solve("../../inputDay3.txt", result, gear_ratio);
    std::cout << result << std::endl;
    std::cout << gear_ratio << std::endl;

    return 0;
}
