#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>
#define SWAP(a, b) {int temp = a; a = b; b = temp;}

void SelectionSort(int* arr, const unsigned length) {
	for (unsigned i = 0; i < length; i++) {
		int min_index = i, min = 2147483647; // min имеет наибольшее возможное значения для int
		for (unsigned j = i; j < length; j++)
			if (arr[j] < min) {
				min = arr[j];
				min_index = j;
			}
		SWAP(arr[i], arr[min_index]);
	}
}

int* MergeSort(int* arr, const unsigned length) {
		if (length == 1) {
			int* temp = (int*)malloc(sizeof(int));
			*temp = *arr;
			return temp;
		}

		unsigned split_index = (length / 2);
		int* left_part = MergeSort(arr, split_index);
		int* right_part = MergeSort(arr + (split_index), length - (split_index));
		int* temp = (int*)malloc(length * sizeof(int));
		unsigned left_iterator = 0, right_iterator = 0;
		while (left_iterator < split_index && right_iterator < length - (split_index)) {
			if (left_part[left_iterator] < right_part[right_iterator])
				temp[left_iterator + right_iterator] = left_part[left_iterator++];
			else
				temp[left_iterator + right_iterator] = right_part[right_iterator++];
		}
		for (; left_iterator < split_index; left_iterator++)
			temp[left_iterator + right_iterator] = left_part[left_iterator];

		for (; right_iterator < length - (split_index); right_iterator++)
			temp[left_iterator + right_iterator] = right_part[right_iterator];

		free(left_part);
		free(right_part);

		return temp;
}

short isSorted(int* arr, const unsigned length) {
	for (int i = 0; i < length - 1; i++)
		if (arr[i] > arr[i + 1])
			return 0;
	return 1;
}

double SelectionSortTime(const int* arr, const unsigned length) {
	int* temp = new int[length];
	for (int i = 0; i < length; i++)
		temp[i] = arr[i];
	clock_t start = clock();
	SelectionSort(temp, length);
	clock_t end = clock();

	if (isSorted(temp, length)) {
		delete[] temp;
		return (double)(difftime(end, start) / CLOCKS_PER_SEC);
	}
	else
		return -1;
}

double MergeSortTime(const int* arr, const unsigned length) {
	int* temp = new int[length];
	for (int i = 0; i < length; i++)
		temp[i] = arr[i];
	int* t;
	clock_t start = clock();
	t = MergeSort(temp, length);
	clock_t end = clock();

	delete[] temp;
	temp = t;

	if (isSorted(temp, length)) {
		delete[] temp;
		return (double) (difftime(end, start) / CLOCKS_PER_SEC);
	}
	else
		return -1;
}