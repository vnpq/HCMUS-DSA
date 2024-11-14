#include "../../include/ShakerSort.h"

// https://www.iostream.vn/article/bubble-sort-va-shaker-sort-01Si3U

void ShakerSort::sort() {
  m_timeStart = std::chrono::high_resolution_clock::now();
  int l = 0, r = m_size - 1;
  int lastSwap = 0;
  while (l < r) {
    for (int i = l; i < r; ++i)
      if (m_array[i] > m_array[i + 1]) {
        std::swap(m_array[i], m_array[i + 1]);
        lastSwap = i;
      }

    r = lastSwap;

    for (int i = r; i > l; --i)
      if (m_array[i] < m_array[i - 1]) {
        std::swap(m_array[i], m_array[i - 1]);
        lastSwap = i;
      }

    l = lastSwap;
  }
  m_timeEnd = std::chrono::high_resolution_clock::now();
}

void ShakerSort::sortWithComparison() {
  int l = 0, r = m_size - 1;
  int lastSwap = 0;
  while (++m_count_comparison && l < r) {
    for (int i = l; ++m_count_comparison && i < r; ++i)
      if (++m_count_comparison && m_array[i] > m_array[i + 1]) {
        std::swap(m_array[i], m_array[i + 1]);
        lastSwap = i;
      }

    r = lastSwap;

    for (int i = r; ++m_count_comparison && i > l; --i)
      if (++m_count_comparison && m_array[i] < m_array[i - 1]) {
        std::swap(m_array[i], m_array[i - 1]);
        lastSwap = i;
      }

    l = lastSwap;
  }
}