#include "../../include/SortStrategy.h"

SortStrategy::SortStrategy() {
  m_array = nullptr;
  m_count_comparison = m_size = 0;
}

SortStrategy::SortStrategy(int* a, int size) {
  m_size = size;
  m_array = new int[m_size];
  for (int i = 0; i < m_size; i++)
    m_array[i] = a[i];
}

int* SortStrategy::getArray() const {
  return m_array;
}

long long SortStrategy::getComparison() const {
  return m_count_comparison;
}

int SortStrategy::getSize() const {
  return m_size;
}

SortStrategy::~SortStrategy() {
  if (m_array != nullptr) {
    delete[] m_array;
  }
  m_count_comparison = m_size = 0;
}

double SortStrategy::getDuration() const {
  std::chrono::duration<double> duration = m_timeEnd - m_timeStart;
  double seconds = duration.count();
  return seconds;
}

void SortStrategy::display() {
  if (m_array == nullptr || m_size == 0) {
    std::cout << "cannot display empty array\n";
    return;
  }
  for (int i = 0; i < m_size; i++) {
    std::cout << m_array[i] << " ";
  }
  std::cout << "\n";
}

void SortStrategy::startTimer() {
  m_timeStart = std::chrono::high_resolution_clock::now();
}

void SortStrategy::stopTimer() {
  m_timeEnd = std::chrono::high_resolution_clock::now();
}

void SortStrategy::writeToFile(std::string FileName) {
  std::ofstream ofs(FileName);
  ofs << m_size << "\n";
  for (int i = 0; i < m_size; i++) {
    ofs << m_array[i] << " ";
  }
  ofs << "\n";
  ofs.close();
}