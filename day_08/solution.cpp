#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cmath>
#include<queue>
#include<algorithm>
#include<set>

#include"aocutils.h"

struct Coordinate {
    int x;
    int y;
    int z;

    Coordinate(std::string line){
        std::vector<std::string> parts = split_line(line,",");
        x = std::stoi(parts[0]);
        y = std::stoi(parts[1]);
        z = std::stoi(parts[2]);
    }

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator<(const Coordinate& other) const {
        if(x != other.x) return x < other.x;
        if(y != other.y) return y < other.y;
        return z < other.z;
    }

    friend std::ostream& operator<<(std::ostream& os, const Coordinate& c) {
        os << "(" << c.x << ", " << c.y << ", " << c.z << ")";
        return os;
    }
};

struct Edge {
    int from;
    int to;
    double weight;
    Edge(int f, int t, double w) : from(f), to(t), weight(w) {}

    bool operator<(const Edge& other) const {
        return weight > other.weight; // For min-heap
    }
};



namespace std {
    template <>
    struct hash<Coordinate> {
        size_t operator()(const Coordinate& c) const {
            return hash<int>()(c.x) ^ (hash<int>()(c.y) << 1) ^ (hash<int>()(c.z) << 2);
        }
    };
}

using solve_t = long long int;

std::pair<solve_t,solve_t> solve1(const std::vector<Coordinate> &coords, std::unordered_map<Coordinate, std::priority_queue<Edge>> &edges, int paths_to_join){
    long long int result = 1;
    long long int last_x1 = 0;
    long long int last_x2 = 0;

    std::vector<int> partition_struct;

    for(int i = 0; i < coords.size(); i++){
        partition_struct.push_back(i); 
    }

    std::set<Coordinate> free_nodes(coords.begin(), coords.end());

    std::vector<std::vector<bool>> used_edges(coords.size(), std::vector<bool>(coords.size(), false));
    int i = 0;
    while(!free_nodes.empty()){
        std::cout << "Iter " << i + 1 << "/" << paths_to_join << std::endl;
        // Find the smallest edge that connects two different components
        double min_weight = std::numeric_limits<double>::max();
        Edge min_edge(0,0,min_weight); 

        int queue_selected = -1;

        for(int j = 0; j < coords.size(); j++){
            if(edges.at(coords[j]).empty()){
                continue;
            }
            const auto & edge_queue = edges.at(coords[j]);
            // Check if edge is used
            if(!used_edges[edge_queue.top().from][edge_queue.top().to]){
                // Get min edge
                if(edge_queue.top().weight < min_weight){
                    min_weight = edge_queue.top().weight;
                    min_edge = edge_queue.top();
                    queue_selected = j;
                } 
            }
        }

        // Merge components
        int new_part = std::min(partition_struct[min_edge.from], partition_struct[min_edge.to]);
        int old_part = std::max(partition_struct[min_edge.from], partition_struct[min_edge.to]);
        
        used_edges[min_edge.from][min_edge.to] = true;
        edges[coords[queue_selected]].pop();

        free_nodes.erase(coords[min_edge.from]);
        free_nodes.erase(coords[min_edge.to]);

        // Only merge different partitions 
        if(new_part != old_part){
            for(int k = 0; k < partition_struct.size(); k++){
                if(partition_struct[k] == old_part){
                    partition_struct[k] = new_part;
                }
            }
            last_x1 = coords[min_edge.from].x; 
            last_x2 = coords[min_edge.to].x;
        }

        if(i == paths_to_join){
            // Find 3 biggest partitions
            std::unordered_map<int, int> partition_sizes;
            for(int part : partition_struct){
                partition_sizes[part]++;
            }

            std::vector<int> sizes;
            for(auto &entry : partition_sizes){
                sizes.push_back(entry.second);
            }
            std::sort(sizes.begin(), sizes.end(), std::greater<int>());
            std::cout << "Partition sizes: " << sizes << std::endl;

            for(int i = 0; i < 3 && i < sizes.size(); i++){
                std::cout << "Partition " << i + 1 << " size: " << sizes[i] << std::endl;
                result *= sizes[i];
            }
        }
    }

    return {result, last_x1 * last_x2};
}

int main(int argc, char ** argv){
    if(argc < 2){
        std::cout << "Please provide the input file" << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);
    std::string line;
    std::vector<Coordinate> coords;
    int num_joins = 0;
    // Read num_joins from first line
    std::getline(infile, line);
    num_joins = std::stoi(line);

    std::cout << "Number of joins: " << num_joins << std::endl;

    while(std::getline(infile, line)){
        coords.push_back(Coordinate(line));
    }

    // Process coords to generate graph
    std::unordered_map<Coordinate, std::priority_queue<Edge>> graph;
    for(const Coordinate &c : coords){
        graph[c] = std::priority_queue<Edge>();
    }
    for(int i = 0; i < coords.size(); i++){
        for(int j = i + 1; j < coords.size(); j++){
                double dist = std::sqrt(std::pow(coords[i].x - coords[j].x, 2) +
                                       std::pow(coords[i].y - coords[j].y, 2) +
                                       std::pow(coords[i].z - coords[j].z, 2));
                graph[coords[i]].emplace(i, j, dist);
    
        }
    }

    std::cout << "Graph generated with " << graph.size() << " nodes." << std::endl;

    std::pair<solve_t,solve_t> s;
    s = solve1(coords, graph, num_joins);

    std::cout << "Solution 1: " << s.first << std::endl;
    std::cout << "Solution 2: " << s.second << std::endl;

    return 0;
}