#ifndef SORTING_ANALYSIS_RADIXSORT_H
#define SORTING_ANALYSIS_RADIXSORT_H

#include "SortStrategy.h"

class RadixSort : public SortStrategy {
 private:
  int getMax();
  void countSort(int exp);
  int getMaxWithComparison();
  void countSortWithComparison(int exp);

 public:
  RadixSort() : SortStrategy() {}
  RadixSort(int* a, int n) : SortStrategy(a, n) {}
  void sort() override;
  void sortWithComparison();
};

#endif