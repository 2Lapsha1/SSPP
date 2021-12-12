//#include <papi.h>
#include <stdio.h>
#include <stdlib.h>

void print_matrix(int** c, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", c[i][j]);
    }
    printf("\n");
  }
}

void print_matrix_in_file(int** c, int n, FILE* file) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fprintf(file, "%d ", c[i][j]);
    }
    fprintf(file, "\n");
  }
}

// ijk
void mult_ijk(int** a, int** b, int** c, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// jik
void mult_jik(int** a, int** b, int** c, int n) {
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// ikj
void mult_ikj(int** a, int** b, int** c, int n) {
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; k++) {
      int r = a[i][k];
      for (int j = 0; j < n; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
}

// jki
void mult_jki(int** a, int** b, int** c, int n) {
  for (int j = 0; j < n; j++) {
    for (int k = 0; k < n; k++) {
      int r = b[k][j];
      for (int i = 0; i < n; i++) {
        c[i][j] += a[i][k] * r;
      }
    }
  }
}

// kij
void mult_kij(int** a, int** b, int** c, int n) {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      int r = a[i][k];
      for (int j = 0; j < n; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
}

// kji
void mult_kji(int** a, int** b, int** c, int n) {
  for (int k = 0; k < n; k++) {
    for (int j = 0; j < n; j++) {
      int r = b[k][j];
      for (int i = 0; i < n; i++) {
        c[i][j] += a[i][k] * r;
      }
    }
  }
}

int main(int argc, char** argv) {
  FILE* file_a;
  FILE* file_b;
  FILE* file_c;

  if (argc < 5) {
    printf(
        "Too little arguments. Need 5:\n./file matrix_a_file matrix_b_file "
        "matrix_c_file "
        "multi_mode\n");
    return 0;
  }
  file_a = fopen(argv[1], "rb");
  file_b = fopen(argv[2], "rb");
  file_c = fopen(argv[3], "wb");
  int mode = atoi(argv[4]);
  if (mode < 0 || mode > 5) {
    printf("Incorrect mode input\n");
    return 0;
  }

  char type_a, type_b;
  int size_a, size_b;
  fscanf(file_a, "%c", &type_a);
  fscanf(file_a, "%d", &size_a);

  fscanf(file_b, "%c", &type_b);
  fscanf(file_b, "%d", &size_b);

  if (size_a != size_b) {
    printf("Error: size of matrix A isnt equal to the size of matrix B\n");
    return 0;
  }

  int n = size_a;
  int **a, **b, **c;
  a = calloc(n, sizeof(*a));
  b = calloc(n, sizeof(*b));
  c = calloc(n, sizeof(*c));

  for (int i = 0; i < n; i++) {
    a[i] = calloc(n, sizeof(**a));
    b[i] = calloc(n, sizeof(**b));
    c[i] = calloc(n, sizeof(**c));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fscanf(file_a, "%d", &a[i][j]);
      fscanf(file_b, "%d", &b[i][j]);
    }
  }

  /* int num_events = 6;
  long long values[6];
  int events[2] = {PAPI_L1_STM, PAPI_L1_LDM, PAPI_L1_TCM,
                   PAPI_L2_STM, PAPI_L2_LDM, PAPI_L2_TCM};

  //    PAPI_L1_TCM - total cache misses
  //    PAPI_L1_LDM - load misses
  //    PAPI_L1_STM - store cache misses

  if (PAPI_start_counters(events, num_events) != PAPI_OK) {
    printf("PAPI error: %d\n", 1);
    return 0;
  }
*/
  switch (mode) {
    case 0:
      mult_ijk(a, b, c, n);
      break;
    case 1:
      mult_jik(a, b, c, n);
      break;
    case 2:
      mult_ikj(a, b, c, n);
      break;
    case 3:
      mult_jki(a, b, c, n);
      break;
    case 4:
      mult_kij(a, b, c, n);
      break;
    case 5:
      mult_kji(a, b, c, n);
      break;
  }

  /* if (PAPI_stop_counters(values, num_events) != PAPI_OK) {
    printf("PAPI_stop_counters error\n");
    return 0;
  };

  printf("%lld, %lld, %lld, %lld, %lld, %lld\n", values[0], values[1],
         values[2], values[3], values[4], values[5]);
 */
  print_matrix(c, n);
  print_matrix_in_file(c, n, file_c);

  for (int i = 0; i < n; i++) {
    free(a[i]);
    free(b[i]);
    free(c[i]);
  }
  free(a);
  free(b);
  free(c);
  fclose(file_a);
  fclose(file_b);
  fclose(file_c);
  return 0;
}
