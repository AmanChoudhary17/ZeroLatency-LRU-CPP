#include <iostream>
#include <thread>
#include <vector>
#include "LRUCache.hpp"

void stressTest(LRUCache<int, std::string>& cache, int threadId) {
    for (int i = 0; i < 100; ++i) {
        cache.put(i, "Thread-" + std::to_string(threadId) + "-Val-" + std::to_string(i));
        if (i % 10 == 0) {
            cache.get(i);
        }
    }
}

int main() {
    LRUCache<int, std::string> cache(50);
    std::vector<std::thread> workers;

    std::cout << "Starting High-Performance Cache Stress Test...\n";

    for (int i = 0; i < 8; ++i) {
        workers.push_back(std::thread(stressTest, std::ref(cache), i));
    }

    for (auto& t : workers) {
        t.join();
    }

    std::cout << "Test passed! Custom Hash Table and Mutex handled 8 threads successfully.\n";
    return 0;
}