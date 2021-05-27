//
// command
//      gcc avgtime.c -o avg -lm -lpthread
// run
//      ./avg

// You can change the number of threads inside main function where thread_count is called.

// The avg time taken to create and terminate threads decreases as the number of threads are increased.
// The average time decrases probably because as the number of threads are increased there are more threads
// runnning simultaneously which decrease the overall time taken.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void* thread_func();

int main(int argc, char* argv[]) {
    int i;
    long thread_count = 10;
    pthread_t* thread_handles;
    
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
    clock_t begin = clock();
    for (i = 0; i < thread_count; i++){
        pthread_create(&thread_handles[i], NULL, thread_func, NULL);
    }
    for (i = 0; i < thread_count; i++){
        pthread_join(thread_handles[i], NULL);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total Time: %f\n", time_spent);
    printf("Time per thread: %f\n", (time_spent/thread_count));
    free(thread_handles);
    return 0;
}

void* thread_func(){
    pthread_exit(0);
}