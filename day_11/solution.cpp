#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<queue>
#include<set>

#include"aocutils.h"

struct State{
    int node_idx;
    bool dac;
    bool fft;

    State(int idx) : node_idx(idx) {
        dac = false;
        fft = false;
    }

    State(int idx, bool dac_visited, bool fft_visited){
        node_idx = idx;
        dac = dac_visited;
        fft = fft_visited;
    }
};


long long int solve2(const std::unordered_map<int, string>& node_names, const std::unordered_map<int, std::vector<int>>& adjacency_list, int initial_node, int end_node, int fft_node, int dac_node){
    long long int result = 0;

    std::queue<State> to_visit;
    to_visit.push(State(initial_node));

    while(!to_visit.empty()){
        State current = to_visit.front();

        to_visit.pop();

        if(current.node_idx == end_node && current.dac && current.fft){
            result++;
        }

        bool dac = current.node_idx == dac_node || current.dac;
        bool fft = current.node_idx == fft_node || current.fft;

        if(current.node_idx != end_node){
            for(int neighbor : adjacency_list.at(current.node_idx)){
                to_visit.push(State(neighbor, dac, fft));
            }
        }
    }

    return result;
}

long long int solve1(const std::unordered_map<int, string>& node_names, const std::unordered_map<int, std::vector<int>>& adjacency_list, int initial_node, int end_node){
    long long int result = 0;

    std::queue<int> to_visit;
    to_visit.push(initial_node);

    while(!to_visit.empty()){
        int current = to_visit.front();

        to_visit.pop();

        if(current == end_node){
            result++;
        }
        else{
            for(int neighbor : adjacency_list.at(current)){
                to_visit.push(neighbor);
            }
        }
    }

    return result;
}

int main(int argc, char ** argv){
    if(argc < 2){
        std::cout << "Please provide input file" << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);
    std::string line;

    std::unordered_map<int, string> node_names;
    std::unordered_map<int, std::vector<int>> adjacency_list;
    std::unordered_map<string, int> name_to_node;

    int you_node = 0;
    int end_node = 0;
    int node_idx = 0;
    int this_node_idx = 0;
    while(std::getline(infile, line)){
        std::vector<std::string> parts = split_in_words(line);
        std::string origin_name = substr(parts[0], 0, parts[0].length() - 1);
        if(name_to_node.find(origin_name) == name_to_node.end()){
            name_to_node[origin_name] = node_idx;
            node_names[node_idx] = origin_name;
            this_node_idx = node_idx;
            node_idx++;
        } else {
            this_node_idx = name_to_node[origin_name];
        }
        for(int i = 1; i < parts.size(); i++){
            std::string dest_name = parts[i];
            if(name_to_node.find(dest_name) == name_to_node.end()){
                name_to_node[dest_name] = node_idx;
                node_names[node_idx] = dest_name;
                adjacency_list[this_node_idx].push_back(node_idx);
                node_idx++;
            } else {
                adjacency_list[this_node_idx].push_back(name_to_node[dest_name]);
            }
        }
    }

    
    you_node = name_to_node["you"];
    end_node = name_to_node["out"];

    adjacency_list[end_node] = std::vector<int>();

    long long int solution1 = 0;

    // std::cout << "Read graph nodes: " << std::endl;
    // for(const auto& pair : node_names){
    //     std::cout << pair.first << ": " << pair.second << std::endl;
    // }

    // std::cout << "Adjacency list: " << std::endl;
    // for(const auto& pair : adjacency_list){
    //     std::cout << node_names[pair.first] << ": ";
    //     for(int neighbor : pair.second){
    //         std::cout << node_names[neighbor] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    solution1 = solve1(node_names, adjacency_list, you_node, end_node);

    std::cout << "Solution 1: " << solution1 << std::endl;

    int svr_node = name_to_node["svr"];
    int fft_node = name_to_node["fft"];
    int dac_node = name_to_node["dac"];

    long long int solution2 = 0;

    long long int svr_to_fft = solve1(node_names, adjacency_list, svr_node, fft_node);
    long long int svr_to_dac = solve1(node_names, adjacency_list, svr_node, dac_node);
    
    long long int dac_to_fft = solve1(node_names, adjacency_list, dac_node, fft_node);
    long long int fft_to_dac = solve1(node_names, adjacency_list, fft_node, dac_node);
  
    long long int fft_to_out = solve1(node_names, adjacency_list, fft_node, end_node);
    long long int dac_to_out = solve1(node_names, adjacency_list, dac_node, end_node);

    solution2 = svr_to_dac * dac_to_fft * fft_to_out + svr_to_fft * fft_to_dac * dac_to_out; 

    std::cout << "Solution 2: " << solution2  << std::endl;

    return 0;
}