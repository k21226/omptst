#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

double stoptime(); 
double AvgM();
double avg, avg2;
int N, NN;
double** M;

int main(){
	int itt = 100;
	double Avg = .0;
	N = pow(2, 10); NN = N*N;
	srand(time(NULL));
	M = new double* [N];
	for(int i = 0; i < N; i++){M[i] = new double[N];}
	for(int ii = 0; ii < NN; ii++){int i = ii/N; int j = ii%N; M[i][j] = 1.*rand()/RAND_MAX - .5;}
	double t = stoptime();
	#pragma omp parallel for reduction(+:Avg)
	for(int p = 0; p < itt; p++) Avg += AvgM();
	t = stoptime() - t;
	std::cout << t << "\t" << Avg/itt <<std::endl; 
	delete(M);
	return 0;
}
double AvgM(){
	avg = .0; 
	for(int ii = 0; ii < NN; ii++){int i = ii/N; int j = ii%N; avg += M[i][j];}
	avg /= NN;
	return avg;
}
double stoptime(){
   struct timeval t;
   gettimeofday(&t, NULL);
   return (double) t.tv_sec + t.tv_usec/1000000.0;
}
