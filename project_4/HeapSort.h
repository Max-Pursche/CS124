//
// Created by mrgat on 11/3/2021.
//

#ifndef PROJECT_4_HEAPSORT_H
#define PROJECT_4_HEAPSORT_H
//// Helper function for heapSort
//inline int leftChild(int i) {
//    return 2 * i + 1;
//}
//// Helper function for heapSort
//// i is the index of the value being percolated down
//// n is the number of items in the heap
//template <typename Comparable>
//void percolateDown(vector<Comparable> &items, int i, int n, int child, Comparable tmp, int &reads, int &writes) {
//    for(tmp = items[i]; leftChild(i) < n; i = child) {
//        child = leftChild(i);
//        reads++;
//        writes++;
//        // choose the child with the larger value
//        if (child != n - 1 && items[child] < items[child + 1]) {
//            ++child;
//        }
//        reads += 2;
//        // if the parent is less than the child, swap them
//        if (tmp < items[child]) {
//            items[i] = items[child];
//            reads +=2;
//            writes++;
//        } else {
//            reads +=2;
//            // parent is >= both children. nothing more to do.
//            break;
//        }
//    }
//    items[i] = tmp;
//    reads++;
//    writes++;
//}
//
//template <typename Comparable>
//vector<Comparable> heapSort(vector<Comparable> items, int reads, int writes) {
//    int i, j, child;
//    Comparable temp, tmp;
//    // build the heap (with max value at root)
//    for (i = items.size() / 2 - 1; i >= 0; --i) {
//        percolateDown(items, i, items.size(), child, tmp, reads, writes);
//    }
//    //printVec(items);
//    // keep deleting the max
//    for (j = items.size() - 1; j > 0; --j) {
//        // swap the maximum out
//        temp = items[0];
//        items[0] = items[j];
//        items[j] = temp;
//        reads += 3;
//        writes += 3;
//
//        // make it into a heap again
//        percolateDown(items, i, items.size(), child, tmp, reads, writes);
//
//        //printVec(items);
//    }
//    return items;
//}
#endif //PROJECT_4_HEAPSORT_H
