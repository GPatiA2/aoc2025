#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

#include"aocutils.h"

long long int solve1(std::vector<Coordinate2D>& coords){
    std::sort(coords.begin(), coords.end(), [](const Coordinate2D& a, const Coordinate2D& b){
        if(a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    long long int area = 0;
    for(size_t i = 0; i < coords.size(); i++){
        for(size_t j = i+1; j < coords.size(); j++){
            long long int width = std::abs(coords[i].x - coords[j].x) + 1;
            long long int height = std::abs(coords[i].y - coords[j].y) + 1; 
            width = width == 0 ? 1 : width;
            height = height == 0 ? 1 : height;
            long long int parc_area = width * height;
            if(parc_area > area){
                area = parc_area;
            }
        }
    }

    return area;
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Please provide the input file path as a command line argument." << std::endl;
        return 1;
    }
    std::ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        std::cout << "Failed to open the input file." << std::endl;
        return 1;
    }
    std::string line;
    std::vector<Coordinate2D> lines;
    while(std::getline(inputFile, line)){
        lines.push_back(Coordinate2D(line));
    }
    inputFile.close();

    long long int result1 = solve1(lines);
    std::cout << "Part 1 Result: " << result1 << std::endl;

    return 0;
}