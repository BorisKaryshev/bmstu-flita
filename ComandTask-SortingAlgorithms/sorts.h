#ifndef sorts
#define sorts
#include <time.h>

void SelectionSort(int* arr, const unsigned length);
double SelectionSortTime(const int* arr, const unsigned length);

int* MergeSort(int* arr, const unsigned length);
double MergeSortTime(const int* arr, const unsigned length);

short isSorted(int* arr, const unsigned length);

#endif