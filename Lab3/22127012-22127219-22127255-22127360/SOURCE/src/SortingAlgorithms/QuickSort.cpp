#include "../../include/QuickSort.h"

int getRandom(int l, int r) {
  srand(time(NULL));
  return 1ll * rand() % (r - l + 1) + l;
}

void QuickSort::quickSort(int l, int r) {
 if (l == r) return;
 int index = getRandom(l, r);
 int pivot = m_array[index], left = l, right = r;
 while (left <= right) {
   while (m_array[left] < pivot) ++left;
   while (pivot < m_array[right]) --right;
   if (left <= right) {
     std::swap(m_array[left], m_array[right]);
     ++left, --right;
   }
 }

 if (left < r)
   quickSort(left, r);
 if (l < right)
   quickSort(l, right);
}

void QuickSort::sort() {
  m_timeStart = std::chrono::high_resolution_clock::now();
  quickSort(0, m_size - 1);
  m_timeEnd = std::chrono::high_resolution_clock::now();
}

void QuickSort::quickSortWithComparison(int l, int r) {
  if (++m_count_comparison && l == r) return;
  int pivot = m_array[l], left = l, right = r;
  while (++m_count_comparison && left <= right) {
    while (++m_count_comparison && m_array[left] < pivot) ++left;
    while (++m_count_comparison && pivot < m_array[right]) --right;
    if (++m_count_comparison && left <= right) {
      std::swap(m_array[left], m_array[right]);
      ++left, --right;
    }
  }

  if (++m_count_comparison && left < r)
    quickSort(left, r);
  if (++m_count_comparison && l < right)
    quickSort(l, right);
}

void QuickSort::sortWithComparison() {
  m_count_comparison = 0;
  quickSortWithComparison(0, m_size - 1);
}