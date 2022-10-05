#include <iostream>
#include <vector>
#include "Ramen.h"
#include "SelectionSort.h"
#include "HeapSort.h"
#include "BubbleSort.h"
#include "QuickSort.h"
using namespace std;
void Record(const std::string& filename,int read, int write) {
    std::ofstream f_out;
    f_out.open(filename, std::ios_base::app);
    if (f_out) {
        f_out << read << " " << write << std::endl;
    }
    f_out.close();
}

template<typename Comparable>
void quickSortStableRec(vector<Comparable> &vec, int &reads, int &writes) {
    // Recursive base case
    if (vec.size() <= 1) {
        return;
    }

    // Choose a partition element
    Comparable partition = vec[0];
    writes++;

    vector<Comparable> smaller, equal, larger;
    // Loop through vec and populate smaller, equal, larger
    int i;
    for (i = 0; i < vec.size(); ++i) {
        if (vec[i] < partition) {
            smaller.push_back(vec[i]);
            reads += 2;
        } else if (vec[i] == partition) {
            equal.push_back(vec[i]);
            reads += 2;
        } else {
            larger.push_back(vec[i]);
            reads += 2;
        }
    }
    // Recursive calls
    quickSortStableRec(smaller, reads, writes);
    quickSortStableRec(larger, reads, writes);
    // Copy everything back into vec
    for (i = 0; i < vec.size(); ++i) {
        if (i < smaller.size()) {
            vec[i] = smaller[i];
            reads += 2;
            writes++;
        } else if (i < smaller.size() + equal.size()) {
            vec[i] = equal[i - smaller.size()];
            reads++;
            writes++;
        } else {
            vec[i] = larger[i - smaller.size() - equal.size()];
            reads++;
            writes++;
        }
    }
}

template<typename Comparable>
void quickSortStable(vector<Comparable> vec, int &reads, int &writes) {
    quickSortStableRec(vec, reads, writes);
}

template<typename Comparable>
void selectionSort(vector<Comparable> vec, int &reads, int &writes) {
    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            if (vec[i] < vec[minIndex]) {
                minIndex = i;
                reads += 2;
            }
        }
        // Swap min value into swapIndex spot in vector
        temp = vec[swapIndex];
        vec[swapIndex] = vec[minIndex];
        vec[minIndex] = temp;
        //printVec(vec);
        reads += 3;
        writes +=3;
    }
}

template<typename Comparable>
void bubbleSort(vector<Comparable> vec, int &reads, int &writes) {
    bool haveSwapped = true;
    int maxIndex = vec.size(), i;
    Comparable temp;
    while (haveSwapped) {
        haveSwapped = false;
        for (i = 0; i + 1 < maxIndex; ++i) {
            // Compare items at indices i and i+1 and swap if necessary
            if (vec[i] > vec[i+1]) {
                temp = vec[i];
                vec[i] = vec[i+1];
                vec[i+1] = temp;
                // Update haveSwapped
                haveSwapped = true;
                reads += 5;
                writes += 3;
            }
            else {
                reads += 2;
            }
        }
        // Update maxIndex
        --maxIndex;
    }
}

// Helper function for heapSort
inline int leftChild(int i) {
    return 2 * i + 1;
}
// Helper function for heapSort
// i is the index of the value being percolated down
// n is the number of items in the heap
template <typename Comparable>
void percolateDown(vector<Comparable> &items, int i, int n, Comparable tmp, int &reads, int &writes) {
    int child = 0;
    for(tmp = items[i]; leftChild(i) < n; i = child) {
        child = leftChild(i);
        reads++;
        writes++;
        // choose the child with the larger value
        if (child != n - 1 && items[child] < items[child + 1]) {
            ++child;
        }
        reads += 2;
        // if the parent is less than the child, swap them
        if (tmp < items[child]) {
            items[i] = items[child];
            reads +=2;
            writes++;
        } else {
            reads +=2;
            // parent is >= both children. nothing more to do.
            break;
        }
    }
    items[i] = tmp;
    reads++;
    writes++;
}

template <typename Comparable>
vector<Comparable> heapSort(vector<Comparable> items, int &reads, int &writes) {
    int i, j, child;
    Comparable temp, tmp;
    //child = 0;
    // build the heap (with max value at root)
    for (i = items.size() / 2 - 1; i >= 0; --i) {
        percolateDown(items, i, items.size(), tmp, reads, writes);
    }
    //printVec(items);
    // keep deleting the max
    for (j = items.size() - 1; j > 0; --j) {
        // swap the maximum out
        temp = items[0];
        items[0] = items[j];
        items[j] = temp;
        reads += 3;
        writes += 3;

        // make it into a heap again
        percolateDown(items, j, items.size(), tmp, reads, writes);

        //printVec(items);
    }
    return items;
}


