#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

void *msg(void *count)
{
    long countt = (long)count;
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&lock);
        *(countt++);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    long count = 0;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, msg, &count);
    pthread_create(&t2, NULL, msg, &count);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Count = %li\n", count);;

    pthread_mutex_destroy(&lock);
    return 0;
}
