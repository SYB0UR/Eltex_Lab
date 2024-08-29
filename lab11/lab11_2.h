#ifndef FUNC_H
    #define FUNC_H

    #include <stdio.h>
    #include <pthread.h>

    #define NUM_THREADS 5
    #define NUM_ITERATIONS 1000000

    extern int counter;
    extern pthread_mutex_t mutex;

    void* increment();

#endif
