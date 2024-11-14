#ifndef SORTING_ANALYSIS_FLASHSORT_H
#define SORTING_ANALYSIS_FLASHSORT_H
#include "SortStrategy.h"

class FlashSort : public SortStrategy {
 public:
  FlashSort() : SortStrategy() {}
  FlashSort(int* a, int n) : SortStrategy(a, n) {}

  void sort() override;
  void sortWithComparison();
};

#endif