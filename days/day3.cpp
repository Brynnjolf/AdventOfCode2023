#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


std::string numbers = "0123456789";

bool check(std::vector<std::string>& schematic, int row, int col) {
    if(row < 0 || row >= schematic.size() || col < 0 || col >= schematic[0].size()) {
        return false;
    }
    if(std::isdigit(schematic[row][col])) {
        return false;
    }
    if(schematic[row][col] == '.') {
        return false;
    }

    schematic[row][col] = 'X';

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

    for(auto& coord : coordsToCheck) {
        if(check(schematic, coord[0], coord[1])) {
            return true;
        }
    }

    return false;
}

int solve(std::filesystem::path filePath) {
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

    int result = 0;

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

    return result;
}

int main() {
    int result = solve("../../inputDay3.txt");
    std::cout << result << std::endl;
    return 0;
}
