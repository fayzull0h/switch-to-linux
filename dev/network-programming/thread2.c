#include "common.h"
#include <pthread.h>

void * thread_main(void * param) {
    int var = *((int *)param);
    char * msg = malloc(sizeof(char) * 50);
    sprintf(msg, "Input: %d\nOutput: %d\n", var, var * 2);
    return (void *)msg;
}

int main() {
    pthread_t pid;
    int thread_param = 5;
    void * thread_ret;

    if (pthread_create(&pid, NULL, thread_main, (void *)&thread_param) != 0) {
        printf("pthread_create() error!\n");
        return -1;
    }

    if (pthread_join(pid, &thread_ret) != 0) {
        printf("pthread_join() error!\n");
        return -1;
    }

    printf((char *)thread_ret);
    free(thread_ret);
    return 0;
}