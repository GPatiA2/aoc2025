#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>

#include "aocutils.h"

struct Move{
    std::vector<int> effects;

    int operator[](int index) const {
        return effects[index];
    }
};

struct State{
    std::vector<int> registers;

    bool operator==(const State & other) const {
        return registers == other.registers;
    }

    void apply(const Move & move){
        for(int i = 0; i < move.effects.size(); i++){
            registers[move[i]] = 1 - registers[move[i]];
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const State& s) {
        os << "[";
        for(int i = 0; i < s.registers.size(); i++){
            os << (s.registers[i] == 1 ? '#' : '.');
        }
        os << "]";
        return os;
    }
};

struct Case{
    std::vector<Move> available_moves;
    State goal_state;
    Case(const std::vector<Move> & moves, const State & goal): available_moves(moves), goal_state(goal) {}

    friend std::ostream& operator<<(std::ostream& os, const Case& c) {
        os << "["; 
        for(int i = 0; i < c.goal_state.registers.size(); i++){
            os << (c.goal_state.registers[i] == 1 ? '#' : '.');
        }
        os << "] ";

        for(int i = 0; i < c.available_moves.size(); i++){
            os << "(";
            for(int j = 0; j < c.available_moves[i].effects.size(); j++){
                os << c.available_moves[i].effects[j];
                if(j < c.available_moves[i].effects.size() - 1){
                    os << ",";
                }
            }
            os << ")";
        }

        os << std::endl;

        return os;
    }
};

long long int solveCase1(const Case & c){

    State initial_state = State();
    for(int i = 0; i < c.goal_state.registers.size(); i++){
        initial_state.registers.push_back(0);
    }

    std::queue<std::pair<State, long long int>> q;
    q.push(std::make_pair(initial_state, 0));

    while(!q.empty()){
        State current_state = q.front().first;
        long long int current_depth = q.front().second;
        q.pop();

        if(current_state == c.goal_state){
            return current_depth;
        }

        for(auto & move : c.available_moves){
            State new_state = current_state;
            new_state.apply(move);
            q.push(std::make_pair(new_state, current_depth + 1));
        }
    }

    return 0;
}

int main(int argc, char ** argv){
    if(argc < 2){
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if(!infile.is_open()){
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    std::vector<string> cases_string;
    while(!infile.eof()){
        std::string line;
        std::getline(infile, line);
        if(!line.empty()){
            cases_string.push_back(line);
        }
    }

    std::vector<Case> cases;
    for(auto & case_str : cases_string){
        std::vector<string> words = split_in_words(case_str);
        std::string goal_state_str = substr(words[0], 1, words[0].size() - 1);
        std::string joltages = words[words.size() - 1];

        State goal_state;
        for(char c : goal_state_str){
            if (c == '#'){
                goal_state.registers.push_back(1);
            } else {
                goal_state.registers.push_back(0);
            }
        }

        std::vector<Move> available_moves;
        for(int i = 1; i < words.size() - 1; i++){
            std::string move_str = substr(words[i], 1, words[i].size() - 1);
            std::vector<string> effects_str = split_line(move_str, ",");
            Move move;
            for(auto & effect : effects_str){
                move.effects.push_back(std::stoi(effect));
            }
            available_moves.push_back(move);
        }

        cases.push_back(Case(available_moves, goal_state));
    }

    // Case c_test = cases[0];
    // std::cout << "Test case: " << c_test << std::endl;
    // State s_test = State();
    // for(int i = 0; i < c_test.goal_state.registers.size(); i++){
    //     s_test.registers.push_back(0);
    // }
    // s_test.apply(c_test.available_moves[c_test.available_moves.size() - 1]);
    // s_test.apply(c_test.available_moves[c_test.available_moves.size() - 2]);


    long long int r1 = 0;
    for(auto & c : cases){
        std::cout << "Solving case: " << c << std::endl;
        r1 += solveCase1(c);
    }
    std::cout << "Result for case 1: " << r1 << std::endl;

    return 0;
}