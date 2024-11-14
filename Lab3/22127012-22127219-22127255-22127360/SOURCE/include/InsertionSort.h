#ifndef SORTING_ANALYSIS_INSERTIONSORT_H
#define SORTING_ANALYSIS_INSERTIONSORT_H

#include "SortStrategy.h"

class InsertionSort : public SortStrategy {
 public:
  InsertionSort() : SortStrategy() {}
  InsertionSort(int* a, int n) : SortStrategy(a, n) {}
  void sort() override;
  void sortWithComparison();
};

#endif