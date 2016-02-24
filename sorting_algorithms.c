//Justin Johnson, Z23136514
//Design and Analysis of Algorithms
//Spring 2016
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "sorting_algorithms.h"


void main(){
	//generate random seed
	srand(time(NULL));
	//Specifications provided by Assignment Directions
	int n;			//current working array size
	int rtCount = (N_FINISH - N_START)/DELTA + 1;	//Total number or array sizes being timed during Run Time testing
	int i, j;

	//declare arrays that will store the run times for each sorting algorithm
	//[0] = time for 1000 elements, [1] = time for 2000 elements, ..., [19] = time for 20000 elements
	double insertionSortRunTimes[rtCount];
	clearArrayD(insertionSortRunTimes, rtCount);
	double mergeSortRunTimes[rtCount];
	clearArrayD(mergeSortRunTimes, rtCount);
	double quickSortRunTimes[rtCount];
	clearArrayD(quickSortRunTimes, rtCount);

	//generate arrays from N_START to N_FINISH, incrementing each array by size DELTA 
	for(n = N_START, i = 0; n <= N_FINISH; n += DELTA, i++){
		printf("Running Insertion Sort, Merge Sort, and Quick Sort on matching arrays with %d elements\n", n);
		//create m different arrays, calculate time for each, then average
		int m;
		for(m = 0; m < 10; m++){
			//create 3 identical arrays of size n with values 0 <= a[i] <= RANGE
			int *a = generateArray(n, RANGE);
			int *b = copyArray(a, n);
			int *c = copyArray(a, n);
			//PERFORM INSERTION SORT ON ARRAY A AND RECORD RUN TIMES
			insertionSortRunTimes[i] += insertionSort(a,n);
			//PERFORM MERGE SORT ON ARRAY B AND RECORD RUN TIMES
			mergeSortRunTimes[i] += startMergeSort(b, 0, n-1);
			//PERFORM QUICK SORT ON ARRAY C AND RECORD RUN TIMES
			quickSortRunTimes[i] += startQuickSort(c, 0, n-1);
			
			//CHECK CORRECTNESS OF SORTING ALGORITHMS ONCE, DURING 1ST ITERATION
			//IF 1ST ITERATION IS CORRECT, WE WILL ASSUME ALL REMAINING ITERATIONS ARE CORRECT
			if(i == 0 && m == 0){
				printf("\nArray of 1000 elements after Insertion Sort:");
				printArrayI(a, n);
				printf("\nArray of 1000 elements after Merge Sort:");
				printArrayI(b, n);
				printf("\nArray of 1000 elements after Quick Sort:");
				printArrayI(c, n);
				if(isEqualArray(a, b, n)){
					printf("\nArray A equals Array B after performing Insertion Sort on A and Merge Sort on B\n");
				}
				if(isEqualArray(b, c, n)){
					printf("Array B equals Array C after performing Merge Sort on B and Quick Sort on C\n");
				}
				printf("\nWe will assume our sorting algorithms worked properly for the remaining arrays of 2000, 3000, 4000, ..., 20000 elements\n\n");
			}
			free(a);
			free(b);
			free(c);
		}
	}
	//average insertionsort time for each array size n
        for(j = 0; j <= rtCount; j++){
        	insertionSortRunTimes[j] = insertionSortRunTimes[j]/10;
		mergeSortRunTimes[j] = mergeSortRunTimes[j]/10;
		quickSortRunTimes[j] = quickSortRunTimes[j]/10;
       	}

	printf("\nInsertion Sort Run Time (ms) for arrays with 1000 | 2000 | 3000 | ... | 20000 elements:\n");
	printArrayD(insertionSortRunTimes, rtCount);
	printf("\nMerge Sort Run Time (ms) for arrays with 1000 | 2000 | 3000| ... | 20000 elements:\n");
	printArrayD(mergeSortRunTimes, rtCount);
	printf("\nQuick Sort Run Times (ms) for arrays with 1000 | 2000 | 3000 | ... | 20000 elements:\n");
	printArrayD(quickSortRunTimes, rtCount);
}




//allocate random array of given length and range
//return pointer to array
int * generateArray(int length, int range){
	int *a = malloc(length * sizeof(int));
	int i;
	for(i = 0; i < length; i++){
		a[i] = rand() % range;
	}
	return a;
}

//create copy of array a and return pointer to copy
int * copyArray(int a[], int length){
	int *b = malloc(length* sizeof(int));
	int i;
	for(i = 0; i < length; i++){
		b[i] = a[i];
	}
	return b;
}

