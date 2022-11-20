#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>


int good = 0;
int *array;
int length;
int numThreads;



// cache structure storing the values of the threads
struct cache {
    int count;
    char dummy[64-sizeof(int)];
};
struct cache totalCount;


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
    int start = (*myid)%numThreads * (length / numThreads);
    int end = start + (length / numThreads);
    for (i = start; i < end; i++)
    {
        if (array[i] == 1)
            totalCount.count++;
    }
    printf("\nThread %d: %d 1s counted\n", *myid, totalCount.count);

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

    clock_t start_t, end_t;
    double total_t;
    length = 1000000;
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

    start_t = clock();
    for (int s = 0; s < 100; s++){
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
    printf("\nTotal number of 1s: %d\n", totalCount.count); 
 

    if (totalCount.count == 500000)
        good++;
    
    totalCount.count = 0;
    } 
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t  );
    printf("Good answers: %d\n", good);
    return 0;
}

