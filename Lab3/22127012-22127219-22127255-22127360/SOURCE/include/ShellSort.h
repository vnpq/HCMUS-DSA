#ifndef SORTING_ANALYSIS_SHELLSORT_H
#define SORTING_ANALYSIS_SHELLSORT_H

#include "SortStrategy.h"
class ShellSort : public SortStrategy {
  const int gaps[8] = {1, 4, 10, 23, 57, 132, 301, 701};

 public:
  ShellSort() : SortStrategy() {}
  ShellSort(int* a, int n) : SortStrategy(a, n) {}
  void sort() override;
  void sortWithComparison() override;
};

#endif  // SORTING_ANALYSIS_SHELLSORT_H
