#include "Algorithm.hpp"

Algorithm::Algorithm(AlgoVisualizer *pvis)
    : m_pvis{ pvis }
{
}

void Algorithm::bubble_sort()
{
    for (int i = 0; i < m_pvis->size(); i++) {
        for (int j = 0; j < m_pvis->size() - i - 1; j++) {
            if (m_pvis->compare(j, j + 1, ">")) {
                std::swap(*m_pvis->access(j), *m_pvis->access(j + 1));
            }
        }
    }

    m_pvis->validate_sorted();
}

void Algorithm::selection_sort()
{
    for (int i = 0; i < m_pvis->size(); i++) {
        int min = i;
        for (int j = i + 1; j < m_pvis->size(); j++) {
            if (m_pvis->compare(j, min, "<")) {
                min = j;
            }
        }
        std::swap(*m_pvis->access(i), *m_pvis->access(min));
    }

    m_pvis->validate_sorted();
}

void Algorithm::insertion_sort()
{
    for (int i = 1; i < m_pvis->size(); i++) {
        int j = i;
        while (j > 0 && m_pvis->compare(j, j - 1, "<")) {
            std::swap(*m_pvis->access(j), *m_pvis->access(j - 1));
            j--;
        }
    }

    m_pvis->validate_sorted();
}

void Algorithm::merge_sort()
{
    if (m_pvis->size() <= 1)
        return;

    merge_sort_internal(0, m_pvis->size() - 1);

    m_pvis->validate_sorted();
}

void Algorithm::quick_sort()
{
    if (m_pvis->size() <= 1)
        return;

    quick_sort_internal(0, m_pvis->size() - 1);

    m_pvis->validate_sorted();
}

void Algorithm::heap_sort()
{
    if (m_pvis->size() <= 1)
        return;

    heap_sort_internal(0, m_pvis->size() - 1);

    m_pvis->validate_sorted();
}

void Algorithm::counting_sort()
{
    for (int i = 0; i < m_pvis->size(); i++) {
        int j = i;
        while (j > 0 && m_pvis->compare(j, j - 1, "<")) {
            std::swap(*m_pvis->access(j), *m_pvis->access(j - 1));
            j--;
        }
    }

    m_pvis->validate_sorted();
}

void Algorithm::radix_sort()
{
    for (int i = 0; i < m_pvis->size(); i++) {
        int j = i;
        while (j > 0 && m_pvis->compare(j, j - 1, "<")) {
            std::swap(*m_pvis->access(j), *m_pvis->access(j - 1));
            j--;
        }
    }

    m_pvis->validate_sorted();
}

void Algorithm::merge_sort_internal(int start, int end) {
    if (start >= end)
        return;

    int mid = (start + end) / 2;

    merge_sort_internal(start, mid);
    merge_sort_internal(mid + 1, end);

    int i = start;
    int j = mid + 1;
    int k = 0;

    std::vector<int> temp(end - start + 1);

    while (i <= mid && j <= end) {
        if (m_pvis->compare(i, j, "<")) {
            temp[k++] = *m_pvis->access(i++);
        } else {
            temp[k++] = *m_pvis->access(j++);
        }
    }

    while (i <= mid) {
        temp[k++] = *m_pvis->access(i++);
    }

    while (j <= end) {
        temp[k++] = *m_pvis->access(j++);
    }

    for (int l = start, m = 0; l <= end; l++, m++) {
        *m_pvis->access(l) = temp[m];
    }
}

int Algorithm::quick_sort_partition(int start, int end) {
    int pivot = end;
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (m_pvis->compare(j, pivot, "<")) {
            i++;
            std::swap(*m_pvis->access(i), *m_pvis->access(j));
        }
    }

    std::swap(*m_pvis->access(i + 1), *m_pvis->access(pivot));
    return i + 1;
}

void Algorithm::quick_sort_internal(int start, int end) {
    if (start >= end)
        return;

    int pivot = quick_sort_partition(start, end);

    quick_sort_internal(start, pivot - 1);
    quick_sort_internal(pivot + 1, end);
}

void Algorithm::heapify(int start, int end) {
    int root = start;

    while (root * 2 + 1 <= end) {
        int child = root * 2 + 1;
        int swap = root;

        if (m_pvis->compare(swap, child, "<")) {
            swap = child;
        }

        if (child + 1 <= end && m_pvis->compare(swap, child + 1, "<")) {
            swap = child + 1;
        }

        if (swap == root) {
            return;
        } else {
            std::swap(*m_pvis->access(root), *m_pvis->access(swap));
            root = swap;
        }
    }
}

void Algorithm::heap_sort_internal(int start, int end) {
    for (int i = (end - 1) / 2; i >= start; i--) {
        heapify(i, end);
    }

    for (int i = end; i > start; i--) {
        std::swap(*m_pvis->access(start), *m_pvis->access(i));
        heapify(start, i - 1);
    }
}