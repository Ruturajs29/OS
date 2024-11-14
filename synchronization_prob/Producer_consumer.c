#include <stdio.h> //PROD CONSUMER
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;

// Number of items each producer and consumer will handle
#define PROCESS_COUNT 5

void *producer(void *arg) {
    int i;
    for (i = 0; i < PROCESS_COUNT; i++) {
        pthread_mutex_lock(&mutex);
        // Wait if the buffer is full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_producer, &mutex);
        }
        
        // Produce an item and add it to the buffer
        buffer[count++] = i;
        printf("Produced: %d\n", i);
        
        // Signal the consumer that an item is available
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
        
        sleep(1); 
    }
    return NULL;
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < PROCESS_COUNT; i++) {
        pthread_mutex_lock(&mutex);
        
        // Wait if the buffer is empty
        while (count == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        
        // Consume an item from the buffer
        int item = buffer[--count];
        printf("Consumed: %d\n", item);
        
        // Signal the producer that space is available
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);
        
        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);
    
    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    
    // Wait for both threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    
    // Destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);
    
    return 0;
}
