#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>

#include"aocutils.h"

int solve1(std::vector<string> map, std::pair<int,int> start_pos){
    int res = 0;
    std::queue<std::pair<int,int>> to_visit;
    std::vector<std::vector<int>> colors(map.size(), std::vector<int>(map[0].size(), 0));
    to_visit.push(start_pos);
    while(!to_visit.empty()){
        auto pos = to_visit.front();
        to_visit.pop();

        char current = map[pos.first][pos.second];
        if(current == '^'){
            res++;
            if(in_bounds(pos.first + 1, pos.second+1, map.size(), map[0].size()) && colors[pos.first + 1][pos.second + 1] == 0){
                to_visit.push({pos.first + 1, pos.second + 1});
                colors[pos.first + 1][pos.second + 1] = 1;
            }
            if(in_bounds(pos.first + 1, pos.second-1, map.size(), map[0].size()) && colors[pos.first + 1][pos.second - 1] == 0){
                to_visit.push({pos.first + 1, pos.second - 1}); 
                colors[pos.first + 1][pos.second - 1] = 1;
            }   
        }
        else{
            if(in_bounds(pos.first + 1, pos.second, map.size(), map[0].size()) && colors[pos.first + 1][pos.second] == 0){
                to_visit.push({pos.first + 1, pos.second});
                colors[pos.first + 1][pos.second] = 1;
            }
        }
    }

    return res;
}

struct State{
    std::pair<int,int> pos;
    int trees;
};

long long solve2(vector<string>& data){
    int rows = data.size();
    int cols = data[0].size();
    
    vector<vector<long long>> processed_rows;
    
    vector<long long> first_row(cols, 0);
    for(int i = 0; i < cols; i++){
        if(data[0][i] == 'S') first_row[i] = 1;
    }
    processed_rows.push_back(first_row);
    
    for(int r = 1; r < rows; r++){
        vector<long long> current(cols, 0);
        
        for(int i = 0; i < cols; i++){
            if(data[r][i] == '^') current[i] = -1;
        }
        
        for(int i = 1; i < cols - 1; i++){
            long long above = processed_rows[r-1][i];
            
            if(above > 0){
                if(data[r][i] == '^'){
                    current[i - 1] += above;
                    current[i + 1] += above;
                }
                else{
                    current[i] += above;
                }
            }
        }
        
     
        processed_rows.push_back(current);
    }
    
    // Count timelines in last row
    long long timelines = 0;
    for(long long val : processed_rows[rows - 1]){
        if(val > 0) timelines += val;
    }
    
    return timelines;
}


int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Please provide the input file path as argument." << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    std::string line;

    std::vector<string> map;

    while(std::getline(infile, line)){
        map.push_back(line);
    }

    std::pair<int,int> start_pos;
    start_pos.first = 0;
    start_pos.second = std::find(map[0].begin(), map[0].end(), 'S') - map[0].begin();
    int sol1 = solve1(map, start_pos);

    std::cout << "Solution part 1: " << sol1 << std::endl;
    long long sol2 = solve2(map);
    std::cout << "Solution part 2: " << sol2 << std::endl;
    return 0;
}