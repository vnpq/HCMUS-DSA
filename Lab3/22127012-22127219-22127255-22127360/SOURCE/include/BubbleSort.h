#ifndef SORTING_ANALYSIS_BUBBLESORT_H
#define SORTING_ANALYSIS_BUBBLESORT_H
#include "SortStrategy.h"

class BubbleSort : public SortStrategy {
 public:
  BubbleSort() : SortStrategy() {}
  BubbleSort(int* a, int n) : SortStrategy(a, n) {}
  void sort() override;
  void sortWithComparison() override;
};

#endif  // SORTING_ANALYSIS_BUBBLESORT_H
