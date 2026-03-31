#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include "CustomHashTable.hpp"

void runBenchmarks() {
    const int numOps = 1000000;
    const int tableSize = 2000000; // Large size to minimize collisions

    
    std::unordered_map<int, int> stdMap;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOps; ++i) {
        stdMap[i] = i;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto stdDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    //Our CustomHashTable
    CustomHashTable<int, int, 2000000> customTable;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOps; ++i) {
        customTable.insert(i, i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto customDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "--- Performance Results (1 Million Inserts) ---\n";
    std::cout << "std::unordered_map: " << stdDuration << " ms\n";
    std::cout << "Custom Linear Probing Table: " << customDuration << " ms\n";
    
    double speedup = (double)stdDuration / customDuration;
    std::cout << "Our table is " << speedup << "x faster than the standard library!\n";
}

int main() {
    runBenchmarks();
    return 0;
}
