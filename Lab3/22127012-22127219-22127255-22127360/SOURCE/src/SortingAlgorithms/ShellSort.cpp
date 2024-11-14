#include "../../include/ShellSort.h"

void ShellSort::sort() {
  m_timeStart = std::chrono::high_resolution_clock::now();
  for (int g : gaps) {
    for (int i = g; i < m_size; i++) {
      int tmp = m_array[i], j = i;
      for (; j >= g && m_array[j - g] > tmp; j -= g)
        m_array[j] = m_array[j - g];

      m_array[j] = tmp;
    }
  }
  m_timeEnd = std::chrono::high_resolution_clock::now();
}

void ShellSort::sortWithComparison() {
  m_count_comparison = 0;
  for (int g : gaps) {
    for (int i = g; ++m_count_comparison && i < m_size; i++) {
      int tmp = m_array[i], j = i;
      for (; ++m_count_comparison && j >= g && ++m_count_comparison &&
             m_array[j - g] > tmp;
           j -= g)
        m_array[j] = m_array[j - g];

      m_array[j] = tmp;
    }
  }
}