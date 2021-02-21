//
// Created by Aleksandar Kostic on 2019-10-28 for Western University's 3305 class.
// This program shows how the behaviour of processes and threads differ.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Global variables (x, y, z)
int x = 10;
int y = 20;
int z = 0;

void *xyaddition() {

    z = x + y;
    pthread_exit(NULL);

}

int main() {

    pid_t pid1;
    pthread_t thread1;
    int status;

    //
    // SECTION 1: Handles the process section of the assignment
    //
    pid1 = fork();

    // Handles error when child was not successfully created
    if (pid1 < 0) {

        perror("Error creating a child");
        exit(1);

    }

    // Deals with the parent process
    if (pid1 > 1) {

        wait(NULL);
        printf("FROM PARENT IN PROCESSES | The value of z is: %d \n", z);

        //
        // SECTION 2: Handles the thread section of the assignment
        //
        status = pthread_create(&thread1, NULL, xyaddition, NULL); // Child thread processes z = x + y
        if (status != 0) {

            perror("Error creating the child thread");
            exit(1);

        }

        pthread_join(thread1, NULL); // Parent waits until child thread is complete before executing further
        printf("FROM PARENT IN THREADS | The value of z is: %d \n", z);

    }

    // Deals with the child process
    if (pid1 == 0) {

        z = x + y;

    }

    return 0;

}
