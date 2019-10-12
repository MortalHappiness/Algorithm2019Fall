// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    const int length = data.size();
    int i, key;
    for (int j = 1; j < length; j++) {
        key = data[j];
        i = j - 1;
        while (i >= 0 && data[i] > key) {
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    if (low < high) {
        const int middle = Partition(data, low, high);
        QuickSortSubVector(data, low, middle);
        QuickSortSubVector(data, middle + 1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector
    const int pivot = data[low];
    int i, j;
    i = low - 1;
    j = high + 1;
    while (1) {
        do {
            j--;
        } while (data[j] > pivot);
        do {
            i++;
        } while (data[i] < pivot);
        if (i < j) {
            swap(data[i], data[j]);
        } else {
            return j;
        }
    }
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    if (low < high) {
        const int middle = (low + high) / 2;
        MergeSortSubVector(data, low, middle);
        MergeSortSubVector(data, middle + 1, high);
        Merge(data, low, middle, middle + 1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    int i, l = 0, r = 0;
    const int leftSize = middle1 - low + 1;
    const int rightSize = high - middle2 + 1;

    vector<int> left(leftSize);
    vector<int> right(rightSize);
    for (i = 0; i < leftSize; i++) {
        left[i] = data[low + i];
    }
    for (i = 0; i < rightSize; i++) {
        right[i] = data[middle2 + i];
    }

    i = low;
    while (l < leftSize && r < rightSize) {
        if (left[l] <= right[r]) {
            data[i] = left[l];
            l++;
        } else {
            data[i] = right[r];
            r++;
        }
        i = (i != middle1)?(i + 1):(middle2);
    }
    while (l < leftSize) {
        data[i] = left[l];
        l++;
        i = (i != middle1)?(i + 1):(middle2);
    }
    while (r < rightSize) {
        data[i] = right[r];
        r++;
        i = (i != middle1)?(i + 1):(middle2);
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    const int left = 2 * root + 1;
    const int right = 2 * root + 2;
    int largestIdx;
    if (left < heapSize && data[left] > data[root]) {
        largestIdx = left;
    } else {
        largestIdx = root;
    }
    if (right < heapSize && data[right] > data[largestIdx]) {
        largestIdx = right;
    }
    if (largestIdx != root) {
        swap(data[root], data[largestIdx]);
        MaxHeapify(data, largestIdx);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    int i;
    // Function : Make input data become a max-heap
    for (i = (heapSize - 1)/2; i >= 0; i--) {
        MaxHeapify(data, i);
    }
}
