//
// Created by mrgat on 11/21/2021.
//
#ifndef PROJECT_5_LINEARPROBING_H
#define PROJECT_5_LINEARPROBING_H
#include <functional>
#include <string>
#include <vector>
using namespace std;
using std::function;
using std::string;
using std::vector;

#include <experimental/optional>
using std::experimental::optional;
using std::experimental::nullopt;
using std::experimental::make_optional;

template<typename Hashable>
class LinearProbing {
private:
    enum state {EMPTY, FILLED, REMOVED};
    struct hashItem {
        state status;
        Hashable item;
    };
    unsigned long tableSize;
    vector<hashItem> table;
    function<string(Hashable)> getKey;
    unsigned long numItems;

    // Hash function
    unsigned long hornerHash(string key) {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % tableSize;
    }

    // Find the next prime number
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n-2);
    }

    void rehash() {
        vector<hashItem> oldTable = table;
        tableSize = nextPrime(tableSize * 2);
        table.clear();
        table.resize(tableSize);
        numItems = 0;
        for (int i = 0; i < oldTable.size(); ++i) {
            if (oldTable[i].status == FILLED) {
                insert(oldTable[i].item);
            }
        }
    }

public:
    // Constructor
    LinearProbing(unsigned long tableSize, function<string(Hashable)> getKey) {
        this->tableSize = nextPrime(tableSize);
        this->getKey = getKey;
        table.resize(this->tableSize);
        numItems = 0;
    }

    // Insert
    void insert(Hashable item) {
        // get a key from the item
        string key = getKey(item);
        // only insert if the key is not already in the table
        if (find(key)) {
            // the key is already in the table. No duplicates allowed.
            return;
        }
        // hash the key into an index
        unsigned long index = hornerHash(key);
        // find an index where we can insert
        while (table[index].status == FILLED) {
            // gotta probe
            index = (index + 1) % tableSize;
        }
        ++numItems;
        table[index].item = item;
        table[index].status = FILLED;
        if (numItems > tableSize / 2) {
            rehash();
        }
    }

    // Find
    optional<Hashable> find(string key) {
        // hash the key into an index
        unsigned long index = hornerHash(key);
        while (table[index].status != EMPTY) {
            // Check if the value at the index has a key that matches the parameter
            if (table[index].status == FILLED && getKey(table[index].item) == key) {
                // Found the item
                return table[index].item;
            }
            // gotta probe
            index = (index + 1) % tableSize;
        }
        // Did not find the item
        return nullopt;
    }

    // Remove
    bool remove(string key) {
        // hash the key into an index
        unsigned long index = hornerHash(key);
        while (table[index].status != EMPTY) {
            // Check if the value at the index has a key that matches the parameter
            if (table[index].status == FILLED && getKey(table[index].item) == key) {
                // Found the item. Remove it.
                table[index].status = REMOVED;
                table[index].item = Hashable();
                return true;
            }
            // gotta probe
            index = (index + 1) % tableSize;
        }
        // Did not find the item
        return false;
    }
};
#endif //PROJECT_5_LINEARPROBING_H
