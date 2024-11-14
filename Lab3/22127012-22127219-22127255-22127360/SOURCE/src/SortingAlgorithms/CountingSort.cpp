#include "../../include/CountingSort.h"

void CountingSort::sort() {
  m_timeStart = std::chrono::high_resolution_clock::now();
  
  memset(_cnt, 0, sizeof(_cnt));
  for (int i = 0; i < m_size; i++)
    _cnt[m_array[i]]++;
  int l = 0;
  for (int i = 0; i < MAX_VAL; i++) {
    for (; _cnt[i]; --_cnt[i], l++)
      m_array[l] = i;
  }

  m_timeEnd = std::chrono::high_resolution_clock::now();
}

void CountingSort::sortWithComparison() {
  m_count_comparison = 0;
  memset(_cnt, 0, sizeof(_cnt));
  for (int i = 0; ++m_count_comparison && i < m_size; i++)
    _cnt[m_array[i]]++;
  int l = 0;
  for (int i = 0; ++m_count_comparison && i < MAX_VAL; i++) {
    for (; _cnt[i]; --_cnt[i], l++)
      m_array[l] = i;
  }
}