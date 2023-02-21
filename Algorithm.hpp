#pragma once

#include "AlgoVisualizer.hpp"

class Algorithm {
public:
    Algorithm(AlgoVisualizer *pvis);

    void bubble_sort();
    void selection_sort();
    void insertion_sort();
    void merge_sort();
    void quick_sort();
    void heap_sort();
    void counting_sort();
    void radix_sort();

private:
    void merge_sort_internal(int start, int end);

    int  quick_sort_partition(int start, int end);
    void quick_sort_internal(int start, int end);

    void heapify(int start, int end);
    void heap_sort_internal(int start, int end);

    AlgoVisualizer *m_pvis;
};
