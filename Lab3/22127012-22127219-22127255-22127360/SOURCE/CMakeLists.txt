cmake_minimum_required(VERSION 3.25)
project(sorting_analysis)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(sorting_analysis
               src/utils/DataGenerator.h
               src/utils/DataGenerator.cpp
               src/CommandLine.h
               src/CommandLine.cpp
               src/main.cpp
               include/common.h
               include/BubbleSort.h
               src/SortingAlgorithms/BubbleSort.cpp
               include/CountingSort.h
               src/SortingAlgorithms/CountingSort.cpp
               include/FlashSort.h
               src/SortingAlgorithms/FlashSort.cpp
               include/InsertionSort.h
               src/SortingAlgorithms/InsertionSort.cpp
               include/MergeSort.h
               src/SortingAlgorithms/MergeSort.cpp
               include/RadixSort.h
               src/SortingAlgorithms/RadixSort.cpp
               include/SelectionSort.h
               src/SortingAlgorithms/SelectionSort.cpp
               include/HeapSort.h
               src/SortingAlgorithms/HeapSort.cpp
               include/ShakerSort.h
               src/SortingAlgorithms/ShakerSort.cpp
               include/ShellSort.h
               src/SortingAlgorithms/ShellSort.cpp
               include/QuickSort.h
               src/SortingAlgorithms/QuickSort.cpp
               include/SortContext.h
               src/SortingContext/SortContext.cpp
               include/SortStrategy.h
               src/SortingStrategy/SortStrategy.cpp
               )

target_link_libraries(sorting_analysis -static)
