/*
 * This program was was made by Aleksandar Kostic on 23 September 2019 for Western University's 3305 course
 * This program reads two values as command line arguments; parent reads X, child reads Y.
 * Pipe is used for communication between the processes - child writes to pipe, parent reads from pipe to obtain value.
 * Parent then adds the two values and pints the summed value.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    pid_t pid, parentId, childId;
    int fd[2], pipeStatus;

    if (argc != 3) {

        perror("Invalid number of command line arguments");
        exit(0);

    }

    // This section deals with the creation of the pipe
    pipeStatus = pipe(fd);

    if (pipeStatus < 0) {

        perror("Pipe was not successfully created");
        exit(0);

    }

    else { // pipe creation successful

        parentId = getpid();
        printf("A pipe is created for communication between parent (PID %d) and child\n", parentId);

    }

    // This section deals with the processes
    pid = fork();

    if (pid < 0) {

        perror("Child process was not successfully created");
        exit(0);

    }

    /*
     * This section deals with the parent process
     * FIRST: read the first integer and wait for child process to finish
     * SECOND: after child process finishes, read from pipe what child wrote and add them
     */
    if (pid > 0) {

        printf("Parent (PID %d) created a child (PID %d)\n", parentId, pid);

        int firstIntegerX = atoi(argv[1]);
        printf("Parent (PID %d) reading X = %d from the user\n", parentId, firstIntegerX);

        wait(NULL);

        char readValue[10];
        read(fd[0], readValue, 10);

        int readValueY = atoi(readValue);
        printf("Parent (PID %d) reading Y from the pipe (Y = %d)\n", parentId, readValueY);

        int finalValueAddition = firstIntegerX + readValueY;
        printf("Parent (PID %d) adding X + Y = %d\n", parentId, finalValueAddition);

    }

    // This section deals with the child process; reads command line and writes to pipe
    if (pid == 0) {

        childId = getpid();

        char* secondIntegerY = argv[2];
        printf("Child (PID %d) reading Y = %s from the user\n", childId, secondIntegerY);

        printf("Child (PID %d) writing Y into the pipe\n", childId);
        write(fd[1], secondIntegerY, strlen(secondIntegerY));

    }

    return 0;

}