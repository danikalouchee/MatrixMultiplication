#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
void compare_matrix(double *a, double *b, int nRows, int nCols);
void produceMatrix(double* a, int rows, int cols);

/** 
    Program to multiply a matrix times a matrix using both
    mpi to distribute the computation among nodes and omp
    to distribute the computation among threads.
*/

int main(int argc, char* argv[])
{
  int nrows, ncols;
  double *aa;	/* the A matrix */
  double *bb;	/* the B matrix */
  double *cc1;	/* A x B computed using the omp-mpi code you write */
  double *cc2;	/* A x B computed using the conventional algorithm */
  int myid, numprocs;
  double starttime, endtime;
  MPI_Status status;
  /* insert other global variables here */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  if (argc > 1) {
    nrows = atoi(argv[1]);
    ncols = nrows;
    if (myid == 0) {
      // Master Code goes here
      aa = gen_matrix(nrows, ncols);
      bb = gen_matrix(ncols, nrows);
      cc1 = malloc(sizeof(double) * nrows * nrows); 
      starttime = MPI_Wtime();
	  int i;
	  for(i=1;i<numprocs;i++) {
		  number *= i;
		  printf("sending to %d\n", i);
		  MPI_Send(&(aa[0]), 2*nrows*ncols, MPI_INT, i, 0, MPI_COMM_WORLD);
	  }
      /* Insert your master code here to store the product into cc1 */
      endtime = MPI_Wtime();
      printf("%f\n",(endtime - starttime));
      cc2  = malloc(sizeof(double) * nrows * nrows);
      mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
      compare_matrices(cc2, cc1, nrows, nrows);

    } else {
      // Slave Code goes here
	  aa = malloc(sizeof(double) * nrows * ncols);
	  MPI_Recv(&(aa[0]), 2*nrows*ncols, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	  produceMatrix(aa, nrows, ncols);
    }
  } else {
    fprintf(stderr, "Usage matrix_times_vector <size>\n");
  }
  MPI_Finalize();
  return 0;
}

void produceMatrix(double *a, int rows, int cols) {
	int i,j;
	printf("\n");
	for(i=0, i < rows; i++) {
		for(j = 0; j < cols; j++) {
			printf("%lf", a[i*rows+ j]);
		}
		printf("\n");
	}
}
