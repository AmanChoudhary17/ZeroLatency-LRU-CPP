#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <list>
#include <shared_mutex>
#include <string>
#include "CustomHashTable.hpp"

template <typename K, typename V>
class LRUCache {
private:
    int capacity;
    std::list<std::pair<K, V>> cache_list;
    
    // Using our custom high-performance table instead of std::unordered_map
    using ListIterator = typename std::list<std::pair<K, V>>::iterator;
    CustomHashTable<K, ListIterator> cache_map;
    
    std::shared_mutex mtx;

public:
    LRUCache(int cap) : capacity(cap) {}

    V get(K key) {
        std::unique_lock<std::shared_mutex> lock(mtx); // Unique because splice modifies list
        ListIterator it;
        if (cache_map.find(key, it)) {
            cache_list.splice(cache_list.begin(), cache_list, it);
            return it->second;
        }
        return "NOT_FOUND"; // Simplified for this example
    }

    void put(K key, V value) {
        std::unique_lock<std::shared_mutex> lock(mtx);
        
        ListIterator it;
        if (cache_map.find(key, it)) {
            cache_list.splice(cache_list.begin(), cache_list, it);
            it->second = value;
            return;
        }

        if (cache_list.size() == capacity) {
            K last_key = cache_list.back().first;
            cache_map.remove(last_key);
            cache_list.pop_back();
        }

        cache_list.push_front({key, value});
        cache_map.insert(key, cache_list.begin());
    }
};

#endif