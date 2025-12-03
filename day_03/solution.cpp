#include<fstream>
#include<iostream>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<cmath>
#include"aocutils.h"

int solve(const vector<int> &numbers){
    int first_digit_pos = 0;
    int second_digit_pos = 1;
    int i = 2; 
    while(i < numbers.size() - 1){ 
        if(numbers[i] > numbers[first_digit_pos]){
            first_digit_pos = i;
            second_digit_pos = i + 1;
            // std::cout << "Moving first digit from " << numbers[first_digit_pos] << " to " << numbers[second_digit_pos] << std::endl;
            // std::cout << "Because " << numbers[i] << " is greater than " << numbers[first_digit_pos] << std::endl;
        }
        else if(numbers[i] > numbers[second_digit_pos]){
            second_digit_pos = i;
        }
        // std::cout << "i: " << i << " first: " << numbers[first_digit_pos] << " second: " << numbers[second_digit_pos] << std::endl;
        i++;
    }
    if (numbers[i] > numbers[second_digit_pos])
    {
        second_digit_pos = i;
    }
    
    return numbers[first_digit_pos] * 10 + numbers[second_digit_pos];
}

long long int solve2(const vector<int> & numbers){


    // Assign first digit
    // First digit is the maximum number that has twelve other number after it
    int position = 0;
    int digits_left = 12;
    long long int value = 0;
    while(digits_left > 0 && position < numbers.size()){
        // Find next maximum number that has enough digits after it
        std::cout << "Finding digit " << (13 - digits_left) << std::endl;
        bool found = false;
        // Find the maximum between position and the position at numbers.size() - digits_left
        int digit = -1;
        for(int j = position; j <= numbers.size() - digits_left; j++){
            if(numbers[j] > digit){
                digit = numbers[j];
                position = j + 1; 
                found = true;
            }
        }
        value = value * 10 + digit;
        digits_left--;

    }
    return value;
}

int main(int argc, char ** argv){
    if(argc < 2){
        std::cout << "Please provide input file" << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);
    std::string line;
    int sum = 0;
    int solution1 = 0;
    long long int solution2 = 0;
    long long int sum2 = 0;
    vector<int> numbers;
    while(std::getline(infile, line)){
        for(int i = 0; i < line.size(); i++){
            numbers.push_back(std::stoi(substr(line, i, i+1)));
        }
        std::cout << "Numbers: " << numbers << std::endl;
        solution1 = solve(numbers);
        solution2 = solve2(numbers);
        std::cout << "Solution1: " << solution1 << std::endl;
        std::cout << "Solution2: " << solution2 << std::endl;
        sum += solution1;
        sum2 += solution2;
        numbers.clear();
    }
    std::cout << "Sum 1: " << sum << std::endl;
    std::cout << "Sum 2: " << sum2 << std::endl;
    return 0;
}