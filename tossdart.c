//
// command
//      gcc tossdart.c -o toss -lm -lpthread
// run
//      ./toss


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

long thread_count = 5;
long long num_circle;
long long toss_count;
pthread_mutex_t mutex;

void *Thread_sum(void *point);

double random_double()
{
    return random() / ((double)RAND_MAX + 1);
}

int main(int argc, char* argv[]) {
    int i;
    pthread_t* thread_handles;
    double Pi = 0;
    
    toss_count = strtol(argv[1], NULL, 10);
    long long point_per_thread = toss_count/thread_count;
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);

    srandom((unsigned)time(NULL));

    for (i = 0; i < thread_count; i++){
        pthread_create(&thread_handles[i], NULL, Thread_sum, &point_per_thread);
    }
    for (i = 0; i < thread_count; i++){
        pthread_join(thread_handles[i], NULL);
    }

    Pi = 4.0 * num_circle / toss_count;
    printf("Number of Points: %lld\n", toss_count);
    printf("Pi Estimate = %f\n", Pi);
    free(thread_handles);
    return 0;
}


void *Thread_sum(void *point){
    long long points = *((long *)point);
    int i;
    int hit_count = 0;
    double x,y;
    
    for (i = 0; i < points; i++) {
        x = random_double() * 2.0 - 1.0;
        y = random_double() * 2.0 - 1.0;
        if ( sqrt(x*x + y*y) <= 1.0 )
            ++hit_count;
    }
    
    pthread_mutex_lock(&mutex);
    num_circle += hit_count;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}