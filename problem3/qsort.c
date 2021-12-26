#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int comp(const void* i, const void* j) {
  return *(int*)i - *(int*)j;
}

int main(int argc, char** argv) {
  int n = 1000000;
  int* arr = calloc(n, sizeof(*arr));

  int i;
  for (i = 0; i < n; i++) {
    arr[i] = rand() % n;
  }

  double start = omp_get_wtime();

  qsort(arr, n, sizeof(*arr), comp);

  double end = omp_get_wtime();
  printf("Elapsed time: %f\n", end - start);

  // for (int i = 0; i < n; i++) {
  //  printf("%d ", arr[i]);
  //}
  // printf("\n");

  return (0);
}
