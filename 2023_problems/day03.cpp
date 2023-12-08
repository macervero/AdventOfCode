#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int problem01Solver(std::string filename);
int problem02Solver(std::string filename);

const std::string DATA_FOLDER = "data/";
const std::string INPUT_FILE = "input_day03.txt";
const std::string TEST_FILE = "test_day03.txt";

int main(int argc, char** argv) {
    std::string filename;
    bool executeBoth = false;
    int sum;

    if(argc == 1 ||
        (argc == 2 && (*argv[1] != 't' && *argv[1] != 'i')) ||
        (argc == 3 && ((*argv[1] != 't' && *argv[1] != 'i') || (*argv[2] != '1' && *argv[2] != '2'))) ||
        argc > 3) {
        std::cout << "This program must be executed as follows:\n"
                        "\t\t./day02.out FILE_TYPE [PROBLEM]\n\n"
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
    std::string line, subline;
    std::ifstream ifile(filename);
    std::vector<std::string> lines;
    std::regex numRegex("(\\d+)");
    std::regex_iterator<std::string::iterator> erit;
    int num, pos, length, sum = 0;
    bool validNum;

    if(!ifile.is_open()) return -1;
    else {
        while(std::getline(ifile, line)) {
            lines.push_back(line);
        }

        for(unsigned int i=0; i<lines.size(); i++) {
            std::regex_iterator<std::string::iterator> rit ( lines[i].begin(), lines[i].end(), numRegex);

            while (rit != erit) {
                num = std::stoi(rit->str(1));
                pos = rit->position(1);
                length = rit->length(1);

                validNum = false;
                //Check line above
                if(i > 0) {
                    if(pos == 0) subline = lines[i-1].substr(pos, length+1);
                    else subline = lines[i-1].substr(pos-1, length+2);


                    for(int k=0; k<subline.size(); k++) {
                        if(subline[k] != '.') validNum = true;
                    }
                }
                //Check same line
                if(!validNum && pos > 0 && lines[i][pos-1] != '.') validNum = true;
                if(!validNum && pos + length < lines[i].length() && lines[i][pos + length] != '.')  validNum = true;
                //Check line below
                if(!validNum && i<lines.size()-1) {
                    if(pos == 0) subline = lines[i+1].substr(pos, length+1);
                    else subline = lines[i+1].substr(pos-1, length+2);
                    
                    for(int k=0; k<subline.size(); k++) {
                        if(subline[k] != '.') validNum = true;
                    }
                }

                if(validNum) sum += num;

                rit++;
            }

        }
    }
    return sum;
}

int problem02Solver(std::string filename) {
    int sum = 0;
    return sum;
}