// C program to multiply two square matrices.
#include <stdio.h>
#define N 3
#include <time.h>
#include <sys/times.h>

// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]

double deltaTime(struct timespec* start, struct timespec* end) {
  double delta = (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec)/1e9;
  return delta;
}

void multiply(int mat1[][N], int mat2[][N], int res[][N])
{
  int i, j, k;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      res[i][j] = 0;
      for (k = 0; k < N; k++)
        res[i][j] += mat1[i][k]*mat2[k][j];
    }
  }
}

int main()
{
  struct timespec start;
  struct timespec end;
  double time;
  int mat1[N][N] = { {1, 1, 1},
    {2, 2, 2},
    {3, 3, 3}};
  
  int mat2[N][N] = { {1, 1, 1},
    {2, 2, 2},
    {3, 3, 3}};
  
  int res[N][N]; // To store result
  int i, j;
  
  clock_gettime(CLOCK_REALTIME, &start);
  multiply(mat1, mat2, res);
  clock_gettime(CLOCK_REALTIME, &end);
  time = deltaTime(&start,&end);
  printf("%f",time);
  
  printf("Result matrix is \n");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
      printf("%d ", res[i][j]);
    printf("\n");
  }
  
  return 0;
}
