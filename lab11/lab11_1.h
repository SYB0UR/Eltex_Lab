#ifndef FUNC_H
    #define FUNC_H

    #include <stdio.h>
    #include <pthread.h>

    #define NUM_THREADS 5

    void* print_index(void* arg);
#endif
