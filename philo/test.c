
#include "philo.h"

// void *exec_function(void *var)
// {
//     int num = *((int*)var);
//     printf("%d\n", num);
//     return(NULL);
// }

// int main()
// {
//     pthread_t thread;
//     pthread_mutex_t mutex;
//     int var = 5;

//     pthread_create(&thread, NULL, &exec_function, (void*)&var);
//     // usleep(50)

//     if (pthread_mutex_init(&mutex, NULL) != 0) {
//         perror("Mutex initialization failed");
//         exit(EXIT_FAILURE);
//     }
//     pthread_mutex_lock(&mutex);

//     // Critical section code
//     printf("In critical section\n");

//     pthread_mutex_unlock(&mutex);


//     //pthread_join(thread, NULL);


// }

pthread_mutex_t mutex;
int shared_resource = 0;

void *thread_function(void *arg) {
    pthread_mutex_lock(&mutex);
    // Critical section
    shared_resource++;
    long timestamp = 60;
    int philo_id = 3;
    timestamp = time_now();
    printf("%ld %d has taken a fork\n", timestamp, philo_id);
    // printf("Shared resource incremented by thread %ld, value: %d\n", (long)arg, shared_resource);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[5];

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        return EXIT_FAILURE;
    }

    // Create threads
    for (long i = 0; i < 5; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, (void *)i) != 0) {
            perror("Thread creation failed");
            pthread_mutex_destroy(&mutex);
            return EXIT_FAILURE;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < 5; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Thread join failed");
            pthread_mutex_destroy(&mutex);
            return EXIT_FAILURE;
        }
    }
    printf("final result is : %d \n", shared_resource);
    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}

