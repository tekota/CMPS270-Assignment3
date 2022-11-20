#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>

int totalCount = 0; //global variable to be used in threads.

int *array;
int length;
int numThreads;

/*
Required: Global variables
Effects: Counts the number of 1's in the array
         by dividing the array into a certain amount of parts which are the threads
*/
void *ThreadsFunction(void *vargp)
{
    int *myid = (int *)vargp;
    int i;
    int start = (*myid)%numThreads * (length / numThreads);
    int end = start + (length / numThreads);
    int count = 0;
    for (i = start; i < end; i++)
    {
        if (array[i] == 1)
            count++;
    }
    totalCount += count;
    printf("\nThread %d: %d 1s counted\n", *myid, count);

}

//TESTER FUNCTIONS FOR THE PROGRAM
/*
This program works for any length of array and any number of threads
*/
int main()
{
    clock_t start_t = clock(); //start time

    printf("Enter the length of the array: ");
    scanf("%d", &length);
    array = (int *)malloc(length * sizeof(int));


    for (int i = 0; i < length; i++)
    {
        array[i] = rand() % 5;
    }



    printf("Enter the number of threads: ");
    scanf("%d", &numThreads);
    pthread_t tid[numThreads]; // Thread ID
    int thread[numThreads]; // Thread number


    for (int i = 0; i < numThreads; i++) 
        {
            thread[i] = i;
            pthread_create(&tid[i], NULL, ThreadsFunction, (void *)&thread[i]);
        }

    for (int i = 0; i < numThreads; i++)
        {
            pthread_join(tid[i], NULL);
        }
    printf("\nFor an array of length %d and %d created threads\n", length, numThreads);
    printf("\nTotal number of 1s: %d\n", totalCount); 

    clock_t end_t = clock(); //end time

    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC; //total time
    printf("\nTotal time taken by CPU: %f\n", total_t  );
    return 0;
}
