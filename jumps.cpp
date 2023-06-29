// 50EB44D3F029ED934858FFFCEAC3547C68768FC9
// Main Function
// EECS281 project1

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

const static int NUM_STOCKS = 4; 
const static int MAX_STOCKS = 10000000; 

class Stock_Solver {
private:
    inline array<int, 4> iteration(const array<int, 4>& seq) { 
        // returns true when all values in vector are 0's
        array<int, 4> newSeq;
        newSeq[0] = abs(seq[1] - seq[0]);
        newSeq[1] = abs(seq[2] - seq[1]);
        newSeq[2] = abs(seq[3] - seq[2]);
        newSeq[3] = abs(seq[3] - seq[0]);
        return newSeq; 
    }  

    std::uint64_t hashIntArray(const int (&arr)[4]) {
        constexpr std::uint64_t multiplier1 = 0xc6a4a7935bd1e995ULL;
        constexpr std::uint64_t multiplier2 = 0x9e3779b97f4a7c15ULL;
        constexpr std::uint64_t prime = 0x1e35a7bd14c131eULL;
        std::uint64_t hashValue = 0;

        for (const int& element : arr) {
            std::uint64_t value = static_cast<std::uint64_t>(element);
            value ^= multiplier1;
            value *= multiplier2;
            hashValue ^= value;
            hashValue *= multiplier2;
        }

        hashValue ^= prime;

        return hashValue;
    }
    
    uint64_t get_hash_key(int a, int b, int c, int d) {
        int gcd = quadGCD(a, b, c, d);
        a /= gcd;
        b /= gcd;
        c /= gcd;
        d /= gcd;
        uint64_t h = 0;
        hash_step(h, a);
        hash_step(h, b);
        hash_step(h, c);
        hash_step(h, d);
        return h;
    }
    
    int solve(array<int, 4>& seq) {
        int count = 0; 
        while (seq[0] != 0 || seq[1] != 0 || seq[2] != 0 || seq[3] != 0) {
            seq = iteration(seq);
            count++;    
        }
    
        return count; 
    }

public:

    int find_best_order() { 
        int largestSum = 0;
        array<int, 4> seq;
        
        for (int dig3 = 0; dig3 < MAX_STOCKS; dig3++) {
            seq[3] = dig3; 
            for (int dig2 = 0; dig2 < dig3; dig2++) {
                seq[2] = dig2;
                for (int dig1 = 0; dig1 < dig2; dig1++) {
                    seq[1] = dig1;
                    for (int dig0 = 0; dig0 < dig1; dig0++) {
                        seq[0] = dig0;
                        int val = solve(seq); 
                        largestSum = max(val, largestSum); 
                        cout << val << endl; 
                    }
                }
            }
        }
    
        return largestSum; 
    }
 
}; 


int main(int argc, char* argv[]) {
    cout << solution() << endl; 
    return 0; 
    
}