//print array of integers
void printArrayI(int a[], int length){
	int i;
	for(i = 0; i < length; i++){
		if(i%10 == 0){ 
			printf("\n");
		}
		printf("%4d|", a[i]); 
	}
	printf("\n");
}

//print array of doubles
void printArrayD(double a[], int length){
	int i;
	for(i = 0; i < length; i++){
		printf("%f |", a[i]);
	}
	printf("\n");
}

//print array of floats
void printArrayF(float a[], int length){
	int i;
	for(i = 0; i < length; i++){
		printf("%f |", a[i]);
	}
	printf("\n");
}

//clear array by assigning every element value 0
void clearArrayD(double a[], int length){
	int i;
	for(i = 0; i < length; i++){
		a[i] = 0;
	}
}

//compare array A and array B and return 1 if they are equal, return 0 if they are not 
int isEqualArray(int a[], int b[], int length){
	int i;
	for(i = 0; i < length; i++){
		if(a[i] != b[i]){
			return 0;
		}
	}
	return 1;
}

//Applies insertion sort to array a and returns total milliseconds elapsed
double insertionSort(int a[], int length){
	struct timeval begin, end;
	gettimeofday(&begin, NULL);

        int j, i;
        int key;
        for(j = 1; j < length; j++){
                key = a[j];
                i = j-1;
                while(i >= 0 && a[i] > key){
                        a[i+1] = a[i];
                        i--;
                }
                a[i+1] = key;
        }
	gettimeofday(&end, NULL);
	//calculate elapsed time in milliseconds
	double elapsed = (end.tv_sec - begin.tv_sec)*1000 +
		((end.tv_usec - begin.tv_usec)/1000.0);
	return elapsed;
}

//startmergesort wraps mergesort algorithm with timer to calculate run time of mergesort
double startMergeSort(int a[], int p, int r){
	struct timeval begin, end;
	gettimeofday(&begin, NULL);
	//perform mergeSort
	mergeSort(a, p, r);
	gettimeofday(&end, NULL);
	double elapsed = (end.tv_sec - begin.tv_sec)*1000 +
		((end.tv_usec - begin.tv_usec)/1000.0);
	return elapsed;
}

//sort array a using mergesort algorithm
void mergeSort(int a[], int p, int r){
	if(p < r){
		int q = floor((p+r)/2);
		mergeSort(a, p, q);
		mergeSort(a, q+1, r);
		merge(a, p, q, r);
	}
}

//merge algorithm, function of mergesort
void merge(int a[], int p, int q, int r){
	int n1 = q - p;
	int n2 = r - q -1;
	int left[n1+1];
	int right[n2+1];
	int i, j, k;
	for(i = 0; i <= n1; i++){
		left[i] = a[p+i];
	}
	for(j = 0; j <= n2; j++){
		right[j] = a[q+1+j];
	}
	left[n1 + 1] = 99999;
	right[n2 + 1] = 99999;
	i = 0; j = 0;
	for(k = p; k <= r; k++){
		if(left[i] <= right[j]){
			a[k] = left[i];
			i++;
		}
		else{
			a[k] = right[j];
			j++;
		}
	}
}

//quicksort algorithm wrapper that calculates time to process quicksort algorithm 
//returns total milliseconds to process quicksort
double startQuickSort(int a[], int p, int r){
	struct timeval begin, end;
        gettimeofday(&begin, NULL);
        //perform quicksort
        quickSort(a, p, r);
        gettimeofday(&end, NULL);
        double elapsed = (end.tv_sec - begin.tv_sec)*1000 +
                ((end.tv_usec - begin.tv_usec)/1000.0);
        return elapsed;
}
//performs quicksort algorithm on array A
void quickSort(int a[], int p, int r){
	if(p < r){
		int q = partition(a, p, r);
		quickSort(a, p, q-1);
		quickSort(a, q+1, r);
	}
}

//function of quicksort algorithm
int partition(int a[], int p, int r){
	int x = a[r];
	int i = p - 1;
	int j;
	for(j = p; j < r; j++){
		if(a[j] <= x){		//if a[j] <= x, swap a[i] and a[j]
			i++;
			int temp = a[j];
			a[j] = a[i];
			a[i] = temp;
		}
	}
	i++;
	int temp = a[r];
	a[r] = a[i];
	a[i] = temp;
	return i;
}
