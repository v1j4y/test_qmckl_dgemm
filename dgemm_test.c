#include <stdio.h>

#include "mkl.h"

#include "qmckl_dgemm.h"

int main() {

  double *A;
  double *B;
  double *C;
  double *CUnpack;
  double *ABlas;
  double *BBlas;
  double *DBlas;
  int64_t DIM_M, DIM_N, DIM_K;
  int64_t M, N, K;
  int64_t MBlas, NBlas, KBlas;
  int64_t incColA = 1;
  int64_t incColB = 1;
  int64_t incColC = 1;
  int64_t iterM, iterN, iterK;
  int64_t rep = 0;
  int i;
  
  int64_t DIM_M_MAX =8*1024;
  int64_t DIM_N_MAX =6*1024;
  int64_t DIM_K_MAX =1024;

  DIM_M = DIM_M_MAX;
  DIM_N = DIM_N_MAX;
	DIM_K = DIM_K_MAX;
    
  
  qmckl_context context = qmckl_context_create();
  qmckl_context_struct* const ctx = (qmckl_context_struct* const) context;
  M = DIM_M;
  N = DIM_N;
  K = DIM_K;
  
  int64_t incRowA = K;
  int64_t incRowB = N;
  int64_t incRowC = N;//ctx->C_tile.Nt;
  
  A = (double *)malloc( M * K * sizeof(double));
  B = (double *)malloc( K * N * sizeof(double));
  C = (double *)aligned_alloc( 64, M * N * sizeof(double));
  
  for(i = 0 ; i < M*K ; i++)
  {
    A[i]= rand();
  }
  for(i = 0 ; i < K*N ; i++)
  {
    B[i]= rand();
  }
  for(i = 0 ; i < M*N ; i++)
  {
    C[i]= 0.0;
  }
  
  qmckl_dgemm_tiled_NN(context, M, N, K, A, incRowA,
			   B, incRowB,
			   C, incRowC);
  
  qmckl_context_destroy(context);
  free(A);
  free(B);
  free(C);

  return QMCKL_SUCCESS;
}
