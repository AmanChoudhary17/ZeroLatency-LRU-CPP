#ifndef CUSTOM_HASH_TABLE_HPP
#define CUSTOM_HASH_TABLE_HPP

#include <vector>
#include <optional>
#include <functional>

template <typename K, typename V>
struct HashEntry {
    K key;
    V value;
    bool isOccupied = false;
    bool isDeleted = false; // "Tombstone" for linear probing deletions
};

template <typename K, typename V, int TABLE_SIZE = 2048>
class CustomHashTable {
private:
    std::vector<HashEntry<K, V>> table;

    int hashFunction(const K& key) const {
        return std::hash<K>{}(key) % TABLE_SIZE;
    }

public:
    CustomHashTable() : table(TABLE_SIZE) {}

    void insert(K key, V value) {
        int index = hashFunction(key);
        while (table[index].isOccupied && table[index].key != key) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
    }

    bool find(const K& key, V& outValue) {
        int index = hashFunction(key);
        int start = index;
        while (table[index].isOccupied || table[index].isDeleted) {
            if (table[index].isOccupied && table[index].key == key) {
                outValue = table[index].value;
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == start) break;
        }
        return false;
    }

    void remove(const K& key) {
        int index = hashFunction(key);
        int start = index;
        while (table[index].isOccupied || table[index].isDeleted) {
            if (table[index].isOccupied && table[index].key == key) {
                table[index].isOccupied = false;
                table[index].isDeleted = true; // Mark as tombstone
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == start) break;
        }
    }
};

#endif