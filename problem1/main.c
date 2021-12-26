#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// int32_t
void print_matrix_int32(int32_t** c, int32_t n) {
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < n; j++) {
      printf("%d ", c[i][j]);
    }
    printf("\n");
  }
}

void print_matrix_in_file_int32(int32_t** c, int32_t n, FILE* file) {
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < n; j++) {
      fprintf(file, "%d ", c[i][j]);
    }
    fprintf(file, "\n");
  }
}

// ijk
void mult_ijk_int32(int32_t** a, int32_t** b, int32_t** c, int32_t n) {
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < n; j++) {
      for (int32_t k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// jik
void mult_jik_int32(int32_t** a, int32_t** b, int32_t** c, int32_t n) {
  for (int32_t j = 0; j < n; j++) {
    for (int32_t i = 0; i < n; i++) {
      for (int32_t k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// ikj
void mult_ikj_int32(int32_t** a, int32_t** b, int32_t** c, int32_t n) {
  for (int32_t i = 0; i < n; i++) {
    for (int32_t k = 0; k < n; k++) {
      int32_t r = a[i][k];
      for (int32_t j = 0; j < n; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
}

// jki
void mult_jki_int32(int32_t** a, int32_t** b, int32_t** c, int32_t n) {
  for (int32_t j = 0; j < n; j++) {
    for (int32_t k = 0; k < n; k++) {
      int32_t r = b[k][j];
      for (int32_t i = 0; i < n; i++) {
        c[i][j] += a[i][k] * r;
      }
    }
  }
}

// kij
void mult_kij_int32(int32_t** a, int32_t** b, int32_t** c, int32_t n) {
  for (int32_t k = 0; k < n; k++) {
    for (int32_t i = 0; i < n; i++) {
      int32_t r = a[i][k];
      for (int32_t j = 0; j < n; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
}

// kji
void mult_kji_int32(int32_t** a, int32_t** b, int32_t** c, int32_t n) {
  for (int32_t k = 0; k < n; k++) {
    for (int32_t j = 0; j < n; j++) {
      int32_t r = b[k][j];
      for (int32_t i = 0; i < n; i++) {
        c[i][j] += a[i][k] * r;
      }
    }
  }
}

// int64_t
void print_matrix_int64(int64_t** c, int32_t n) {
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < n; j++) {
      printf("%d ", c[i][j]);
    }
    printf("\n");
  }
}

void print_matrix_in_file_int64(int64_t** c, int32_t n, FILE* file) {
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < n; j++) {
      fprintf(file, "%d ", c[i][j]);
    }
    fprintf(file, "\n");
  }
}

// ijk
void mult_ijk_int64(int64_t** a, int64_t** b, int64_t** c, int32_t n) {
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < n; j++) {
      for (int32_t k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// jik
void mult_jik_int64(int64_t** a, int64_t** b, int64_t** c, int32_t n) {
  for (int32_t j = 0; j < n; j++) {
    for (int32_t i = 0; i < n; i++) {
      for (int32_t k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// ikj
void mult_ikj_int64(int64_t** a, int64_t** b, int64_t** c, int32_t n) {
  for (int32_t i = 0; i < n; i++) {
    for (int32_t k = 0; k < n; k++) {
      int64_t r = a[i][k];
      for (int32_t j = 0; j < n; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
}

// jki
void mult_jki_int64(int64_t** a, int64_t** b, int64_t** c, int32_t n) {
  for (int32_t j = 0; j < n; j++) {
    for (int32_t k = 0; k < n; k++) {
      int64_t r = b[k][j];
      for (int32_t i = 0; i < n; i++) {
        c[i][j] += a[i][k] * r;
      }
    }
  }
}

// kij
void mult_kij_int64(int64_t** a, int64_t** b, int64_t** c, int32_t n) {
  for (int32_t k = 0; k < n; k++) {
    for (int32_t i = 0; i < n; i++) {
      int64_t r = a[i][k];
      for (int32_t j = 0; j < n; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
}

// kji
void mult_kji_int64(int64_t** a, int64_t** b, int64_t** c, int32_t n) {
  for (int32_t k = 0; k < n; k++) {
    for (int32_t j = 0; j < n; j++) {
      int64_t r = b[k][j];
      for (int32_t i = 0; i < n; i++) {
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

  if (type_a != type_b) {
    printf(
        "Error: type of elements of matrix A isnt equal to the type of"
        " elements of matrix B\b");
    return 0;
  }

  int32_t n = size_a;
  if (type_a == 'd') {
    int32_t **a, **b, **c;
    a = calloc(n, sizeof(*a));
    b = calloc(n, sizeof(*b));
    c = calloc(n, sizeof(*c));

    for (int32_t i = 0; i < n; i++) {
      a[i] = calloc(n, sizeof(**a));
      b[i] = calloc(n, sizeof(**b));
      c[i] = calloc(n, sizeof(**c));
    }

    for (int32_t i = 0; i < n; i++) {
      for (int32_t j = 0; j < n; j++) {
        fscanf(file_a, "%d", &a[i][j]);
        fscanf(file_b, "%d", &b[i][j]);
      }
    }

    switch (mode) {
      case 0:
        mult_ijk_int32(a, b, c, n);
        break;
      case 1:
        mult_jik_int32(a, b, c, n);
        break;
      case 2:
        mult_ikj_int32(a, b, c, n);
        break;
      case 3:
        mult_jki_int32(a, b, c, n);
        break;
      case 4:
        mult_kij_int32(a, b, c, n);
        break;
      case 5:
        mult_kji_int32(a, b, c, n);
        break;
    }
    print_matrix_int32(c, n);
    print_matrix_in_file_int32(c, n, file_c);

    for (int i = 0; i < n; i++) {
      free(a[i]);
      free(b[i]);
      free(c[i]);
    }
    free(a);
    free(b);
    free(c);
  } else if (type_a == 'l') {
    int64_t **a, **b, **c;
    a = calloc(n, sizeof(*a));
    b = calloc(n, sizeof(*b));
    c = calloc(n, sizeof(*c));

    for (int32_t i = 0; i < n; i++) {
      a[i] = calloc(n, sizeof(**a));
      b[i] = calloc(n, sizeof(**b));
      c[i] = calloc(n, sizeof(**c));
    }

    for (int32_t i = 0; i < n; i++) {
      for (int32_t j = 0; j < n; j++) {
        fscanf(file_a, "%d", &a[i][j]);
        fscanf(file_b, "%d", &b[i][j]);
      }
    }

    switch (mode) {
      case 0:
        mult_ijk_int64(a, b, c, n);
        break;
      case 1:
        mult_jik_int64(a, b, c, n);
        break;
      case 2:
        mult_ikj_int64(a, b, c, n);
        break;
      case 3:
        mult_jki_int64(a, b, c, n);
        break;
      case 4:
        mult_kij_int64(a, b, c, n);
        break;
      case 5:
        mult_kji_int64(a, b, c, n);
        break;
    }
    print_matrix_int64(c, n);
    print_matrix_in_file_int64(c, n, file_c);

    for (int32_t i = 0; i < n; i++) {
      free(a[i]);
      free(b[i]);
      free(c[i]);
    }
    free(a);
    free(b);
    free(c);
  }
  
  fclose(file_a);
  fclose(file_b);
  fclose(file_c);
  return 0;
}
