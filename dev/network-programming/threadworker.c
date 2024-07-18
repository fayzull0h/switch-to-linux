#include "common.h"
#include <pthread.h>

int sum = 0;

void * thread_summation(void * range) {
    int start = ((int *)range)[0];
    int end = ((int *)range)[1];
    for (int i = start; i <= end; i++) {
        sum+=i;
    }
    return NULL;
}

int main(int argc, char * argv[]) {
    pthread_t t1, t2;
    int range1[] = {1, 5};
    int range2[] = {6, 10};
    void * status;

    pthread_create(&t1, NULL, thread_summation, (void *)range1);
    pthread_create(&t2, NULL, thread_summation, (void *)range2);

    pthread_join(t1, &status);
    pthread_join(t2, &status);

    printf("sum: %d\n", sum);
    return 0;
}