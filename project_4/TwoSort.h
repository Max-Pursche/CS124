//
// Created by mrgat on 11/3/2021.
//

#ifndef PROJECT_4_TWOSORT_H
#define PROJECT_4_TWOSORT_H
template<typename Comparable>
void twoSort(vector<Comparable> vec) {
    int reads = 0;
    int writes = 0;
    bool haveSwapped = true;
    int maxIndex = vec.size(), i;
    Ramen ramen;
    while (haveSwapped) {
        haveSwapped = false;
        for (i = 0; i + 1 < maxIndex; ++i) {
            // Compare items at indices i and i+1 and swap if necessary
            if (vec[i].getRating() > vec[i+1].getRating()) {
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
}
#endif //PROJECT_4_TWOSORT_H
