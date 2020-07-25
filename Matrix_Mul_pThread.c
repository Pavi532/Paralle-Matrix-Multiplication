#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <assert.h>
#include <pthread.h>

#define RANDLIMIT 5 /* Magnitude limit of generated randno.*/
#define N 1000 /* Matrix Size*/
#define THREADS 4 /* Number of Threads */
#define NUMLIMIT 70.0

void *slave (void *myid);

/*Matrices*/
float a[N][N]; //Matrix A
float b[N][N]; //Matrix B
float c[N][N]; //Matrix C to store resulting matrix

void *slave( void *myid ){
    int x, low, high;
    /*Calculate which rows to calculate by each Thread*/
    if (N >= THREADS) {
        //When the matrix has more rows than the number of threads
        x = N/THREADS;
        low = (int) myid * x;
        high = low + x;
    }
    else{
        x = 1;
        low = (int) myid;
        if (low >= N){
            //there is nothing to calculate for the extra threads
            high = low;
        }
        else {
            high = low +1; //each thread will be calculating only one row
        }
    }
    //Multiplying A and B matrices and storing results in C
    int i, j, k;
    for (i=low; i<high; i++) {
        for (j=0; j<N; j++) {
            c[i][j] = 0.0;
            for (k=0; k<N; k++){
                c[i][j] = c[i][j] + a[i][k]*b[k][j];
            }
        }
    }
}

int main(){

    struct timeval start, stop;
    int i,j;
    pthread_t tid[THREADS];

    /* generate mxs randomly */
    printf("Matrix Size\t  :%d\n",N);
    printf("Used Method\t  :PTHREAD\n");
    printf("Number of Threads :%d\n",THREADS);
    for (i=0; i<N; i++){
        for (j=0; j<N; j++) {
            a[i][j] = 1+(int) (NUMLIMIT*rand()/(RAND_MAX+1.0));
            b[i][j] = (double) (rand() % RANDLIMIT);
        }
    }

    gettimeofday(&start, 0);

    /*Create Threads*/
    for ( i=0; i<THREADS ; i++){
        if (pthread_create( &tid[i], NULL, slave, (void *) i) != 0){
            perror ("Pthread create fails");
        }
    }

    /*Join Threads*/
    for ( i=0; i<THREADS ; i++){
        if (pthread_join( tid[i], NULL) != 0 ){
            perror ("Pthread join fails");
        }
    }

    /*End Timing*/
    gettimeofday(&stop, 0);

    /*Print the timing details*/
    printf("Time to Multiply  :%.6f Seconds\n",(stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));
    return(0);
}