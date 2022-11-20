#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

int totalCount = 0;
int good = 0; // good answers
int *array;
int length;
int numThreads;
pthread_mutex_t lock;
// The function that will be executed by the threads
/*
Required: Global variables
Effects: Counts the number of 1's in the array
         by dividing the array into a certain amount of parts which are the threads
*/
void *ThreadsFunction(void *vargp)
{
    int *myid = (int *)vargp;
    int i;
    int start_t = (*myid)%numThreads * (length / numThreads);
    int end_t = start_t + (length / numThreads);
    int count = 0;
    for (i = start_t; i < end_t; i++)
    {
        if (array[i] == 1)
            count++;
    }
    //mutex lock
    pthread_mutex_lock(&lock);
    totalCount += count;
    //mutex unlock
    pthread_mutex_unlock(&lock);
    
    // printf("\nThread %d: %d 1s counted\n", *myid, count);
}

//TESTER FUNCTIONS FOR THE PROGRAM
/*
Works for any number of threads and any length of array

The global variables are altered.
*/

/*
Report Contd
*/

int main(int argc)
{
     
    printf("Enter the number of threads: ");
    scanf("%d", &numThreads);
    length = 100000000;
    array = (int *)malloc(length * sizeof(int));
    for (int i=0; i< length/16; i++)
        {
            array[i] = 1;
        }
    for (int i=length/16; i<2*length/16; i++)
        {
            array[i] = 0;
        }
    for (int i=2*length/16; i<3*length/16; i++)
        {
            array[i] = 1;
        }
    for (int i=3*length/16; i<4*length/16; i++)
        {
            array[i] = 0;
        }
    for (int i=4*length/16; i<5*length/16; i++)
        {
            array[i] = 1;
        }
    for (int i=5*length/16; i<6*length/16; i++)
        {
            array[i] = 0;
        }
    for (int i=6*length/16; i<7*length/16; i++)
        {
            array[i] = 1;
        }
    for (int i=7*length/16; i<8*length/16; i++)
        {
            array[i] = 0;
        }
    for (int i=8*length/16; i<9*length/16; i++)
        {
            array[i] = 1;
        }
    for (int i=9*length/16; i<10*length/16; i++)
        {
            array[i] = 0;
        }
    for (int i=10*length/16; i<11*length/16; i++)
        {
            array[i] = 1;
        }
    for (int i=11*length/16; i<12*length/16; i++)
        {
            array[i] = 0;
        }
    for (int i=12*length/16; i<13*length/16; i++)
        {
            array[i] = 1;
        }
    for (int i=13*length/16; i<14*length/16; i++)
        {
            array[i] = 0;
        }
    for (int i=14*length/16; i<15*length/16; i++)
        {
            array[i] = 1;
        }
    for (int i=15*length/16; i<16*length/16; i++)
        {
            array[i] = 0;
        }
    
    
    
    pthread_t tid[numThreads]; // Thread ID
    int thread[numThreads]; // Thread number

   clock_t start_t = clock();
    for (int s = 0; s <100; s++){
      
    for (int i = 0; i < numThreads; i++) 
        {
            thread[i] = i;
            pthread_create(&tid[i], NULL, ThreadsFunction, (void *)&thread[i]);
        }

    for (int i = 0; i < numThreads; i++)
        {
            pthread_join(tid[i], NULL);
        }
    // printf("\nFor an array of length %d and %d created threads\n", length, numThreads);
    // printf("\nTotal number of 1s: %d\n", totalCount); 
    
    

    if (totalCount == length/2)
        good++;

    totalCount = 0;    
}
    clock_t end_t = clock();
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC; 
    printf("\nTotal time taken by CPU: %f\n", total_t);
    printf("Good answers: %d\n", good);
    return 0;
}
