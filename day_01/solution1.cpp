#include<iostream>
#include<fstream>
#include<vector>
int main(int argc, char** argv) {
    std::ifstream infile(argv[1]);
    std::vector<int> numbers;
    std::string line; 
    int dial = 50;
    int move;
    int count_zeros = 0;
    while(infile >> line){
        int sign = (line[0] == 'L')? -1 : 1;
        int value = std::stoi( line.substr(1, line.length()) );
        move = sign * value; 
        move = move % 100;
        std::cout << "Move: " << move << std::endl;
        if (move + dial < 0){
            dial = 100 + (move + dial);
        }
        else{
            dial += move;
            dial = dial % 100;
        }
        if (dial == 0) count_zeros++;
        std::cout << "Dial now at " << dial << std::endl;
    }
    std::cout << count_zeros << std::endl;
    return 0;


}