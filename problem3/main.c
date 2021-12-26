#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void merge(int* arr, int left, int middle, int right) {
  int temp[middle - left + 1], temp2[right - middle];
  for (int i = 0; i < (middle - left + 1); i++) {
    temp[i] = arr[left + i];
  }
  for (int i = 0; i < (right - middle); i++) {
    temp2[i] = arr[middle + 1 + i];
  }
  int i = 0, j = 0, k = left;
  while (i < (middle - left + 1) && j < (right - middle)) {
    if (temp[i] < temp2[j]) {
      arr[k++] = temp[i++];
    } else {
      arr[k++] = temp2[j++];
    }
  }
  while (i < (middle - left + 1)) {
    arr[k++] = temp[i++];
  }
  while (j < (right - middle)) {
    arr[k++] = temp2[j++];
  }
}

void mergeSortSerial(int* arr, int left, int right) {
  if (left < right) {
    int middle = (left + right) / 2;
    mergeSortSerial(arr, left, middle);
    mergeSortSerial(arr, middle + 1, right);
    merge(arr, left, middle, right);
  }
}

void mergeSort(int* arr, int left, int right) {
  if (left < right) {
    int middle = (left + right) / 2;
#pragma omp task firstprivate(arr, left, middle)
    mergeSort(arr, left, middle);
#pragma omp task firstprivate(arr, middle, right)
    mergeSort(arr, middle + 1, right);
#pragma omp taskwait
    merge(arr, left, middle, right);

    merge(arr, left, middle, right);
  } else {
    mergeSortSerial(arr, left, right);
  }
}

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Input more arguments:\n ./file array_size threads_count\n");
    return 0;
  }
  int n = atoi(argv[1]);
  int p = atoi(argv[2]);
  int* arr = calloc(n, sizeof(*arr));

  int i;
  for (i = 0; i < n; i++) {
    arr[i] = rand() % n;
  }

  omp_set_num_threads(p);

  double start = omp_get_wtime();

  mergeSort(arr, 0, n - 1);

  double end = omp_get_wtime();
  printf("Elapsed time: %f\n", end - start);

  // for (int i = 0; i < n; i++) {
  //   printf("%d ", arr[i]);
  // }
  // printf("\n");

  return (0);
}
