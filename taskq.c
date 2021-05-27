//
// command
//      gcc taskq.c -o task -lm -lpthread
// run
//      ./task
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_func();

struct Mylist { 
    int data; 
    struct Mylist* next; 
}; 

struct Mylist* head;
pthread_mutex_t mutex;
pthread_cond_t proceed;
int taskdone = 0;
int taskstodo;
int task;

void printlist() { 
    struct Mylist *temp = head;
    printf("\n\nList elements are - \n");
    while(temp != NULL)
    {
        printf("%d ---> ",temp->data);
        temp = temp->next;
    }
}

int Member(int value) { 
    struct Mylist* curr_p = head;
    while (curr_p != NULL && curr_p->data < value) {
        curr_p = curr_p->next;
    }
    if (curr_p == NULL || curr_p->data > value) { 
        return 0;
    }
    else { 
        return 1;
    }
}


int Insertlist(int value) {
    struct Mylist* curr_p = head;
    struct Mylist* pred_p = NULL;
    struct Mylist* temp_p;
    
    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if (curr_p == NULL || curr_p->data > value) { 
        temp_p = malloc(sizeof(struct Mylist)); 
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL){
            head = temp_p;
        }    
        else{
            pred_p->next = temp_p; 
        }
        return 1;
    } 
    else { 
        return 0;
    }
}




int main(int argc, char* argv[]) {
    int i;
    long thread_count = 10;
    pthread_t* thread_handles;


    
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&proceed, NULL);

    for (i = 0; i < thread_count; i++){
        pthread_create(&thread_handles[i], NULL, thread_func, NULL);
    }

    while (taskdone == 0){
        task = (rand() % 2) + 1; 
        taskstodo = 1;
        taskdone = 1;
    }

    for (i = 0; i < thread_count; i++){
        pthread_join(thread_handles[i], NULL);
    }

    free(thread_handles);
    return 0;
}

void* thread_func(){

    if (taskstodo == 1){
        pthread_cond_signal(&proceed);
        if (task == 1){
            member(4);
        }
        if (task == 2){
            Insertlist(3);
        }
    }
    else{
        while(pthread_cond_wait(&proceed, &mutex) != 0);
    }
    if (taskdone == 1){
        pthread_cond_broadcast(&proceed);
    }

    pthread_exit(0);
}


