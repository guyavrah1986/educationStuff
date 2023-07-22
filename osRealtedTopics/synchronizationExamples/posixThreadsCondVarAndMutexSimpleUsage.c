#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

// global variables
pthread_mutex_t lock;
pthread_cond_t cond;
int ready;

void* waitingThread(void* arg)
{
	printf("%s thread - start \n", (char *)arg);

	
	pthread_mutex_lock(&lock);
	while (ready == 0)
		pthread_cond_wait(&cond, &lock);
	printf("--- %s thread - done waiting for ready object --- \n", (char *)arg);
	pthread_mutex_unlock(&lock);
	
	printf("%s thread - end \n", (char *)arg);
	return NULL;
}

void* wakingUpThread(void* arg)
{
	printf("%s thread - start \n", (char *)arg);
	pthread_mutex_lock(&lock);
	ready = 1;
	sleep(5);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
	printf("%s thread - end \n", (char *)arg);
	return NULL;
}

void init()
{
	int res = pthread_mutex_init(&lock, NULL);
	assert(res == 0);
	res = pthread_cond_init(&cond, NULL);
	assert(res == 0);
	ready = 0;
	printf("init - successfully initialized mutex, condition variables and flag objects \n");
}

void clean()
{
	int res = pthread_mutex_destroy(&lock);
	assert(res == 0);
	res = pthread_cond_destroy(&cond);
	assert(res == 0);
	printf("init - successfully destroyed mutex and condition variables objects \n");
}

int main(int argc, char* argv[])
{
	pthread_t p1, p2;
	int rc;
	printf("main - begin\n");
	init();

	
	rc = pthread_create(&p1, NULL, waitingThread, "waitingThread");
	assert(rc == 0);
	sleep(1);
	rc = pthread_create(&p2, NULL, wakingUpThread, "wakingUpThread");
	assert(rc == 0);

	

	// join waits for the threads to finish
	rc = pthread_join(p1, NULL);
	assert(rc == 0);
	rc = pthread_join(p2, NULL);
	assert(rc == 0);



	printf("main - end\n");
	return 0;
}
