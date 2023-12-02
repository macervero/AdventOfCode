#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
    std::string filename = "input1_day01.txt", line;
    std::ifstream ifile(filename);
    int pos, num, sum = 0;

    if(!ifile.is_open()) std::cerr << filename << " can not be opened\n";
    else {
        while(!ifile.eof()) {
            ifile >> line;

            pos = 0;
            while(line[pos]<'0' || line[pos]>'9') pos++;
            num = std::stoi(std::string(1, line[pos])) * 10;

            pos = line.size()-1;
            while(line[pos]<'0' || line[pos]>'9') pos--;
            num += std::stoi(std::string(1, line[pos]));

            sum += num;
        }

        std::cout << sum << "\n";
    }

    ifile.close();
    return 0;
}