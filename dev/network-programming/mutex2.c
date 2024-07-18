#include "common.h"
#include <pthread.h>
#define NUM_THREADS 10
#define BIGNUM 5000000

pthread_mutex_t mutex;

void * thread_inc(void * sum) {
    int * num = (int *)sum;
    for (int i = 0; i < BIGNUM; i++) {
        if (pthread_mutex_lock(&mutex)) exit(1);
        *num += 1;
        if (pthread_mutex_unlock(&mutex)) exit(1);
    }
    return NULL;
}

void * thread_dec(void * sum) {
    int * num = (int *)sum;
    for (int i = 0; i < BIGNUM; i++) {
        if (pthread_mutex_lock(&mutex)) exit(1);
        *num -= 1;
        if (pthread_mutex_unlock(&mutex)) exit(1);
    }
    return NULL;
}

int main(int argc, char * argv[]) {
    long long sum = 0;
    pthread_t pids[NUM_THREADS];
    void * status;

    if (pthread_mutex_init(&mutex, NULL)) {
        printf("Mutex initiation\n");
        return 1;
    }

    printf("size of long long: %d\n", sizeof(long long));

    for (int i = 0; i < NUM_THREADS; i++) {
        if (i % 2 == 0)
            pthread_create(&pids[i], NULL, thread_inc, (void *)&sum);
        else
            pthread_create(&pids[i], NULL, thread_dec, (void *)&sum);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(pids[i], &status);
    
    printf("sum: %d\n", sum);

    if (pthread_mutex_destroy(&mutex)) {
        printf("Could not destroy\n");
        return 1;
    }

    return 0;
}