#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: %s N\n", argv[0]);
    return -1;
  }

  int n = atoi(argv[1]);
  double* a = (double*)malloc(n * n * sizeof(double)); // Matrix A
  double* b = (double*)malloc(n * n * sizeof(double)); // Matrix B
  double* c = (double*)malloc(n * n * sizeof(double)); // Matrix C

  // Initialize the matrices to some values.
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      a[i * n + j] = i * n + j; // A[i][j]
      b[i * n + j] = j * n + i; // B[i][j]
      c[i * n + j] = 0; // C[i][j]
    }
  }

  double begin = get_time();

  /**************************************/
  /* Write code to calculate C = A * B. */
  /**************************************/

  // 行列aの入力
  printf("1つ目の行列aを入力\n");
  for(i = 0; i < n; ++i) {
    for(j = 0; j < n; ++j) {
      printf("a[%d][%d] = ", i, j);
      scanf("%d", &a[i * n + j]);
    }
  }

  // 行列bの入力
  printf("2つ目の行列bを入力\n");
  for(i = 0; i < n; ++i) {
    for(j = 0; j < n; ++j) {
      printf("b[%d][%d] = ", i, j);
      scanf("%d", &b[i * n + j]);
    }
  }

  int k, term;
  for(i = 0; i < n; ++i) {
    for(j = 0; j < n; ++j) {
      c[i * n + j] = a[i * n + j] * b[i * n + j];
 
      // 行列の項を計算
      for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
          term = 0;
          for(k = 0; k < n; k++)
            term = term + a[i * n + k]*b[k * n + j];
          c[i * n + j] = term;
        }
      }
    }
  }

  double end = get_time();
  printf("time: %.6lf sec\n", end - begin);

  // Print C for debugging. Comment out the print before measuring the execution time.
  double sum = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      sum += c[i * n + j];
      // printf("c[%d][%d]=%lf\n", i, j, c[i * n + j]);
    }
  }
  // Print out the sum of all values in C.
  // This should be 450 for N=3, 3680 for N=4, and 18250 for N=5.
  printf("\nsum: %.6lf\n", sum);

  free(a);
  free(b);
  free(c);
  return 0;
}
