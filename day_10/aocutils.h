
#ifndef AOCUTILS_H
#define AOCUTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

inline vector<string> split_line(string s, string sep) {
  vector<string> ret;
  int pos = 0;
  string tok;
  while ((pos = s.find(sep)) != string::npos) {
    tok = s.substr(0, pos);
    ret.push_back(tok);
    s.erase(0, pos + sep.length());
  }
  ret.push_back(s);
  return ret;
}

std::vector<std::string> split_in_words(const std::string& str) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

template <class T> inline vector<T> subvect(vector<T> v, int start, int end) {
  vector<T> ret;
  for (int i = start; i < end; i++) {
    ret.push_back(v[i]);
  }
  return ret;
}

inline string substr(string s, int start, int end) {
  string ret = "";
  for (int i = start; i < end; i++) {
    ret += s[i];
  }
  return ret;
}

template <class T> inline ostream &operator<<(ostream &os, vector<T> vec) {
  for (T it : vec) {
    os << it << " ";
  }
  return os;
}

template <class T>
vector<T> filter_vector(const vector<T> &v, bool (*filter)(T)) {
  vector<T> ret;
  for (T elem : v) {
    if (filter(elem)) {
      ret.push_back(elem);
    }
  }
  return ret;
}

template <class T>
vector<T> filter_vector(const vector<T> &v, bool (*filter)(T, T), const T &ef) {
  vector<T> v_ret;
  for (T elem : v) {
    if (filter(elem, ef)) {
      v_ret.push_back(elem);
    }
  }
  return v_ret;
}

inline long int variations(int elems, int groups) {
  long int prod = 1;
  for (int i = elems; i >= groups; i--) {
    prod *= i;
  }

  return prod;
}

inline long int count_in_substr(const string &str, long int start, long int end,
                                char c) {
  long int count = 0;
  for (int i = start; i < end; i++) {
    if (str[i] == c) {
      count += 1;
    }
  }
  return count;
}

int figures(long int n){
  int count = 0;
  while(n > 0){
    n /= 10;
    count++;
  }
  return count;
}

bool in_bounds(int x, int y, int max_x, int max_y){
    return x >= 0 && x < max_x && y >= 0 && y < max_y;
}

template <class T>
int index_of(const T & elem, const std::vector<T> &vec){
  auto it = std::find(vec.begin(), vec.end(), elem);
  if(it != vec.end()){
    return std::distance(vec.begin(), it);
  } else {
    return -1;
  }
}

struct Coordinate3D {
    int x;
    int y;
    int z;

    Coordinate3D(std::string line){
        std::vector<std::string> parts = split_line(line,",");
        x = std::stoi(parts[0]);
        y = std::stoi(parts[1]);
        z = std::stoi(parts[2]);
    }

    bool operator==(const Coordinate3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator<(const Coordinate3D& other) const {
        if(x != other.x) return x < other.x;
        if(y != other.y) return y < other.y;
        return z < other.z;
    }

    friend std::ostream& operator<<(std::ostream& os, const Coordinate3D& c) {
        os << "(" << c.x << ", " << c.y << ", " << c.z << ")";
        return os;
    }
};

struct Coordinate2D{
    long long int x;
    long long int y;

    Coordinate2D(std::string line){
        std::vector<std::string> parts = split_line(line,",");
        x = std::stoi(parts[0]);
        y = std::stoi(parts[1]);
    }

    bool operator==(const Coordinate2D& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Coordinate2D& other) const {
        if(x != other.x) return x < other.x;
        return y < other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Coordinate2D& c) {
        os << "(" << c.x << ", " << c.y << ")";
        return os;
    }
};

#endif
