#ifndef _HEAP_H
#define _HEAP_H

#include <vector>

// =====================================

// MaxHeap, T must has "key" attributes
template <class T>
class MaxHeap {
public:
    // Build a heap from a vector, use the index in that vector as label
    MaxHeap(std::vector<T>&);
    // Extract and return label of the element with maximum key
    int extract_maximum(void);
    // Increase the key of an element and adjust the heap structure
    void increase_key(const int, const int);
    // Whether the heap is empty
    bool is_empty(void) { return !(_heap_size); };
private:
    // The heap size
    int _heap_size;
    // Pointer to the element vector
    std::vector<T>* _elem_vec_ptr;
    // The main heap structure, heap_index to label
    std::vector<int> _heap;
    // label to heap_index, -1 if not in the heap
    std::vector<int> _elem_idx;
    // Maintain the heap structure(sift down small element)
    void _sift_down(int);
    // Maintain the heap structure(sift up large element)
    void _sift_up(int);
};

// =====================================

// implementation

template <class T>
MaxHeap<T>::MaxHeap(std::vector<T>& elem_vec) {
    _elem_vec_ptr = &elem_vec;
    const int n = elem_vec.size();
    _heap_size = n;
    _heap.resize(n);
    _elem_idx.resize(n);
    int i;
    for (i = 0; i < n; ++i) {
        _heap[i] = i;
        _elem_idx[i] = i;
    }
    for (i = n / 2 - 1; i >= 0; --i) {
        _sift_down(i);
    }
}

template <class T>
int MaxHeap<T>::extract_maximum() {
    if (_heap_size == 0) {
        std::cout << "Heap is empty!" << std::endl;
        return -1;
    }
    int head, tail;
    head = _heap[0];
    tail = _heap[_heap_size - 1];
    _heap[0] = tail;
    _elem_idx[head] = -1;
    _elem_idx[tail] = 0;
    --_heap_size;
    _sift_down(0);
    return head;
}

template <class T>
void MaxHeap<T>::increase_key(const int label, const int key) {
    int idx = _elem_idx[label];
    if (idx == -1) {
        std::cout << "The element is not in heap!" << std::endl;
        return;
    }
    (*(_elem_vec_ptr))[idx].key = key;
    _sift_up(idx);
}

template <class T>
void MaxHeap<T>::_sift_down(int i) {
    int left, right, largest, i_label, l_label;
    left = 2 * i + 1;
    right = left + 1;
    largest = i;
    if (left < _heap_size &&
        (*(_elem_vec_ptr))[_heap[left]].key >
        (*(_elem_vec_ptr))[_heap[i]].key) {
        largest = left;
    }
    if (right < _heap_size &&
        (*(_elem_vec_ptr))[_heap[right]].key >
        (*(_elem_vec_ptr))[_heap[i]].key) {
        largest = right;
    }
    if (largest != i) {
        i_label = _heap[i];
        l_label = _heap[largest];
        _heap[i] = l_label;
        _heap[largest] = i_label;
        _elem_idx[i_label] = largest;
        _elem_idx[l_label] = i;
        _sift_down(largest);
    }
}

template <class T>
void MaxHeap<T>::_sift_up(int i) {
    if (i == 0) {
        return;
    }
    int parent, i_label, p_label;
    parent = (i - 1) / 2;
    if ((*(_elem_vec_ptr))[_heap[i]].key >
        (*(_elem_vec_ptr))[_heap[parent]].key) {
        i_label = _heap[i];
        p_label = _heap[parent];
        _heap[i] = p_label;
        _heap[parent] = i_label;
        _elem_idx[i_label] = parent;
        _elem_idx[p_label] = i;
        _sift_up(parent);
    }
}

// =====================================

#endif
