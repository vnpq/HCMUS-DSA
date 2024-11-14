#ifndef SORT_OBJECT
#define SORT_OBJECT

#include "SortContext.h"

class SortObject
{
    private:
        SortContext timeSort;
        SortContext compareSort;
    public:
        SortObject(SortingAlgorithm algo, int* a, int n);
        bool checkValid();
        void sort();
        double getDuration();
        long long getComparison();
};

#endif