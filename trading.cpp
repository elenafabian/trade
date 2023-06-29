#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <numeric>
#include <unordered_map>
#include <iostream>
#include <csignal>
#include <array>
using namespace std;

static int TEN_MILLION = 10000000;
static int FORTY_MILLION = TEN_MILLION * 4;
std::unordered_map<uint64_t, uint64_t> hashKey2Count;
uint64_t currentSum;
uint64_t currentCount;
uint64_t start[4];
uint64_t bestCount = 0;

// generate hashkeys
inline uint64_t h(uint64_t quad[]) {
    uint64_t key = quad[0];
    key = key * 10000001 + static_cast<uint64_t>(quad[1]);
    key = key * 10000001 + static_cast<uint64_t>(quad[2]);
    key = key * 10000001 + static_cast<uint64_t>(quad[3]);
    
    /* uint64_t key = 0;
    key ^= std::hash<uint64_t>{}(quad[0]) + 0x9e3779b9 + (key << 6) + (key >> 2);
    key ^= std::hash<uint64_t>{}(quad[1]) + 0x9e3779b9 + (key << 6) + (key >> 2);
    key ^= std::hash<uint64_t>{}(quad[2]) + 0x9e3779b9 + (key << 6) + (key >> 2);
    key ^= std::hash<uint64_t>{}(quad[3]) + 0x9e3779b9 + (key << 6) + (key >> 2); */ 
    return key;
}

inline uint64_t pairGCD(uint64_t x, uint64_t y) {
    // Euclid's Algorithm
    while (y != 0) {
        uint64_t temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

inline uint quadGCD(uint64_t quad[]) {
    // GCD of pairs and GCD of that
    uint gcd1 = pairGCD(quad[0], quad[1]);
    if (gcd1 == 1)
        return 1; 
    uint gcd2 = pairGCD(quad[2], quad[3]);
    if (gcd2 == 1)
        return 1; 
    return pairGCD(gcd1, gcd2);
}

// reduce 4 values (mutate in place)
inline void r(uint64_t quad[]) {
    // subtract the smallest element from each number
    uint64_t min1 = quad[1] > quad[0] ? quad[0] : quad[1];
    uint64_t min2 = quad[3] > quad[2] ? quad[2] : quad[3];
    uint64_t min =  min2 > min1 ? min1 : min2;
    if (min != 0) {
        quad[0] -= min;
        quad[1] -= min;
        quad[2] -= min;
        quad[3] -= min;
    }

    // divide out the remaining GCD
    uint gcd = quadGCD(quad);
    if (gcd > 1) {
            quad[0] /= gcd; 
            quad[1] /= gcd;
            quad[2] /= gcd; 
            quad[3] /= gcd;
    }
}

// calculate next 4 values (mutate in place)
inline void n(uint64_t quad[]) {
    uint64_t tempAAA = quad[0];
    quad[0] = quad[0] > quad[1] ? quad[0]-quad[1] : quad[1]-quad[0];
    quad[1] = quad[1] > quad[2] ? quad[1]-quad[2] : quad[2]-quad[1];
    quad[2] = quad[2] > quad[3] ? quad[2]-quad[3] : quad[3]-quad[2];
    quad[3] = quad[3] > tempAAA ? quad[3]-tempAAA : tempAAA-quad[3];
}

uint64_t c(uint64_t quad[]) {
    // create a jump counter
    uint64_t count = 0;

    r(quad);                                // reduce
    uint64_t key = h(quad);                 // hashkey
    auto pair = hashKey2Count.find(key);    // lookup

    if (pair != hashKey2Count.end()) {      // FOUND!
       count = pair->second;                //  make use of memo
       return count; 
    }
                                            // NOT FOUND
    count++;                                //  add 1 to count
    n(quad);                                //  apply transform
    count += c(quad);                       //  repeat
    hashKey2Count.insert({key, count});     //  add memo
    return count;
}

void handleSignal(int signal) {
    if (signal == SIGINT) {
        printf("\n\n** INTERRUPT\t");
        printf("current run:\t(%llu, %llu, %llu, %llu)\tsum: %llu\n", start[0], start[1], start[2], start[3], currentSum);
    }
}

int main() {
    std::signal(SIGINT, handleSignal);

    // create hash map (global) + insert base case
    uint64_t basecase[] = {0, 0, 0, 0};
    hashKey2Count.insert({h(basecase), 1});

    // iterate through sums x in [0, 40 million]
    // x = a+b+c+d where a=0 and a<b<c<d
    for (currentSum = 0; currentSum < FORTY_MILLION; currentSum++) {
        for (start[3] = 0; start[3] < currentSum; start[3]++) {
            int lim = currentSum - start[3];
            for(start[2] = 0; start[2] < start[3] && start[2] < lim; start[2]++) {

                start[1] = currentSum - start[3] - start[2];
                if (start[1] >= start[2] || ((int) start[1]) < 0)
                    continue; 
                start[0] = 0;

                // create a mutable copy and analyze
                uint64_t quad[] = {start[0], start[1], start[2], start[3]};
                uint64_t count = c(quad);

                if (count > bestCount) {
                    bestCount = count;
                    printf("\n!! UPDATE\n");
                    printf("Smallest No. Stocks:\t%llu\n", currentSum);
                    printf("New Best No. Jumps:\t%llu\n", bestCount);
                    printf("(%llu, %llu, %llu, %llu)\n\n", start[0], start[1], start[2], start[3]);
                }
            }
        }
    }
}

