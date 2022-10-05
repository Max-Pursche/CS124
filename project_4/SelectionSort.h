//

// Created by mrgat on 11/3/2021.
//

#ifndef PROJECT_4_SELECTIONSORT_H
#define PROJECT_4_SELECTIONSORT_H

//template<typename Comparable>
//void selectionSort(vector<Comparable> vec, int &reads, int &writes) {
//    int swapIndex, i, minIndex;
//    Comparable temp;
//    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
//        // Loop through vector starting at swapIndex and keep track of min
//        minIndex = swapIndex;
//        for (i = swapIndex + 1; i < vec.size(); ++i) {
//            if (vec[i] < vec[minIndex]) {
//                minIndex = i;
//                reads += 2;
//            }
//        }
//        // Swap min value into swapIndex spot in vector
//        temp = vec[swapIndex];
//        vec[swapIndex] = vec[minIndex];
//        vec[minIndex] = temp;
//        //printVec(vec);
//        reads += 3;
//        writes +=3;
//    }
//    //Record(filename, reads, writes);
//}
#endif //PROJECT_4_SELECTIONSORT_H
