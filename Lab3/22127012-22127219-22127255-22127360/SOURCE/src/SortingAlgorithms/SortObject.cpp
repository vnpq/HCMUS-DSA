#include "../../include/SortObject.h"

SortObject::SortObject(SortingAlgorithm algo, int* a, int n)
{
    timeSort.setStrategy(algo, a, n);
    compareSort.setStrategy(algo, a, n);
}

void SortObject::sort()
{
    timeSort.sort();
    compareSort.sortWithComparison();
}

double SortObject::getDuration()
{
    return timeSort.getDuration();
}

long long SortObject::getComparison()
{
    return compareSort.getComparison();
}

bool SortObject::checkValid()
{
    if (timeSort.getStrategy() == nullptr || compareSort.getStrategy() == nullptr)
        return false;
    return true;
}


