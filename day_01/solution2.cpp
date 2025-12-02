#include<iostream>
#include<fstream>
#include<vector>
int main(int argc, char** argv) {
    std::ifstream infile(argv[1]);
    std::vector<int> numbers;
    std::string line; 
    int dial = 50;
    int move;
    int extra;
    int count_zeros = 0;
    int spins = 0; 
    while(infile >> line){
        int sign = (line[0] == 'L')? -1 : 1;
        int value = std::stoi( line.substr(1, line.length()) );
        bool hit = 0; 
        move = sign * value; 
        extra = move % 100;
        if(extra < 0) extra += 100;
        spins = move / 100;
        count_zeros += std::abs(spins);
        // Extra is always positive here
        // Now we have to count if we cross zero with the extra
        dial = (dial + extra);
        if(dial == 0) {
            count_zeros++;
            std::cout << "Dial ended up at 0" << std::endl;
        }
        else if(dial >= 100){
            dial = dial % 100;
            count_zeros++;
            std::cout << "Dial crossed 0" << std::endl;
        }
        std::cout << "Move: " << move << " (extra: " << extra << ", spins: " << spins << ")" << " new pos " << dial << std::endl;

    }
    std::cout << count_zeros << std::endl;
    return 0;


}