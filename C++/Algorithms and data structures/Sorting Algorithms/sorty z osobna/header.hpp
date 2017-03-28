
#ifndef header_hpp
#define header_hpp

#include <stdio.h>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<fstream>

double selsort(int *tab, int param, int n);
double inssort(int *tab, int param, int n);
double shellsort(int*tab, int param, int n);
int calculate_gap(int n, int h);
void ** build_tabs(int**tab, int n, int k);
double quicksort_time( int tab[], int left, int right );
double quicksort_random_time( int tab[], int left, int right );
void quicksort( int tab[], int left, int right );
void quicksort_random( int tab[], int left, int right );
void max_heapify(int *a, int i, int n);
double heapsort(int *tab, int n);

#endif // header_h

