//
// Created by Ly Dinh Minh Man on 12/07/2023.
//

#ifndef SORTING_ANALYSIS_SORTSTRATEGY_H
#define SORTING_ANALYSIS_SORTSTRATEGY_H
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>

class SortStrategy {
 protected:
  int* m_array;
  std::chrono::high_resolution_clock::time_point m_timeStart;
  std::chrono::high_resolution_clock::time_point m_timeEnd;
  long long m_count_comparison = 0;
  int m_size;

 public:
  SortStrategy();
  SortStrategy(int* a, int size);
  ~SortStrategy();

  virtual void sort() = 0;
  virtual void sortWithComparison() = 0;
  int* getArray() const;
  long long getComparison() const;
  int getSize() const;

  // return runtime in seconds
  double getDuration() const;
  void startTimer();
  void stopTimer();

  void writeToFile(std::string FileName);

  void display();
};

#endif  // SORTING_ANALYSIS_SORTSTRATEGY_H
