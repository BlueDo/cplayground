#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_SUB_JOBS 4
#define NUM_THREADS 3

pthread_mutex_t locks[NUM_SUB_JOBS];

void* job(void* arg) {
    for (int i = 0; i < NUM_SUB_JOBS; i++) {
        pthread_mutex_lock(&locks[i]);
        sleep(1);
        pthread_mutex_unlock(&locks[i]);
        printf("Thread %d Subjob %d has finished\n", *(int *)arg, i);
    }
}

int main(int argc, char** argv) {
    int i = 0;
    int error;
    pthread_t threads[NUM_THREADS];
    int thread_number[NUM_THREADS];
    for (int i = 0; i < NUM_SUB_JOBS; i++) {
        if (pthread_mutex_init(&locks[i], NULL) != 0) {
            fprintf(stderr, "Mutex init has failed\n");
            return 1;
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_number[i] = i;
        error = pthread_create(&(threads[i]), NULL, &job, &thread_number[i]);
        if (error != 0) {
            printf("Thread can't be created :[%s]\n", strerror(error));
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_SUB_JOBS; i++) {
        pthread_mutex_destroy(&locks[i]);
    }
    return 0;
}
