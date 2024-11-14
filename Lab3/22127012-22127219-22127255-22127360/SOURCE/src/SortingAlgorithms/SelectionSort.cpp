#include "../../include/SelectionSort.h"
#include <iostream>

void SelectionSort::sort() {
  m_timeStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < m_size; ++i) {
    int minPos = i;
    for (int j = i + 1; j < m_size; ++j)
      if (m_array[j] < m_array[minPos])
        minPos = j;
    std::swap(m_array[i], m_array[minPos]);
  }
  m_timeEnd = std::chrono::high_resolution_clock::now();
}

void SelectionSort::sortWithComparison() {
  for (int i = 0; ++m_count_comparison && i < m_size; ++i) {
    int minPos = i;
    for (int j = i + 1; ++m_count_comparison && j < m_size; ++j)
      if (++m_count_comparison && m_array[j] < m_array[minPos])
        minPos = j;
    std::swap(m_array[i], m_array[minPos]);
  }
}