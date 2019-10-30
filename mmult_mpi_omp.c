#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
void compare_matrix(double *a, double *b, int nRows, int nCols);
void produceMatrix(double* a, int rows, int cols);
void produceMatrixToFile(double* a, int rows, int cols);

/** 
    Program to multiply a matrix times a matrix using both
    mpi to distribute the computation among nodes and omp
    to distribute the computation among threads.
*/

int main(int argc, char* argv[])
{
  char *inputFile1;
  char *inputFile2;
  FILE *if1;
  FILE *if2;
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
    
    
    if(argc > 2){
      inputFile1 = argv[1];
      inputFile2 = argv[2];
      
      if1 = fopen(inputFile1, "r");
      if(if1 == NULL){
        printf("cannot open %s\n", inputFile1);
        return 1;
      }
      if2 = fopen(inputFile2, "r");
      if(if2 == NULL){
        printf("cannot open %s\n", inputFile2);
        return 1;
      }
      
      int max_line = 2048 * 5;
      
      char *lineBuffer = (char *) malloc(max_line);
      
      
      char *line = NULL;
      size_t length = 0;
      ssize_t read;
      int c;
      int lineCount = 0;
      char *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8;
      char *pRow1, *pCol1, pRow2, *pCol2;
      pRow1 = (char *) malloc(8);
      pCol1 = (char *) malloc(8);
      pRow2 = (char *) malloc(8);
      pCol2 = (char *) malloc(8);
      char s[2] = " ";
      char *token;
      int row1, cols1, rows2, cols2;
      int tokenCount;
      
      while((read = getline(&line, &length, if1))!=-1){
        if(lineCount++ == 0){
          p1 = strstr(line, "rows(");
          if(p1){
            p2 = strstr(p1, ")c");
            if(p2){
              sprintf(pRow1, "%.*s", p2-p1-5, p1+5);
              p3 = strstr(line, "cols(");
              if(p3){
                p4 = strstr(p3, ")");
                if(p4){
                  sprintf(pCol1, "%.*s", p4-p3-5, p3+5);
                  row1 = atof(pRow1);
                  cols1 = atof(pCol1);
                }else{
                  printf("can't read matrix %s\n", inputFile1);
                  exit(1);
                }
              }else{
                printf("can't read matrix %s\n", inputFile1);
                exit(1);
              }
            }else{
              printf("can't read matrix %s\n", inputFile1);
              exit(1);
            }
          }else{
            printf("can't read matrix %s\n", inputFile1);
            exit(1);
          }
        }else{
          if(myid == 0){
            if(lineCount == 2){
              aa = malloc(sizeof(double)*row1*cols1);
            }
            token = strtok(line, s);
            tokenCount = 0;
            while(token != NULL){
              aa[((lineCount-2)*cols1) + tokenCount++] = atof(token);
              token = strtok(NULL, s);
            }
          }
        }
      }
      char *token1;
      lineCount = 0;
      length = 0;
      while((read = getline(&line, &length, if2))!=-1){
        if(lineCount++ == 0){
          p5 = strstr(line, "rows(");
          if(p5){
            p6 = strstr(p5, ")c");
            if(p6){
              sprintf(pRow1, "%.*s", p6-p5-5, p5+5);
              p7 = strstr(line, "cols(");
              if(p7){
                p8 = strstr(p7, ")");
                if(p8){
                  sprintf(pCol1, "%.*s", p8-p7-5, p7+5);
                  rows2 = atof(pRow1);
                  cols2 = atof(pCol1);
                }else{
                  printf("can't read matrix %s\n", inputFile2);
                  exit(1);
                }
              }else{
                printf("can't read matrix %s\n", inputFile2);
                exit(1);
              }
            }else{
              printf("can't read matrix %s\n", inputFile2);
              exit(1);
            }
          }else{
            printf("can't read matrix %s\n", inputFile2);
            exit(1);
          }
        }else{
          if(myid == 0){
            if(lineCount == 2){
              bb = malloc(sizeof(double)*rows2*cols2);
            }
            token1 = strtok(line, s);
            tokenCount = 0;
            while(token1 != NULL){
              bb[((lineCount-2)*cols2) + tokenCount++] = atof(token1);
              token1 = strtok(NULL, s);
            }
          }
        }
      }
      if(myid == 0){
        if(cols1 != rows2){
          printf("matrix dimensions do not comply with multplication requirements\n");
          printf("A: %dx%d\tB: %dx%d", row1, cols1, rows2, cols2);
        }
        
        produceMatrix(aa, row1, cols1);
        produceMatrix(bb, rows2, cols2);
      }
      
      nrows = row1;
      ncols = cols1;
      
      fclose(if1);
      fclose(if2);
      
      free(lineBuffer);
    }else{
      nrows = atoi(argv[1]);
      ncols = nrows;
    }
    
    if (myid == 0) {
      // Master Code goes here
      if(argc==2){
        aa = gen_matrix(nrows, ncols);
        bb = gen_matrix(ncols, nrows);
      }
      cc1 = malloc(sizeof(double) * nrows * nrows); 
      starttime = MPI_Wtime();
      
      perRows = nrows / (numprocs-1);
      rowsLeft = nrows / (numprocs-1);
      offset = 0;
      
	  int i, j;
	  for(i=1;i<numprocs;i++) {
		  printf("sending to %d\n", i);
		  MPI_Send(&(bb[0]), 2*nrows*ncols, MPI_INT, i, 0, MPI_COMM_WORLD);
          MPI_Send(&offset,1, MPI_INT, i, 0, MPI_COMM_WORLD);
          if(i== numprocs-1)
            perRows += rowsLeft;
          MPI_Send(&perRows,1, MPI_INT, i, 0, MPI_COMM_WORLD);
          for (j=0; j< nrows*perRows; j++){
            MPI_Send(&(aa[offset*ncols+j]),2,MPI_INT,i,0,MPI_COMM_WORLD);
          }
          MPI_Send(&(bb[offset*nrows]),2*ncols,MPI_INT,i,0,MPI_COMM_WORLD);
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
      produceMatrixToFile(cc2,nrows,ncols);
    } else {
      // Slave Code goes here
	  bb = malloc(sizeof(double) * nrows * ncols);
	  MPI_Recv(&(bb[0]), 2*nrows*ncols, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      MPI_Recv(&offset,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      MPI_Recv(&perRows,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	  
      aa = malloc(sizeof(double)*ncols*perRows);
      testCC = malloc(sizeof(double)*nrows*nrows);
      
      int m,l;
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
  for(i=0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			printf("%lf", a[i*rows+ j]);
		}
		printf("\n");
	}
}

void produceMatrixToFile(double *a, int rows, int cols){
  FILE *file = fopen("out.txt","w");
  
  int i,j;
  fprintf(file,"rows(%d)cols(%d)\n",rows,cols);
  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
      fprintf(file,"%lf",a[i*rows+j]);
    }
    fprintf(file,"\n");
  }
  fclose(file);
}
