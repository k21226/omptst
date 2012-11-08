#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

double stoptime(); 
void disp();
double avg, avg2;
int N, NN;
double** M;

int main(){
	int itt = 100;
	double t = stoptime(); 
	N = pow(2, 10); NN = N*N;
	srand(time(NULL));
	M = new double* [N];
	for(int i = 0; i < N; i++){M[i] = new double[N];}
	for(int p = 0; p < itt; p++) disp();
	t = stoptime() - t;
	std::cout << t << "\t" << avg << "\t" << avg2 <<std::endl; 
	delete(M);
	return 0;
}
void disp(){
	#pragma omp parallel for
	for(int ii = 0; ii < NN; ii++){int i = ii/N; int j = ii%N; M[i][j] = 1.*rand()/RAND_MAX - .5;}
	avg = .0; avg2 = .0;	
	#pragma omp parallel for reduction(+:avg)
	for(int ii = 0; ii < NN; ii++){int i = ii/N; int j = ii%N; avg += M[i][j];}
	avg /= NN;
	#pragma omp parallel for
	for(int ii = 0; ii < NN; ii++){int i = ii/N; int j = ii%N; M[i][j] -= avg;}
	#pragma omp parallel for reduction(-:avg2)
	for(int ii = 0; ii < NN; ii++){int i = ii/N; int j = ii%N; avg2 += M[i][j]*M[i][j];}
	avg2 /= NN;
}
double stoptime(){
   struct timeval t;
   gettimeofday(&t, NULL);
   return (double) t.tv_sec + t.tv_usec/1000000.0;
}
