#include <cctype>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

std::map<std::string,std::string> numberMap =  {
    {"one", "o1e"},
    {"two", "t2o"},
    {"three", "th3ee"},
    {"four", "fo4r"},
    {"five", "f5ve"},
    {"six", "s6x"},
    {"seven", "se7en"},
    {"eight", "ei8ht"},
    {"nine", "n9ne"},
};

void formatNumberString(std::string& line) {
    for(auto& [num, formattedNum] : numberMap) {
        int idx = line.find(num);
        while(idx != std::string::npos) {
            line.replace(idx, num.size(), formattedNum);
            idx = line.find(num, idx+1);
        }
    }
}

int getNumFromLine(std::string line) {
    int lo = 0;
    int hi = line.size() - 1;

    formatNumberString(line);

    while(lo < hi && (!std::isdigit(line[lo]) || !std::isdigit(line[hi]))) {
        if(!std::isdigit(line[lo])) {
            lo++;
        }
        if(!std::isdigit(line[hi])) {
            hi--;
        }
    }
    return std::stoi(std::string(1, line[lo]) + line[hi]);
}

int getSumOfLines(std::filesystem::path filePath) {
    std::ifstream file(filePath);
    std::string line;

    int result = 0;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            int num = getNumFromLine(line);
            result += num;
        }
    } else {
        std::cout << "error opening file\n";
    }
    return result;
}

int main()
{
    int result = getSumOfLines("../../inputDay1.txt");
    std::cout << result << std::endl;
	return 0;
}
