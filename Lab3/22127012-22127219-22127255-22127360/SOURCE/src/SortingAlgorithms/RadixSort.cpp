#include "../../include/RadixSort.h"

int RadixSort::getMax() {
  int mx = m_array[0];
  for (int i = 1; i < m_size; i++)
    if (m_array[i] > mx)
      mx = m_array[i];
  return mx;
}

// A function to do counting sort of m_array[]
// according to the digit
// represented by exp.
void RadixSort::countSort(int exp) {
  // Output array
  int* output = new int[m_size];
  int i, count[10] = {0};

  // Store count of occurrences
  // in count[]
  for (i = 0; i < m_size; i++)
    count[(m_array[i] / exp) % 10]++;

  // Change count[i] so that count[i]
  // now contains actual position
  // of this digit in output[]
  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];

  // Build the output array
  for (i = m_size - 1; i >= 0; i--) {
    output[count[(m_array[i] / exp) % 10] - 1] = m_array[i];
    count[(m_array[i] / exp) % 10]--;
  }

  // Copy the output array to m_array[],
  // so that m_array[] now contains sorted
  // numbers according to current digit
  for (i = 0; i < m_size; i++)
    m_array[i] = output[i];
}

// The main function to that sorts m_array[]
// of size n using Radix Sort
void RadixSort::sort() {
  m_timeStart = std::chrono::high_resolution_clock::now();
  // Find the maximum number to
  // know number of digits
  int m = getMax();

  // Do counting sort for every digit.
  // Note that instead of passing digit
  // number, exp is passed. exp is 10^i
  // where i is current digit number
  for (int exp = 1; m / exp > 0; exp *= 10)
    countSort(exp);
  m_timeEnd = std::chrono::high_resolution_clock::now();
}

//================With Comparison================

int RadixSort::getMaxWithComparison() {
  int mx = m_array[0];
  for (int i = 1; ++m_count_comparison && i < m_size; i++)
    if (++m_count_comparison && m_array[i] > mx)
      mx = m_array[i];
  return mx;
}

// A function to do counting sort of m_array[]
// according to the digit
// represented by exp.
void RadixSort::countSortWithComparison(int exp) {
  // Output array
  int* output = new int[m_size];
  int i, count[10] = {0};

  // Store count of occurrences
  // in count[]
  for (i = 0; ++m_count_comparison && i < m_size; i++)
    count[(m_array[i] / exp) % 10]++;

  // Change count[i] so that count[i]
  // now contains actual position
  // of this digit in output[]
  for (i = 1; ++m_count_comparison && i < 10; i++)
    count[i] += count[i - 1];

  // Build the output array
  for (i = m_size - 1; ++m_count_comparison && i >= 0; i--) {
    output[count[(m_array[i] / exp) % 10] - 1] = m_array[i];
    count[(m_array[i] / exp) % 10]--;
  }

  // Copy the output array to m_array[],
  // so that m_array[] now contains sorted
  // numbers according to current digit
  for (i = 0; ++m_count_comparison && i < m_size; i++)
    m_array[i] = output[i];
}

void RadixSort::sortWithComparison() {
  // Find the maximum number to
  // know number of digits
  int m = getMaxWithComparison();

  // Do counting sort for every digit.
  // Note that instead of passing digit
  // number, exp is passed. exp is 10^i
  // where i is current digit number
  for (int exp = 1; ++m_count_comparison && m / exp > 0; exp *= 10)
    countSortWithComparison(exp);
}
