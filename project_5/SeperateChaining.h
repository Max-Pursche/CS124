//
// Created by mrgat on 11/21/2021.
//

#ifndef PROJECT_5_SEPERATECHAINING_H
#define PROJECT_5_SEPERATECHAINING_H
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
class SeparateChaining {
private:
    unsigned long tableSize;
    vector<vector<Hashable>> table;
    function<string(Hashable)> getKey;

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

public:
    // Constructor
    SeparateChaining(unsigned long tableSize, function<string(Hashable)> getKey) {
        this->tableSize = nextPrime(tableSize);
        this->getKey = getKey;
        table.resize(this->tableSize);
    }

    void Record(const std::string filename,int read) {
        std::ofstream f_out;
        f_out.open(filename, std::ios_base::app);
        if (f_out) {
            f_out << read << std::endl;
        }
        f_out.close();
    }

    // Insert
    //reades/writes recording which variable? item/ key/or Index
    //
    void insert(Hashable item, int &reads, std::string filename ) {
        reads = 0;
        // get a key from the item
        string key = getKey(item);
        // only insert if the key is not already in the table
        if (find(key, reads)) {
            // the key is already in the table. No duplicates allowed.
            return;
        }
        // hash the key into an index
        unsigned long index = hornerHash(key);
        // store the item at the index
        table[index].push_back(item);
        reads++;
        Record(filename, reads);
    }

    // Find
    optional<Hashable> find(string key, int &reads) {
        // hash the key into an index
        unsigned long index = hornerHash(key);
        // Check if the vector at the index has the item we're looking for
        for (int i = 0; i < table[index].size(); ++i) {
            if (getKey(table[index][i]) == key) {
                // Found the item
                reads += 2;
                return table[index][i];
            }
            else reads++;
        }
        return nullopt;
    }

    // Remove
    bool remove(string key, int &reads) {
        // hash the key into an index
        unsigned long index = hornerHash(key);
        // Check if the vector at the index has the item we're looking for
        for (int i = 0; i < table[index].size(); ++i) {;
            if (getKey(table[index][i]) == key) {
                // Found the item. Remove it.
                table[index].erase(table[index].begin() + i);
                reads += 2;
                return table[index][i];
            }
            reads++;
        }
        return false;
    }
};
#endif //PROJECT_5_SEPERATECHAINING_H
