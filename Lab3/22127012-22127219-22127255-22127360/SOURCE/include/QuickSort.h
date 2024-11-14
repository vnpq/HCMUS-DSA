#ifndef SORTING_ANALYSIS_QUICKSORT_H
#define SORTING_ANALYSIS_QUICKSORT_H

#include "SortStrategy.h"
class QuickSort : public SortStrategy {
public:
  QuickSort(): SortStrategy(){}
  QuickSort(int *a, int n): SortStrategy(a, n){}
  void quickSort(int l, int r);
  void quickSortWithComparison(int l, int r);
  void sort() override;
  void sortWithComparison() override;
};

#endif // SORTING_ANALYSIS_QUICKSORT_H
