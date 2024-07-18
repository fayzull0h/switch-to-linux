#include "common.h"
#include <pthread.h>

void * thread_main(void * arg) {
    int count = *((int *)arg);
    for (int i = 0; i < count; i++) {
        puts("thread action");
        sleep(1);
    }
}

int main(int argc, char * argv[]) {
    pthread_t pid;
    int thread_param = 5;

    if (pthread_create(&pid, NULL, thread_main, (void *)&thread_param) != 0) {
        printf("pthread_create() error!\n");
        exit(1);
    }

    for (int i = 0; i < thread_param; i++) {
        puts("main action");
        sleep(1);
    }
    
    sleep(2);
    puts("end of main");
    return 0;
}