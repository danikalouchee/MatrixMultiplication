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
  double *testCC;
  int myid, numprocs;
  double starttime, endtime;
  int perRows, rowsLeft, offset;
  
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
      
      perRows = nrows / (numprocs-1);
      rowsLeft = nrows / (numprocs-1);
      offset = 0;
      
	  int i, j;
	  for(i=1;i<numprocs;i++) {
		  number *= i;
		  printf("sending to %d\n", i);
		  MPI_Send(&(bb[0]), 2*nrows*ncols, MPI_INT, i, 0, MPI_COMM_WORLD);
          MPI_Send(&offset,1, MPI_INT, i, 0, MPI_COMM_WORLD);
          if(i== numprocs-1)
            perRows += rowsLeft;
          MPI_Send(&perRows,1, MPI_INT, i, 0, MPI_COMM_WORLD);
          for (j=0; j< nrows*perRows; j++){
            MPI_Send(&(aa[offset*ncols+j]),2,MPI_INT,i,0,MPI_COMM_WORLD);
          }
          MPI_Send(&(bb[offset*ncols+j]),2*ncols,MPI_INT,i,0,MPI_COMM_WORLD);
          offset+=perRows;
	  }
      
      testCC = malloc(sizeof(double)*2 *nrows*nrows);
      for(i=1;i<numprocs;i++){
        MPI_Recv(&offset,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(&(testCC[nrows*offset]),2*nrows*nrows,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      }
      cc1 = testCC;
      
      /* Insert your master code here to store the product into cc1 */
      endtime = MPI_Wtime();
      printf("%f\n",(endtime - starttime));
      cc2  = malloc(sizeof(double) * nrows * nrows);
      mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
      compare_matrices(cc2, cc1, nrows, nrows);

    } else {
      // Slave Code goes here
	  bb = malloc(sizeof(double) * nrows * ncols);
	  MPI_Recv(&(bb[0]), 2*nrows*ncols, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      MPI_Recv(&offset,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      MPI_Recv(&perRows,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	  
      aa = malloc(sizeof(double)*ncols*perRows);
      testCC = malloc(sizeof(double)*nrows*nrows);
      
      in m,l;
      for(m=0; m<ncols*perRows;m++){
        MPI_Recv(&(aa[m]),2,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      }
      
      mmult(testCC,aa,perRows,ncols,bb,nrows,ncols);
      MPI_Send(&offset,1,MPI_INT,0,0,MPI_COMM_WORLD);
      MPI_Send(&(testCC[0]),2*nrows*nrows,MPI_INT,0,0,MPI_COMM_WORLD);
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