void twoSort(vector<Ramen> vec, int &reads, int &writes) {
    bool haveSwapped = true;
    int maxIndex = vec.size(), i;
    Ramen ramen;
    while (haveSwapped) {
        haveSwapped = false;
        for (i = 0; i + 1 < maxIndex; ++i) {
            // Compare items at indices i and i+1 and swap if necessary
            if (vec[i].getNumber() > vec[i+1].getNumber()) {
                ramen = vec[i];
                vec[i] = vec[i+1];
                vec[i+1] = ramen;
                // Update haveSwapped
                haveSwapped = true;
                reads += 5;
                writes += 3;
            }
            else {
                //recording the reads from if statement
                reads += 2;
            }
        }
        // Update maxIndex
        --maxIndex;
    }
    //Record("../readwrite.txt", reads, writes);
}

int main() {
    int reads = 0;
    int writes = 0;
    std::string filename = "../ramen-ratings.csv";
    std::string filename2 = "../readwriteSS.txt";
    std::string filename3 = "../readwriteHS.txt";
    std::string filename4 = "../readwriteBS.txt";
    std::string filename5 = "../readwriteQS.txt";
    std::string filename6 = "../readwriteTS.txt";
    std::vector<Ramen> ramenList;
    std::vector<Ramen> randRamenList;

    //load vector with ramen data
    getRamenData(filename, ramenList);

    //Selection Sorting
    selectionSort(ramenList, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;

    //Heap Sorting
    heapSort(ramenList, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;

    //Bubble Sorting
    bubbleSort(ramenList, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;

    //Quick Sorting
    quickSortStable(ramenList, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    int trains=0;

    //Sorting via another datatype
    twoSort(ramenList, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;

    std::vector<Ramen> vec100;
    std::vector<Ramen> vec200;
    std::vector<Ramen> vec300;
    std::vector<Ramen> vec400;
    std::vector<Ramen> vec500;
    std::vector<Ramen> vec600;
    std::vector<Ramen> vec700;
    std::vector<Ramen> vec800;
    std::vector<Ramen> vec900;
    std::vector<Ramen> vec1000;
    int i = 0;
    //Loop: While i is <= 1000 + push
    do {
        if(i >= 100) {
            vec100.push_back(ramenList[i]);
        }
        if(i >= 200){
            vec200.push_back(ramenList[i]);
        }
        if(i >= 300){
            vec300.push_back(ramenList[i]);
        }
        if(i >= 400){
            vec400.push_back(ramenList[i]);
        }
        if(i >= 500){
            vec500.push_back(ramenList[i]);
        }
        if(i >= 600){
            vec600.push_back(ramenList[i]);
        }
        if(i >= 700){
            vec700.push_back(ramenList[i]);
        }
        if(i >= 800){
            vec800.push_back(ramenList[i]);
        }
        if(i >= 900){
            vec900.push_back(ramenList[i]);
        }
        if(i >= 1000){
            vec1000.push_back(ramenList[i]);
        }
        i++;
    }while(i <= 1000);

    //Selection sort through 1000 vecs
    selectionSort(vec100, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec200, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec300, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec400, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec500, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec600, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec700, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec800, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec900, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec1000, reads, writes);
    Record(filename2, reads, writes);
    reads = 0;
    writes = 0;

    //Heap Sort through 1000 vecs
    heapSort(vec100, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;
    heapSort(vec200, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;
    heapSort(vec300, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;
    heapSort(vec400, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;
    heapSort(vec500, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;
    heapSort(vec600, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;
    heapSort(vec700, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;
    heapSort(vec800, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;
    heapSort(vec900, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;
    heapSort(vec1000, reads, writes);
    Record(filename3, reads, writes);
    reads = 0;
    writes = 0;

    //Bubble Sort through 1000 vecs
    bubbleSort(vec100, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;
    bubbleSort(vec200, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;
    bubbleSort(vec300, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;
    bubbleSort(vec400, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;
    bubbleSort(vec500, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;
    bubbleSort(vec600, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;
    bubbleSort(vec700, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;
    bubbleSort(vec800, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;
    bubbleSort(vec900, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;
    bubbleSort(vec1000, reads, writes);
    Record(filename4, reads, writes);
    reads = 0;
    writes = 0;

    //Quick Sort through 1000 vecs
    quickSortStable(vec100, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    quickSortStable(vec200, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    quickSortStable(vec300, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    quickSortStable(vec400, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    quickSortStable(vec500, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    quickSortStable(vec600, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    quickSortStable(vec700, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    quickSortStable(vec800, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    quickSortStable(vec900, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;
    quickSortStable(vec1000, reads, writes);
    Record(filename5, reads, writes);
    reads = 0;
    writes = 0;

    //Two Sort through 1000 vecs
    selectionSort(vec100, reads, writes);
    twoSort(vec100, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec200, reads, writes);
    twoSort(vec200, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec300, reads, writes);
    twoSort(vec300, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec400, reads, writes);
    twoSort(vec400, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec500, reads, writes);
    twoSort(vec500, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec600, reads, writes);
    twoSort(vec600, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec700, reads, writes);
    twoSort(vec700, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec800, reads, writes);
    twoSort(vec800, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;
    selectionSort(vec1000, reads, writes);
    twoSort(vec1000, reads, writes);
    Record(filename6, reads, writes);
    reads = 0;
    writes = 0;
}