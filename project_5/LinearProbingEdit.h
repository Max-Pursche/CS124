//
// Created by mrgat on 11/21/2021.
//

#ifndef PROJECT_5_LINEARPROBINGEDIT_H
#define PROJECT_5_LINEARPROBINGEDIT_H
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
class LinearProbingEdit {
private:
    enum state {EMPTY, FILLED, REMOVED};
    struct hashItem {
        state status;
        Hashable item;
    };
    unsigned long tableSize;
    vector<hashItem> table;
    function<string(Hashable)> getKey;
    int PRIME = 7;
    unsigned long numItems;


////    Hash function
    unsigned long DoubleHash(string key) {
        (hash1(key) * hash2(key)) % tableSize;
    }
    unsigned long hash1(string key) {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % tableSize;
    }
    // function to calculate second hash
    unsigned long hash2(string key) {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return PRIME - (hashVal % PRIME);
    }

////     Find the next prime number
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

    void rehash(int reads, std::string filename) {
        vector<hashItem> oldTable = table;
        tableSize = nextPrime(tableSize * 2);
        table.clear();
        table.resize(tableSize);
        numItems = 0;
        for (int i = 0; i < oldTable.size(); ++i) {
            if (oldTable[i].status == FILLED) {
                insert(oldTable[i].item, reads, filename);
            }
        }
    }

public:
////     Constructor
    LinearProbingEdit(unsigned long tableSize, function<string(Hashable)> getKey) {
        this->tableSize = nextPrime(tableSize);
        this->getKey = getKey;
        table.resize(this->tableSize);
        numItems = 0;
    }

    void Record(const std::string filename,int read) {
        std::ofstream f_out;
        f_out.open(filename, std::ios_base::app);
        if (f_out) {
            f_out << read << std::endl;
        }
        f_out.close();
    }

////     Insert
    void insert(Hashable item, int &reads, std::string filename) {
//      std::string filename = "hhhhhhainingraw";
        reads = 0;
        // get a key from the item
        string key = getKey(item);
        // only insert if the key is not already in the table
        if (find(key, reads)) {
            // the key is already in the table. No duplicates allowed.
            return;
        }
        // hash the key into an index
        unsigned long index = DoubleHash(key);
        // find an index where we can insert
        while (table[index].status == FILLED) {
            // gotta probe
            index = (index + 1) % tableSize;
        }
        ++numItems;
        table[index].item = item;
        table[index].status = FILLED;
        reads++;
        if (numItems > tableSize / 2) {
            rehash(reads, filename);
        }
        Record(filename, reads);
    }

////     Find
    optional<Hashable> find(string key, int &reads) {
        // hash the key into an index
        unsigned long index = DoubleHash(key);
        while (table[index].status != EMPTY) {
            // Check if the value at the index has a key that matches the parameter
            if (table[index].status == FILLED && getKey(table[index].item) == key) {
                // Found the item
                reads += 2;
                return table[index].item;
            }
            // gotta probe
            index = (index + 1) % tableSize;
        }
        // Did not find the item
        return nullopt;
    }

////     Remove
    bool remove(string key, int &reads) {
        // hash the key into an index
        unsigned long index = DoubleHash(key);
        while (table[index].status != EMPTY) {
            // Check if the value at the index has a key that matches the parameter
            if (table[index].status == FILLED && getKey(table[index].item) == key) {
                // Found the item. Remove it.
                table[index].status = REMOVED;
                table[index].item = Hashable();
                reads +=2;
                return true;
            }
            // gotta probe
            index = (index + 1) % tableSize;
        }
        // Did not find the item
        return false;
    }
};
#endif //PROJECT_5_LINEARPROBINGEDIT_H
