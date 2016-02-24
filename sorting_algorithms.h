//Justin Johnson , Z23136514
//Header File Contains Function Declarations For
//Insertion Sort, Merge Sort, and Quick Sort Algorithms and
//General Array Operations
#ifndef SORTING_ALG_HEADER
#define SORTING_ALG_HEADER

#define N_START 1000	//minimum array size to be sorted
#define N_FINISH 20000	//maximum array size to be sorted
#define DELTA 1000	//value to increment array size when testing various array sizes Run Times
#define RANGE 1000	//maximum value of array elements when producing random elements

//array functionality
int * generateArray(int, int);
void printArrayI(int [], int);
void printArrayD(double [], int);
void printArrayF(float [], int);
void clearArrayD(double [], int);
int * copyArray(int [], int);
int isEqualArray(int [], int [], int);

//insertion sort
double insertionSort(int [], int);

//merge sort
double startMergeSort(int [], int, int);
void mergeSort(int [], int, int);
void merge(int [], int, int, int);

//quick sort
double startQuickSort(int [], int, int);
void quickSort(int [], int, int);
int partition(int [], int, int);

#endif
