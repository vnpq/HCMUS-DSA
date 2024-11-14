#ifndef SORTING_ANALYSIS_SORTCONTEXT_H
#define SORTING_ANALYSIS_SORTCONTEXT_H
#include "./SortStrategy.h"
#include "BubbleSort.h"
#include "FlashSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "RadixSort.h"
#include "SelectionSort.h"
#include "ShakerSort.h"
#include "CountingSort.h"
#include "QuickSort.h"
#include "ShellSort.h"
#include "common.h"

class SortContext : public SortStrategy {
 private:
  SortStrategy* strategy;

 public:
  SortContext() : strategy(nullptr) {}
  SortContext(SortStrategy* strat_) : strategy(strat_) {}
  SortContext(SortingAlgorithm algo, int* a, int n) {
    setStrategy(algo, a, n);
  }
  ~SortContext();
  void setStrategy(SortingAlgorithm algo, int* a, int n);
  void sort() { strategy->sort(); }
  void sortWithComparison() { strategy->sortWithComparison(); }
  void display() { strategy->display(); }
  long long getComparison() { return strategy->getComparison(); }
  SortStrategy* getStrategy() { return strategy; }
  double getDuration() { return strategy->getDuration(); }
  void writeToFile(std::string FileName) { strategy->writeToFile(FileName); }
};

#endif  // SORTING_ANALYSIS_SORTCONTEXT_H
