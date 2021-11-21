#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100

int array[SIZE];
int threadMax = 2;
int part = 0;


void fillArrayWithRandomNumbers(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) array[i] = rand()%100;
}

void printArray(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) printf("%5d", arr[i]);
    printf("\n");
}

typedef struct StartEndIndexes {
    int start;
    int end;
} StartEndIndexes;

//Merge sort algorithm cited form geeksforgeeks.com
void merge(int low, int mid, int high){

    int n1 = mid - low+1;
    int n2 = high - mid;
 
    int l[n1];
    int r[n2];
  
    for(int i = 0; i < n1; i++){
      l[i] = array[i + low];
    }
  
    for(int i = 0; i < n2; i++){
      r[i]  = array[i + mid + 1];
    }
    
    int lowtemp = low, j = 0, x = 0;
    
    while(j < n1 && x < n2) {
      if(l[j] <= r[x]){
        array[lowtemp++] = l[j++];
      }else {
        array[lowtemp++] = r[x++];
      }
    }
  
    while(j < n1){
      array[lowtemp++] = l[j++];
    }
  
    while(x < n2){
      array[lowtemp++] = r[x++];
    }
}

void merge_Sort(int low, int high){
    int mid = low + (high -low)/2;
    
    if (low < high){
      merge_Sort(low, mid);
      merge_Sort(mid +1, high);
      merge(low, mid, high);
    }
}

// Runs mergesort on the array segment described in the
// argument. Spawns two threads to mergesort each half
// of the array segment, and then merges the results.
void* mergeSort(void* args) {
    int threadPart = part++;
    
    int low = threadPart * (SIZE/threadMax);
    int high = (threadPart + 1) * (SIZE/threadMax) - 1;
    
    int mid = low + (high -low)/2;
    
    if (low < high){
      merge_Sort(low, mid);
      merge_Sort(mid +1, high);
      merge(low, mid, high);
    }    
}

int main() {
    srand(time(0));
    StartEndIndexes sei;
    sei.start = 0;
    sei.end = SIZE - 1;
    
    // 1. Fill array with random numbers.
    fillArrayWithRandomNumbers(array);
    
    // 2. Print the array.
    printf("Unsorted array: ");
    printArray(array);
    
    // 3. Create a 2 threads for merge sort.
    pthread_t threads[threadMax];
     
    for(int i = 0; i < threadMax; i++){
      pthread_create(&threads[i], NULL, mergeSort, (void*)NULL);
    }
  
    for(int i =0; i < threadMax; i++){
      pthread_join(threads[i], NULL);
    }
    
    // 4. Wait for mergesort to finish.
    merge(0, (SIZE/2 - 1)/2, SIZE/2 - 1);
    merge(SIZE/2 + 1, SIZE/2 + (SIZE-1-SIZE/2)/2, SIZE-1);
    // 5. Print the sorted array.
    printf("Sorted array:   ");
    printArray(array);
}
