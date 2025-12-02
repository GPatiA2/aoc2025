#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include "aocutils.h"

using range = std::pair<long long int,long long int>;

long long int solve(int start, int end, int depth){
    long long int sum = 0;
    int fig_start = figures(start);
    int fig_end = figures(end);
    string depth_str = "";
    for (int i = 0; i < depth; i++){
        depth_str += "  ";
    }
    if (fig_start == fig_end && fig_start % 2 != 0){
        sum = 0;
        std::cout << depth_str << "Solving case " << start << "-" << end << std::endl;
        std::cout << depth_str << "Figures for start and end are odd: " << fig_start << std::endl;
    }
    else if(fig_start != fig_end){

        std::cout << depth_str << "Solving case " << start << "-" << end << std::endl;
        std::cout << depth_str << "Different number of figures: " << fig_start << " and " << fig_end << std::endl; 
        sum += solve(start, std::pow(10, fig_start) - 1, depth + 1);
        sum += solve(std::pow(10, fig_start), end, depth + 1);
    }
    else{
        std::cout << depth_str << "Solving case " << start << "-" << end << std::endl;
        std::cout << depth_str << "Same number of figures: " << fig_start << std::endl;
        long long int half_figs = fig_start / 2;
        long long int first_half = start / std::pow(10, half_figs);
        long long int second_half = end / std::pow(10, half_figs);
        std::cout << depth_str << "First half range: " << first_half << "-" << second_half << std::endl;
        
        for (long long int i = first_half; i <= second_half; i++){
            long long int double_i = i * static_cast<long long int>(std::pow(10, half_figs)) + i;
            if (double_i >= start && double_i <= end){
                sum += double_i;
                std::cout << depth_str << "Adding number: " << double_i << std::endl;
            }
        }
    }

    std::cout << "--- Range " << start << "-" << end << ": " << sum << std::endl;
    return sum;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    std::vector<range> ranges;
    std::string line;
    std::getline(infile, line);
    vector<std::string> parts = split_line(line, ",");
    for (const std::string& part : parts) {
        vector<std::string> bounds = split_line(part, "-");
        if (bounds.size() == 2) {
            long long int start = std::stod(bounds[0]);
            long long int end = std::stod(bounds[1]);
            ranges.push_back(std::make_pair(start, end));
        }
    }

    long long int total_sum = 0;
    for (const range& r : ranges){
        std::cout << "=== SOLVING RANGE " << r.first << "-" << r.second << " ===" << std::endl;
        total_sum += solve(r.first, r.second, 0);
        std::cout << "===== SUM = " << total_sum << std::endl;
    }

    infile.close();

    std::cout << "Total sum: " << total_sum << std::endl;
    return 0;
}