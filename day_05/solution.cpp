#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>

#include"aocutils.h"

struct Range{
    long long int start;
    long long int end;

    Range(long long int s, long long int e): start(s), end(e) {}

    bool contains(long long int val){
        return val >= start && val <= end;
    }

    bool fully_contains(Range other){
        return this->contains(other.start) && this->contains(other.end);
    }


};

long long int solve1(std::vector<Range> ranges, std::vector<long long int> ids){
    long long int count = 0;
    for(long long int id : ids){
        for(Range range : ranges){
            if(range.fully_contains(Range(id, id))){
                count++;
                break;
            }
        }
    }
    return count;
}

long long int solve2(std::vector<Range> ranges){
    // Merge overlapping ranges
    if(ranges.size() == 0) return 0;
    std::sort(ranges.begin(), ranges.end(), [](Range a, Range b){ return a.start < b.start; });
    std::vector<Range> merged;
    merged.push_back(ranges[0]);
    for(size_t i = 1; i < ranges.size(); i++){
        Range last = merged.back();
        if(ranges[i].start <= last.end){
            last.end = std::max(last.end, ranges[i].end);
            merged.back() = last;
        } else {
            merged.push_back(ranges[i]);
        }
    }
    // Calculate the length of each range and sum
    long long int total_length = 0;
    for(Range range : merged){
        total_length += (range.end - range.start + 1);
    }
    return total_length;
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Please provide the input file path as argument." << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);
    std::string line;
    std::vector<Range> ranges;

    std::getline(infile, line);
    while(line != ""){
        auto range1_parts = split_line(line, "-");
        ranges.push_back(Range(std::stoll(range1_parts[0]), std::stoll(range1_parts[1])));
        std::getline(infile, line);
    }
    std::vector<long long int> ids; 
    while(std::getline(infile, line)){
        long long int id = std::stoll(line);
        ids.push_back(id);
    }

    long long int sol1 = solve1(ranges, ids);
    long long int sol2 = solve2(ranges);

    std::cout << "Solution 1: " << sol1 << std::endl;
    std::cout << "Solution 2: " << sol2 << std::endl;
    return 0;
}