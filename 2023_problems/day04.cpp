#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int problem01Solver(std::string filename);
int problem02Solver(std::string filename);
void matchLists(std::string line, std::vector<int>* matchNums);

const std::string DATA_FOLDER = "data/";
const std::string INPUT_FILE = "input_day04.txt";
const std::string TEST_FILE = "test_day04.txt";

int main(int argc, char** argv) {
    std::string filename;
    bool executeBoth = false;
    int sum;

    if(argc == 1 ||
        (argc == 2 && (*argv[1] != 't' && *argv[1] != 'i')) ||
        (argc == 3 && ((*argv[1] != 't' && *argv[1] != 'i') || (*argv[2] != '1' && *argv[2] != '2'))) ||
        argc > 3) {
        std::cout << "This program must be executed as follows:\n"
                        "\t\t./day04.out FILE_TYPE [PROBLEM]\n\n"
                        "FILE_TYPE: t (for testing); i (for real input)\n"
                        "PROBLEM: 1 (for problem 1); 2 (for problem 2); nothing for both problems at the same time" << std::endl;
        return 0;
    }

    if(argc == 2) executeBoth = true;
    if(executeBoth || *argv[2] == '1') {
        if(*argv[1] == 't') filename = DATA_FOLDER + TEST_FILE;
        else filename = DATA_FOLDER + INPUT_FILE;

        sum = problem01Solver(filename);
        if(sum == -1) std::cerr << filename << " can not be opened" << std::endl;
        else std::cout << sum << std::endl;
    }

    if(executeBoth || *argv[2] == '2') {
        if(*argv[1] == 't') filename = DATA_FOLDER + TEST_FILE;
        else filename = DATA_FOLDER + INPUT_FILE;

        sum = problem02Solver(filename);
        if(sum == -1) std::cerr << filename << " can not be opened" << std::endl;
        else std::cout << sum << std::endl;
    }

    return 0;
}

int problem01Solver(std::string filename) {
    std::string line;
    std::ifstream ifile(filename);
    std::vector<int> matchNums;
    int worth, sum = 0;

    if(!ifile.is_open()) return -1;
    else {
        while(std::getline(ifile, line)) {
            matchNums.clear();
            matchLists(line, &matchNums);            

            worth = 0;
            for(unsigned int i=0; i<matchNums.size(); i++) {
                if(worth == 0) worth++;
                else worth *= 2;
            }

            sum += worth;
        }
    }

    return sum;
}

int problem02Solver(std::string filename) {
    std::string line;
    std::ifstream ifile(filename);
    std::vector<int> matchNums, nmatches, repetedLines;
    int nlines, nline;

    if(!ifile.is_open()) return -1;
    else {
        nlines = 0;
        while(std::getline(ifile, line)) {
            matchNums.clear();
            matchLists(line, &matchNums);
            
            repetedLines.push_back(nlines);
            nmatches.push_back(matchNums.size());          

            nlines++;
        }

        for(unsigned int i=0; i<repetedLines.size(); i++) {
            for(unsigned int j=1; j<=nmatches[repetedLines[i]]; j++) {
                if(repetedLines[i] + j < nlines) {
                    repetedLines.push_back(repetedLines[i] + j);
                }
            }
        }
    }

    return repetedLines.size();
}


void matchLists(std::string line, std::vector<int>* matchNums) {
    std::string winnerList, ownList;
    std::vector<int> winnerNums, ownNums;
    int pos, ipos, epos;

    pos = line.find(":");
    winnerList = line.substr(pos+1);

    pos = winnerList.find("|");
    ownList = winnerList.substr(pos+1) + " ";
    winnerList = winnerList.substr(0, pos);

    winnerNums.clear();
    ipos = 1;
    epos = winnerList.find(" ", ipos);
    do {
        if(ipos != epos) winnerNums.push_back(std::stoi(winnerList.substr(ipos, epos-ipos)));
        ipos = epos+1;
        epos = winnerList.find(" ", ipos);
    } while(epos != std::string::npos);

    ownNums.clear();
    ipos = 1;
    epos = ownList.find(" ", ipos);
    do {
        if(ipos != epos) ownNums.push_back(std::stoi(ownList.substr(ipos, epos-ipos)));
        ipos = epos+1;
        epos = ownList.find(" ", ipos);
    } while(epos != std::string::npos);

    for(unsigned int i=0; i<ownNums.size(); i++) {
        for(unsigned int j=0; j<winnerNums.size(); j++) {
            if(ownNums[i] == winnerNums[j]) {
                matchNums->push_back(ownNums[i]);
            }
        }
    }
}