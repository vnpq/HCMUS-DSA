#include "../../include/HeapSort.h"

// https://www.geeksforgeeks.org/heap-sort/

void HeapSort::heapify(int i, int m_size) {
  int maxPos = i;
  int L = 2 * i + 1;
  int R = 2 * i + 2;
  if (L < m_size && m_array[L] > m_array[maxPos])
    maxPos = L;
  if (R < m_size && m_array[R] > m_array[maxPos])
    maxPos = R;

  if (maxPos != i) {
    std::swap(m_array[i], m_array[maxPos]);
    heapify(maxPos, m_size);
  }
}

void HeapSort::sort() {
  // build max heap
  m_timeStart = std::chrono::high_resolution_clock::now();

  for (int i = m_size / 2 - 1; i >= 0; --i)
    heapify(i, m_size);

  // heap sort
  for (int i = m_size - 1; i >= 0; --i) {
    std::swap(m_array[0], m_array[i]);
    heapify(0, i);
  }

  m_timeEnd = std::chrono::high_resolution_clock::now();
}

void HeapSort::heapifyWithComparison(int i, int m_size) {
  int maxPos = i;
  int L = 2 * i + 1;
  int R = 2 * i + 2;
  if (++m_count_comparison && L < m_size)
    if (++m_count_comparison && m_array[L] > m_array[maxPos])
      maxPos = L;

  if (++m_count_comparison && R < m_size)
    if (++m_count_comparison && m_array[R] > m_array[maxPos])
      maxPos = R;

  if (++m_count_comparison && maxPos != i) {
    std::swap(m_array[i], m_array[maxPos]);
    heapifyWithComparison(maxPos, m_size);
  }
}

void HeapSort::sortWithComparison() {
  // build max heap
  for (int i = m_size / 2 - 1; i >= 0; --i)
    heapifyWithComparison(i, m_size);

  // heap sort
  for (int i = m_size - 1; i >= 0; --i) {
    std::swap(m_array[0], m_array[i]);
    heapifyWithComparison(0, i);
  }
}