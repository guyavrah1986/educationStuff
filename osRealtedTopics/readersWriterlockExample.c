// =================================================================================================================================
// =================================================================================================================================
//
//
//
// =================================================================================================================================
// =================================================================================================================================
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

typedef void* (*funcPointer)(void*);

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond_readers;
    pthread_cond_t cond_writers;
    unsigned int readers;
    unsigned int writers;
}rw_lock;

void rw_lock_init(rw_lock *lock)
{
    lock->readers = 0;
    lock->writers = 0;
    pthread_mutex_init(&lock->mutex, NULL);
    pthread_cond_init(&lock->cond_readers, NULL);
    pthread_cond_init(&lock->cond_writers, NULL);
}

void rw_lock_acquire_read(rw_lock *lock)
{
    pthread_mutex_lock(&lock->mutex);
    while (lock->writers > 0)
    {
        pthread_cond_wait(&lock->cond_readers, &lock->mutex);
    }
    lock->readers++;
    pthread_mutex_unlock(&lock->mutex);
}

void rw_lock_release_read(rw_lock *lock)
{
    pthread_mutex_lock(&lock->mutex);
    lock->readers--;
    if (lock->readers == 0)
    {
        pthread_cond_broadcast(&lock->cond_writers);
    }
    pthread_mutex_unlock(&lock->mutex);
}

void rw_lock_acquire_write(rw_lock *lock)
{
    pthread_mutex_lock(&lock->mutex);
    while (lock->readers > 0 || lock->writers > 0)
    {
        pthread_cond_wait(&lock->cond_writers, &lock->mutex);
    }
    lock->writers++;
    pthread_mutex_unlock(&lock->mutex);
}

void rw_lock_release_write(rw_lock *lock) 
{
    pthread_mutex_lock(&lock->mutex);
    lock->writers--;
    pthread_cond_broadcast(&lock->cond_writers);
    pthread_cond_broadcast(&lock->cond_readers);
    pthread_mutex_unlock(&lock->mutex);
}

void rw_lock_destroy(rw_lock *lock)
{
    pthread_mutex_destroy(&lock->mutex);
    pthread_cond_destroy(&lock->cond_readers);
    pthread_cond_destroy(&lock->cond_writers);
}

void* reader_thread_func(void* arg)
{
	int intArg = *(int*)arg;
	printf("reader_thread_func - got an int value of:%d\n", intArg);
	pid_t threadId = syscall(__NR_gettid); // 4)
	printf("thread1_func - the thread ID is:%d\n", threadId);
	*(int*)arg = 0;
 	pthread_exit(arg);
}

void* writer_thread_func(void* arg)
{
	int intArg = *(int*)arg;
	printf("writer_thread_func - got an int value of:%d\n", intArg);
	pid_t threadId = syscall(__NR_gettid);
	printf("thread2_func - the thread ID is:%d\n", threadId);
	printf("thread2_func - terminating thread\n");
	return NULL;
}

int main()
{
	printf("main - start\n");
	readersWritersInit();
	printf("main - end\n");
}
