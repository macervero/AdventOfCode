#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int problem01Solver(std::string filename);
int problem02Solver(std::string filename);
bool areColorCubesValid(std::string line, std::regex regex, const int COLOR_CUBES);
int getMinValidColorCubes(std::string line, std::regex regex);

const int RED_CUBES = 12;
const int GREEN_CUBES = 13;
const int BLUE_CUBES = 14;

const std::string DATA_FOLDER = "data/";
const std::string INPUT_FILE = "input_day02.txt";
const std::string TEST_FILE = "test_day02.txt";

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
    std::string line;
    std::ifstream ifile(filename);
    std::regex idRegex("Game (\\d*):");
    std::regex redRegex("(\\d*) red");
    std::regex greenRegex("(\\d*) green");
    std::regex blueRegex("(\\d*) blue");
    std::smatch idMatch;
    int id, sum = 0;

    if(!ifile.is_open()) return -1;
    else {
        while(std::getline(ifile, line)) {
            std::regex_search(line, idMatch, idRegex);
            id = std::stoi(std::string(idMatch[1]));

            if(areColorCubesValid(line, redRegex, RED_CUBES) &&
                areColorCubesValid(line, greenRegex, GREEN_CUBES) &&
                areColorCubesValid(line, blueRegex, BLUE_CUBES)) {
                sum += id;
            }
        }
    }
    return sum;
}

int problem02Solver(std::string filename) {
    std::string line;
    std::ifstream ifile(filename);
    std::regex redRegex("(\\d*) red");
    std::regex greenRegex("(\\d*) green");
    std::regex blueRegex("(\\d*) blue");
    int minRed, minGreen, minBlue, sum = 0;

    if(!ifile.is_open()) return -1;
    else {
        while(std::getline(ifile, line)) {
            minRed = getMinValidColorCubes(line, redRegex);
            minGreen = getMinValidColorCubes(line, greenRegex);
            minBlue = getMinValidColorCubes(line, blueRegex);

            sum += minRed * minGreen * minBlue;
        }
    }
    
    return sum;
}

bool areColorCubesValid(std::string line, std::regex regex, const int COLOR_CUBES) {
    std::smatch colorMatch;
    bool matched, isValid = true;

    matched = std::regex_search(line, colorMatch, regex);
    while(matched) {
        if(std::stoi(std::string(colorMatch[1])) > COLOR_CUBES) {
            isValid = false;
            matched = false;
        } else {
            line = std::string(colorMatch.suffix());
            matched = std::regex_search(line, colorMatch, regex);
        }
    }

    return isValid;
}

int getMinValidColorCubes(std::string line, std::regex regex) {
    std::smatch colorMatch;
    bool matched;
    int ncubes, minCubes = 0;

    matched = std::regex_search(line, colorMatch, regex);
    while(matched) {
        ncubes = std::stoi(std::string(colorMatch[1]));
        if(ncubes > minCubes) {
            minCubes = ncubes; 
        }

        line = std::string(colorMatch.suffix());
        matched = std::regex_search(line, colorMatch, regex);
    }

    return minCubes;
}