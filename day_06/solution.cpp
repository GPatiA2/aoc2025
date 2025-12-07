#include<iostream>
#include<string>
#include<fstream>
#include<vector>

#include"aocutils.h"

long long int solve1(std::vector<std::vector<string>> data){
    long long int res = 0;
    for(int j = 0; j < data[0].size(); j++){
        bool sum = (data[data.size()-1][j] == "+");
        long long int par_res = (sum ? 0 : 1);
        for(int i = 0; i < data.size() - 1; i++){
            if(sum){
                par_res += std::stoll(data[i][j]);
            } else {
                par_res *= std::stoll(data[i][j]);
            }
        }
        res += par_res;
    }
    return res;
}

long long int solve2(std::vector<string> data){
    long long int res = 0;
    std::vector<long long int> nums;
    for(int j = data[0].size() -1; j >= 0; j--){
        long long int partial_num = 0;
        for(int i = 0; i < data.size(); i++){
            if(std::isdigit(data[i][j])){
                std::cout << "Found char " << data[i][j] << " is number " << (data[i][j] - '0') << std::endl;
                partial_num = partial_num * 10 + (data[i][j] - '0');
            }
        }
        if(partial_num != 0){
            nums.push_back(partial_num);
        }
        if(data[data.size()-1][j] == '+'){
            std::cout << "Found sum operation" << std::endl;
            long long int s = 0;
            for(long long int n : nums){
                std::cout << " " << n << " + ";
                s += n;
            }
            std::cout << "= " << s << std::endl;
            res += s;
            nums.clear();
        }
        else if(data[data.size()-1][j] == '*'){
            std::cout << "Found product operation" << std::endl;
            long long int p = 1;
            for(long long int n : nums){
                std::cout << " " << n << " * ";
                p *= n;
            }
            std::cout << "= " << p << std::endl;
            res += p;
            nums.clear();
        }
    }
    return res;
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Please provide the input file path as argument." << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    std::string line;
    std::vector<std::vector<string>> data1;
    std::vector<string> data2;
    while(std::getline(infile, line)){
        std::vector<string> parts = split_in_words(line);
        data1.push_back(parts);
        data2.push_back(line);
    }

    long long int sol1 = solve1(data1);
    long long int sol2 = solve2(data2);

    std::cout << "Solution 1: " << sol1 << std::endl;
    std::cout << "Solution 2: " << sol2 << std::endl;

    return 0;
}