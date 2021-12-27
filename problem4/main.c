#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <mpi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int size, rank;

  assert((argc == 4) && "Not enough arguments");

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    FILE* file_a;
    FILE* file_b;
    FILE* file_c;

    file_a = fopen(argv[1], "rb");
    file_b = fopen(argv[2], "rb");
    file_c = fopen(argv[3], "wb");

    int64_t matrix_size, vector_size;
    fscanf(file_a, "%" SCNd64, &matrix_size);
    fscanf(file_b, "%" SCNd64, &vector_size);
    assert((matrix_size == vector_size) && "Invalid sizes");

    // Выделение памяти
    int64_t** matrix_a;
    matrix_a = calloc(matrix_size, sizeof(*matrix_a));
    for (int64_t i = 0; i < matrix_size; i++) {
      matrix_a[i] = calloc(matrix_size, sizeof(**matrix_a));
    }
    int64_t *vector_b, *vector_c;
    vector_b = calloc(vector_size, sizeof(*vector_b));
    vector_c = calloc(vector_size, sizeof(*vector_c));

    for (int64_t i = 0; i < matrix_size; i++) {
      fscanf(file_b, "%" SCNd64, &vector_b[i]);
      for (int64_t j = 0; j < matrix_size; j++) {
        fscanf(file_a, "%" SCNd64, &matrix_a[i][j]);
      }
    }
    double time_start, time_end;
    time_start = MPI_Wtime();

    if (size == 1) {
      for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
          vector_c[i] += matrix_a[i][j] * vector_b[j];
        }
      }
    } else {
      // Распределяем все строки матрицы А между процессами
      int64_t *rows_count_to_mpi, *mpi_poz_rows;
      rows_count_to_mpi = calloc(size - 1, sizeof(*rows_count_to_mpi));
      mpi_poz_rows = calloc(size - 1, sizeof(*mpi_poz_rows));
      int64_t r = matrix_size % (size - 1);
      for (int64_t i = 0; i < r; i++) {
        rows_count_to_mpi[i]++;
      }
      for (int64_t i = 0; i < size - 1; i++) {
        rows_count_to_mpi[i] += matrix_size / (size - 1);
        if (i > 0) {
          mpi_poz_rows[i] = mpi_poz_rows[i - 1] + rows_count_to_mpi[i - 1];
        } else {
          mpi_poz_rows[i] = 0;
        }
      }

      int64_t current_poz = 0;
      for (int64_t i = 1; i < size; i++) {
        MPI_Send(&rows_count_to_mpi[i - 1], 1, MPI_INT64_T, i, 0,
                 MPI_COMM_WORLD);
        MPI_Send(&matrix_size, 1, MPI_INT64_T, i, 0, MPI_COMM_WORLD);
        for (int64_t j = 0; j < rows_count_to_mpi[i - 1]; j++) {
          MPI_Send(matrix_a[current_poz++], (int)matrix_size, MPI_INT64_T, i, 0,
                   MPI_COMM_WORLD);
        }
        MPI_Send(vector_b, (int)vector_size, MPI_INT64_T, i, 0, MPI_COMM_WORLD);
      }
      MPI_Barrier(MPI_COMM_WORLD);

      // Получение данных
      for (int64_t i = 1; i < size; i++) {
        int64_t vector_c_recv[(int)rows_count_to_mpi[i - 1]];
        MPI_Recv(vector_c_recv, (int)rows_count_to_mpi[i - 1], MPI_INT64_T, i,
                 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int64_t j = 0; j < rows_count_to_mpi[i - 1]; j++) {
          vector_c[j + mpi_poz_rows[i - 1]] = vector_c_recv[j];
        }
      }
      MPI_Barrier(MPI_COMM_WORLD);
      free(rows_count_to_mpi);
      free(mpi_poz_rows);
    }
    time_end = MPI_Wtime();
    double elapsed_time = time_end - time_start;
    printf("Elapsed time: %f\n", elapsed_time);

    // вывод вектора С в файл
    for (int64_t i = 0; i < matrix_size; i++) {
      fprintf(file_c, "% " PRId64, vector_c[i]);
    }
    fprintf(file_c, "\n");

    free(vector_c);
    free(vector_b);
    for (int64_t i = 0; i < matrix_size; i++) {
      free(matrix_a[i]);
    }
    free(matrix_a);

    fclose(file_a);
    fclose(file_b);
    fclose(file_c);
  } else {
    // Получение всех данных
    int64_t count, matrix_size;
    MPI_Recv(&count, 1, MPI_INT64_T, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&matrix_size, 1, MPI_INT64_T, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);

    int64_t** matrix_a_rows;
    matrix_a_rows = calloc(count, sizeof(*matrix_a_rows));
    for (int64_t i = 0; i < count; i++) {
      matrix_a_rows[i] = calloc(matrix_size, sizeof(**matrix_a_rows));
    }
    int64_t* vector_b;
    vector_b = calloc(matrix_size, sizeof(*vector_b));

    for (int64_t i = 0; i < count; i++) {
      MPI_Recv(matrix_a_rows[i], (int)matrix_size, MPI_INT64_T, 0, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Recv(vector_b, (int)matrix_size, MPI_INT64_T, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);

    MPI_Barrier(MPI_COMM_WORLD);

    // Подсчет
    int64_t* vector_c;
    vector_c = calloc(count, sizeof(*vector_c));

    for (int64_t i = 0; i < count; i++) {
      for (int64_t j = 0; j < matrix_size; j++) {
        vector_c[i] += matrix_a_rows[i][j] * vector_b[j];
      }
    }

    MPI_Send(vector_c, (int)count, MPI_INT64_T, 0, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    free(vector_c);
    free(vector_b);
    for (int64_t i = 0; i < count; i++) {
      free(matrix_a_rows[i]);
    }
    free(matrix_a_rows);
  }

  MPI_Finalize();
  return 0;
}
