//
// Created by mrgat on 11/3/2021.
//

#ifndef PROJECT_4_BUBBLESORT_H
#define PROJECT_4_BUBBLESORT_H
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
#endif //PROJECT_4_BUBBLESORT_H
