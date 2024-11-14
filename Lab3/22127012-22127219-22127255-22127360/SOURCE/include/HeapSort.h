#ifndef HEAP_SORT
#define HEAP_SORT
#include "SortStrategy.h"

class HeapSort : public SortStrategy {
 public:
  HeapSort(int* a, int n) : SortStrategy(a, n) {}

  void heapify(int i, int m_size);
  void sort() override;
  void sortWithComparison() override;
  void heapifyWithComparison(int i, int m_size);
};

#endif