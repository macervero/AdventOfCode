#include <iostream>
#include <fstream>
#include <string>

int problem01Solver(std::string filename);
int problem02Solver(std::string filename);
int getCallibrationValue(std::string line);

int main(int argc, char** argv) {
    std::string filename;
    bool executeBoth = false;
    int sum;

    if(argc == 1) executeBoth = true;
    
    if(executeBoth || *argv[1] == '1') {
        filename = "input1_day01.txt";
        sum = problem01Solver(filename);
        if(sum == -1) std::cerr << filename << " can not be opened\n";
        else std::cout << sum << "\n";
    }

    if(executeBoth || *argv[1] == '2') {
        filename = "input2_day01.txt";
        sum = problem02Solver(filename);
        if(sum == -1) std::cerr << filename << " can not be opened\n";
        else std::cout << sum << "\n";
    }

    return 0;
}

int problem01Solver(std::string filename) {
    std::string line;
    std::ifstream ifile(filename);
    int sum = 0;

    if(!ifile.is_open()) return -1;
    else {
        while(!ifile.eof()) {
            ifile >> line;
            sum += getCallibrationValue(line);
        }
    }

    ifile.close();
    return sum;
}

int problem02Solver(std::string filename) {
    std::string line;
    std::ifstream ifile(filename);
    std::string patterns_text[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::string numbers[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    
    int pos, maxpos, minpos, maxval, minval, sum = 0, capacity = sizeof(patterns_text)/sizeof(std::string);

    if(!ifile.is_open()) return -1;
    else {
        int curline = 0;
        while(!ifile.eof()) {
            ifile >> line;

            maxpos = -1;
            minpos = line.size();
            for(int i=0; i<capacity; i++) {
                pos = line.find(patterns_text[i]);
                if(pos != -1 && pos < minpos) {
                    minpos = pos;
                    minval = i;
                }

                pos = line.rfind(patterns_text[i]);
                if(pos != -1 && pos > maxpos) {
                    maxpos = pos;
                    maxval = i;
                }
            }

            if(maxpos != -1 || maxpos == minpos) line = line.substr(0, maxpos) + numbers[maxval] + line.substr(maxpos, line.size()-maxpos);
            if(minpos != line.size() && maxpos != minpos) line = line.substr(0, minpos) + numbers[minval] + line.substr(minpos, line.size()-minpos);

            sum += getCallibrationValue(line);
        }
    }

    ifile.close();
    return sum;
}

int getCallibrationValue(std::string line) {
    int pos = 0, num;
    while(line[pos]<'0' || line[pos]>'9') pos++;
    num = std::stoi(std::string(1, line[pos])) * 10;

    pos = line.size()-1;
    while(line[pos]<'0' || line[pos]>'9') pos--;
    num += std::stoi(std::string(1, line[pos]));

    return num;
}