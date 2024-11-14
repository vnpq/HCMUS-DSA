#include "../../include/FlashSort.h"

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

// Flash Sort algorithm
void FlashSort::sort() {
  m_timeStart = std::chrono::high_resolution_clock::now();
  int minVal = m_array[0];
  int max = 0;
  int m = int(0.45 * m_size);
  int* l = new int[m];
  for (int i = 0; i < m; i++)
    l[i] = 0;
  for (int i = 1; i < m_size; i++) {
    if (m_array[i] < minVal)
      minVal = m_array[i];
    if (m_array[i] > m_array[max])
      max = i;
  }
  if (m_array[max] == minVal)
    return;
  double c1 = (double)(m - 1) / (m_array[max] - minVal);
  for (int i = 0; i < m_size; i++) {
    int k = int(c1 * (m_array[i] - minVal));
    ++l[k];
  }
  for (int i = 1; i < m; i++)
    l[i] += l[i - 1];

  // swap
  swap(m_array[max], m_array[0]);

  int nmove = 0;
  int j = 0;
  int k = m - 1;
  int t = 0;
  int flash;
  while (nmove < m_size - 1) {
    while (j > l[k] - 1) {
      j++;
      k = int(c1 * (m_array[j] - minVal));
    }
    flash = m_array[j];
    if (k < 0)
      break;
    while (j != l[k]) {
      k = int(c1 * (flash - minVal));
      int hold = m_array[t = --l[k]];
      m_array[t] = flash;
      flash = hold;
      ++nmove;
    }
  }
  delete[] l;

  // insertion sort
  for (int i = 1; i < m_size; i++) {
    int key = m_array[i];
    int j = i - 1;

    // Move elements greater than key to one position ahead
    while (j >= 0 && m_array[j] > key) {
      m_array[j + 1] = m_array[j];
      j--;
    }

    // Place the key in its correct position
    m_array[j + 1] = key;
  }
  m_timeEnd = std::chrono::high_resolution_clock::now();
}

void FlashSort::sortWithComparison() {
  int minVal = m_array[0];
  int max = 0;
  int m = int(0.45 * m_size);
  int* l = new int[m];
  for (int i = 0; ++m_count_comparison && i < m; i++)
    l[i] = 0;
  for (int i = 1; ++m_count_comparison && i < m_size; i++) {
    if (++m_count_comparison && m_array[i] < minVal)
      minVal = m_array[i];
    if (++m_count_comparison && m_array[i] > m_array[max])
      max = i;
  }
  if (++m_count_comparison && m_array[max] == minVal)
    return;
  double c1 = (double)(m - 1) / (m_array[max] - minVal);
  for (int i = 0; ++m_count_comparison && i < m_size; i++) {
    int k = int(c1 * (m_array[i] - minVal));
    ++l[k];
  }
  for (int i = 1; ++m_count_comparison && i < m; i++)
    l[i] += l[i - 1];

  // swap
  swap(m_array[max], m_array[0]);
  m_count_comparison += 3;

  int nmove = 0;
  int j = 0;
  int k = m - 1;
  int t = 0;
  int flash;
  while (++m_count_comparison && nmove < m_size - 1) {
    while (++m_count_comparison && j > l[k] - 1) {
      j++;
      k = int(c1 * (m_array[j] - minVal));
    }
    flash = m_array[j];
    if (++m_count_comparison && k < 0)
      break;
    while (++m_count_comparison && j != l[k]) {
      k = int(c1 * (flash - minVal));
      int hold = m_array[t = --l[k]];
      m_array[t] = flash;
      flash = hold;
      ++nmove;
    }
  }
  delete[] l;

  // insertion sort
  for (int i = 1; ++m_count_comparison && i < m_size; i++) {
    int key = m_array[i];
    int j = i - 1;

    // Move elements greater than key to one position ahead
    while (++m_count_comparison && j >= 0 && ++m_count_comparison &&
           m_array[j] > key) {
      m_array[j + 1] = m_array[j];
      j--;
    }

    // Place the key in its correct position
    m_array[j + 1] = key;
  }
}
