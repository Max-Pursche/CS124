#include <iostream>
#include <string>
#include "Ramen.h"
#include "LinearProbing.h"
#include "LinearProbingEdit.h"
#include "SeperateChaining.h"
using namespace std;

#include <experimental/optional>
using std::experimental::optional;
using std::experimental::nullopt;
using std::experimental::make_optional;

// Here is an example of a getKey function for a Ramen
string getRamenCountry(Ramen ram) {
    return ram.getCountry() + to_string(ram.getNumber());
}

string intToString(int value) {
    return to_string(value);
}

int main() {
    int reads = 0;
    std::string filename = "../ramen-ratings.csv";
    std::string filename1 = "sepchainingraw.txt";
    std::string filename2 = "sepchaining3000.txt";
    std::string filename3 = "sepchaining3500.txt";
    std::string filename4 = "sepchaining4000.txt";
    std::string filename5 = "sepchaining4500.txt";
    std::string filename6 = "sepchaining5000.txt";
    std::string filename7 = "linprobingraw.txt";
    std::string filename8 = "linprobing3000.txt";
    std::string filename9 = "linprobing3500.txt";
    std::string filename10 = "linprobing4000.txt";
    std::string filename11 = "linprobing4500.txt";
    std::string filename12 = "linprobing5000.txt";
    std::vector<Ramen> ramenList;
    int size1 = 3000;
    int size2 = 3500;
    int size3 = 4000;
    int size4 = 4500;
    int size5 = 5000;
//    std::ofstream f_out;
//    f_out.open("../readsSeperateChainingInsert", std::ofstream::out | std::ofstream::out);
//    f_out.close();
//    f_out.open("readsLinearProbingInsert", std::ofstream::out | std::ofstream::out);
//    f_out.close();

    //load vector with ramen data
    getRamenData(filename, ramenList);

////    Sep chaining with ramen
    SeparateChaining<Ramen> hashSeparateChaining(ramenList.size(), getRamenCountry);
    for (Ramen ram: ramenList) {
        hashSeparateChaining.insert(ram, reads, filename1);
    }

////    Sep chaining with ramen size 1
    SeparateChaining<Ramen> hashSeparateChaining3000(size1, getRamenCountry);
    for (Ramen ram: ramenList) {
        hashSeparateChaining3000.insert(ram, reads, filename2);
    }

////    Sep chaining with ramen size 2
    SeparateChaining<Ramen> hashSeparateChaining3500(size2, getRamenCountry);
    for (Ramen ram: ramenList) {
        hashSeparateChaining3500.insert(ram, reads, filename3);
    }

////    Sep chaining with ramen size 3
    SeparateChaining<Ramen> hashSeparateChaining4000(size3, getRamenCountry);
    for (Ramen ram: ramenList) {
        hashSeparateChaining4000.insert(ram, reads,filename4);
    }

////    Sep chaining with ramen size 4
    reads = 0;
    SeparateChaining<Ramen> hashSeparateChaining4500(size4, getRamenCountry);
    for (Ramen ram: ramenList) {
        hashSeparateChaining4500.insert(ram, reads, filename5);
    }

////    Sep chaining with ramen size 5
    reads = 0;
    SeparateChaining<Ramen> hashSeparateChaining5000(size5, getRamenCountry);
    for (Ramen ram: ramenList) {
        hashSeparateChaining5000.insert(ram, reads, filename6);
    }


////    Linear Probing w/ double hashing with ramen
    reads = 0;
    LinearProbingEdit<Ramen> dblHashLinearProbing(ramenList.size(), getRamenCountry);
    for (Ramen ram: ramenList) {
        dblHashLinearProbing.insert(ram, reads, filename7);
    }

////    Linear Probing w/ double hashing with ramen size 1
    reads = 0;
    LinearProbingEdit<Ramen> dblHashLinearProbing3000(size1, getRamenCountry);
    for (Ramen ram: ramenList) {
        dblHashLinearProbing3000.insert(ram, reads, filename8);
    }

////    Linear Probing w/ double hashing with ramen size 2
    reads = 0;
    LinearProbingEdit<Ramen> dblHashLinearProbing3500(size2, getRamenCountry);
    for (Ramen ram: ramenList) {
        dblHashLinearProbing3500.insert(ram, reads, filename9);
    }

////    Linear Probing w/ double hashing with ramen size 3
    reads = 0;
    LinearProbingEdit<Ramen> dblHashLinearProbing4000(size3, getRamenCountry);
    for (Ramen ram: ramenList) {
        dblHashLinearProbing4000.insert(ram, reads, filename10);
    }

////    Linear Probing w/ double hashing with ramen size 4
    reads = 0;
    LinearProbingEdit<Ramen> dblHashLinearProbing4500(size4, getRamenCountry);
    for (Ramen ram: ramenList) {
        dblHashLinearProbing4500.insert(ram, reads, filename11);
    }

////    Linear Probing w/ double hashing with ramen size 5
    reads = 0;
    LinearProbingEdit<Ramen> dblHashLinearProbing5000(size5, getRamenCountry);
    for (Ramen ram: ramenList) {
        dblHashLinearProbing5000.insert(ram, reads, filename12);
    }

}

