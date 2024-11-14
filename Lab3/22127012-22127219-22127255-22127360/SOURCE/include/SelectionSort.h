#ifndef SELECTION_SORT
#define SELECTION_SORT

#include "SortStrategy.h"

class SelectionSort : public SortStrategy {
 public:
  SelectionSort(int* a, int n) : SortStrategy(a, n) {}
  void sort();
  void sortWithComparison();
};
#endif