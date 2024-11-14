#include "../../include/SortContext.h"

void SortContext::setStrategy(SortingAlgorithm algo, int* a, int n) {
  if (strategy) {
    delete strategy;
    strategy = nullptr;
  }
  switch (algo) {
    case SortingAlgorithm::BubbleSort:
      strategy = new BubbleSort(a, n);
      break;
    case SortingAlgorithm::SelectionSort:
      strategy = new SelectionSort(a, n);
      break;
    case SortingAlgorithm::InsertionSort:
      strategy = new InsertionSort(a, n);
      break;
    case SortingAlgorithm::HeapSort:
      strategy = new HeapSort(a, n);
      break;
    case SortingAlgorithm::MergeSort:
      strategy = new MergeSort(a, n);
      break;
    case SortingAlgorithm::QuickSort:
      strategy = new QuickSort(a, n);
      break;
    case SortingAlgorithm::RadixSort:
      strategy = new RadixSort(a, n);
      break;
    case SortingAlgorithm::ShakerSort:
      strategy = new ShakerSort(a, n);
      break;
    case SortingAlgorithm::ShellSort:
      strategy = new ShellSort(a, n);
      break;
    case SortingAlgorithm::CountingSort:
      strategy = new CountingSort(a, n);
      break;
    case SortingAlgorithm::FlashSort:
      strategy = new FlashSort(a, n);
      break;
  }
}

SortContext::~SortContext() {
  if (strategy) {
    delete strategy;
  }
}