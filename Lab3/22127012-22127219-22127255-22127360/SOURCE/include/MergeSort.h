#ifndef SORTING_ANALYSIS_MERGESORT_H
#define SORTING_ANALYSIS_MERGESORT_H

#include "SortStrategy.h"

class MergeSort : public SortStrategy {
private:
  void mergeSort(int left, int right);
  void mergeTwoArrays(int left, int mid, int right);
public:
  MergeSort() : SortStrategy() {}
  MergeSort(int* a, int n) : SortStrategy(a, n) {}
  
  void mergeSortWithComparison(int left, int right);
  void mergeTwoArraysWithComparison(int left, int mid, int right);
  void sort() override;
  void sortWithComparison();
};

#endif