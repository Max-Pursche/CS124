//
// Created by mrgat on 11/3/2021.
//
#ifndef PROJECT_4_QUICKSORT_H
#define PROJECT_4_QUICKSORT_H
//template<typename Comparable>
//void quickSortStableRec(vector<Comparable> &vec) {
//    int reads = 0;
//    int writes = 0;
//    // Recursive base case
//    if (vec.size() <= 1) {
//        return;
//    }
//    // Choose a partition element
//    Comparable partition = vec[0];
//    writes++;
//
//    vector<Comparable> smaller, equal, larger;
//    // Loop through vec and populate smaller, equal, larger
//    int i;
//    for (i = 0; i < vec.size(); ++i) {
//        if (vec[i] < partition) {
//            smaller.push_back(vec[i]);
//            reads += 2;
//        } else if (vec[i] == partition) {
//            equal.push_back(vec[i]);
//            reads += 2;
//        } else {
//            larger.push_back(vec[i]);
//            reads += 2;
//        }
//    }
//    // Recursive calls
//    quickSortStableRec(smaller);
//    quickSortStableRec(larger);
//    // Copy everything back into vec
//    for (i = 0; i < vec.size(); ++i) {
//        if (i < smaller.size()) {
//            vec[i] = smaller[i];
//            reads += 2;
//            writes++;
//        } else if (i < smaller.size() + equal.size()) {
//            vec[i] = equal[i - smaller.size()];
//            reads++;
//            writes++;
//        } else {
//            vec[i] = larger[i - smaller.size() - equal.size()];
//            reads++;
//            writes++;
//        }
//    }
//}
//
//template<typename Comparable>
//void quickSortStable(vector<Comparable> vec) {
//    quickSortStableRec(vec);
//}
#endif //PROJECT_4_QUICKSORT_H
