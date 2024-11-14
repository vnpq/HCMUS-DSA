#ifndef SHAKER_SORT
#define SHAKER_SORT
#include "SortStrategy.h"

class ShakerSort : public SortStrategy {
 public:
  ShakerSort(int* a, int n) : SortStrategy(a, n) {}
  void sort();
  void sortWithComparison();
};
#endif