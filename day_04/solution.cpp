#include<iostream>
#include<string>
#include<fstream>

#include"aocutils.h"

vector<pair<int,int>> directions = {
    {0,1},  // right
    {1,0},  // down
    {0,-1}, // left
    {-1,0},  // up
    {-1,-1}, // up-left
    {-1,1}, // up-right
    {1,-1}, // down-left
    {1,1}   // down-right
};

bool in_bounds(int i, int j, int rows, int cols){
    return i >= 0 && i < rows && j >= 0 && j < cols;
}

std::pair<int, std::vector<std::pair<int,int>>> solve1(std::vector<std::string> lines){
    int count = 0;
    std::vector<std::pair<int,int>> positions;
    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < lines[i].size(); j++){
            int num_rolls = 0;
            if(lines[i][j] != '@'){
                continue;
            }
            for(int k = 0; k < directions.size(); k++){
                int ady_i = i + directions[k].first;
                int ady_j = j + directions[k].second;
                if(in_bounds(ady_i, ady_j, lines.size(), lines[i].size())){
                    if(lines[ady_i][ady_j] == '@'){
                        num_rolls++;
                    }
                }                
            }
            if(num_rolls < 4){
                count++;
                positions.push_back({i,j});
            }
        } 
    }
    return {count, positions};
}

long int solve2(std::vector<std::string> lines){
    int total_count = 0; 
    int parc_count;
    do{
        auto [count, positions] = solve1(lines);
        parc_count = count;
        total_count += count;
        for(auto pos : positions){
            lines[pos.first][pos.second] = '#';;
        }
    } while(parc_count > 0);
    return total_count;
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Please provide an input file." << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);
    std::string line;
    std::vector<std::string> lines;
    while(std::getline(infile, line)){
        lines.push_back(line);
    }
    std::vector<std::pair<int,int>> positions;
    auto p1 = solve1(lines);
    std::cout << "Solution 1: " << p1.first << std::endl;

    long int solution2 = solve2(lines);
    std::cout << "Solution 2: " << solution2 << std::endl;

    return 0;
}