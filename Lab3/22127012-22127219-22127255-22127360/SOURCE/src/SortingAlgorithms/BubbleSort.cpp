#include "../../include/BubbleSort.h"

void BubbleSort::sort() {
  m_timeStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < m_size; i++) {
    for (int j = 0; j < m_size - i - 1; j++) {
      if (m_array[j] > m_array[j + 1]) {
        int tmp = m_array[j];
        m_array[j] = m_array[j + 1];
        m_array[j + 1] = tmp;
      }
    }
  }
  m_timeEnd = std::chrono::high_resolution_clock::now();
}

void BubbleSort::sortWithComparison() {
  for (int i = 0; ++m_count_comparison && i < m_size; i++) {
    for (int j = 0; ++m_count_comparison && j < m_size - i - 1; j++) {
      if (++m_count_comparison && m_array[j] > m_array[j + 1]) {
        int tmp = m_array[j];
        m_array[j] = m_array[j + 1];
        m_array[j + 1] = tmp;
      }
    }
  }
}