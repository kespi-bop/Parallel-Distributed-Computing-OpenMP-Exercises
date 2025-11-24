#ifndef C_MATMAT_H
#define C_MATMAT_H

// Dichiarazioni delle funzioni pubbliche di c_timer.c

void matmatijk(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatkji(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatikj(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatjik(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatkij(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatjki(int ldA, int ldB, int ldC,
               double *A, double *B, double *C,
               int N1, int N2, int N3);

void matmatblock(int ldA, int ldB, int ldC, double *A, double *B, double *C, int N1, int N2, int N3, int dbA, int dbB, int dbC);

void matmatthread(int ldA, int ldB, int ldC, double *A, double *B, double *C,
                  int N1, int N2, int N3, int dbA, int dbB, int dbC, int NTROW, int NTCOL);

#endif // C_MATMAT_H