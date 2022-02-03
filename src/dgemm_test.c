#include <stdio.h>

#include "qmckl_dgemm.h"

unsigned long long rdtsc(void)
{
  unsigned long long a, d;
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  return (d<<32) | a;
}

int main(int argc, char *argv[]) {

  double *A;
  double *B;
  double *C;
  int64_t DIM_M, DIM_N, DIM_K;
  int64_t M, N, K;
  int i;
  int64_t rep =(int64_t)atol(argv[1]);
  
  int64_t DIM_M_MAX =8*1024;
  int64_t DIM_N_MAX =6*1024;
  int64_t DIM_K_MAX =1024;

  M = DIM_M_MAX;
  N = DIM_N_MAX;
  K = DIM_K_MAX;
    
  qmckl_context context = qmckl_context_create();
  qmckl_context_struct* const ctx = (qmckl_context_struct* const) context;
  
  int64_t incRowA = K;
  int64_t incRowB = N;
  int64_t incRowC = N;
  
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
  
  // Initial call
  qmckl_dgemm_tiled_NN(context, M, N, K, A, incRowA,
			   B, incRowB,
			   C, incRowC);

  const uint64_t avx2t0 = rdtsc();
  // Subsequent calls
  for(i = 0; i < rep; ++i) {
    qmckl_dgemm_tiled_NN(context, M, N, K, A, incRowA,
			   B, incRowB,
			   C, incRowC);
  }
  const uint64_t avx2dt = rdtsc() - avx2t0;
  printf("CPU-Cycles [QMCKL_DGEMM(AVX2_16)] = %f\n", 1e-9 * avx2dt/rep);
  
  qmckl_context_destroy(context);
  free(A);
  free(B);
  free(C);

  return QMCKL_SUCCESS;
}
