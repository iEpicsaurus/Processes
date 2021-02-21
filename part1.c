/*
 * This program was was made by Aleksandar Kostic on 23 September 2019 for Western University's 3305 course.
 * This program is used for communication between processes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid, pid2, pid3;
    int status;

    pid = fork(); // used to created the first child

    if (pid < 0) {

        perror("Child_1 was not successfully created");
        exit(0);

    }

    // CURRENTLY IN PARENT: this deals with the second child scenario, avoids first child.
    if (pid > 0) {

        pid_t parentId = getpid();
        wait(NULL);

        pid2 = fork(); // deals with creation of child_2

        if (pid2 < 0) {

            perror("Child_2 was not successfully created");
            exit(0);

        }

        //this deals with the child_2 process; ensures parent does transfer control to external program
        if (pid2 == 0) {

            pid_t child2Id = getpid();

            printf("Parent (PID %d) created child_2 (PID %d)\n", parentId, child2Id);
            printf("Child_2 (PID %d) is calling external program external_program.out & leaving child_2\n", child2Id);
            status = execl("external_program.out", "external_program.out", NULL);

            if (status < 0) {

                perror("Error with execl(...) system call");
                exit(0);

            }

        }

        return 0; // after parent executes, return to exit program.

    }

    // IN CHILD_1 AFTER FIRST FORK: this deals with the first child scenario ONLY
    if (pid == 0) {

        pid_t parentId = getppid();
        pid_t child1Id = getpid();
        printf("Parent process (PID %d) created child_1 (PID %d)\n", parentId, child1Id);
        printf("Parent process (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", parentId, child1Id);

        pid3 = fork(); // creates child_1.1

        if (pid3 < 0) {

            perror("Child_1.1 has not been created successfully\n");
            exit(0);

        }

        //deals with child_1 process ending; ensures child_1.1 does nothing
        if (pid3 > 0) {

            wait(NULL); // after child_1.1 terminates, return control to child_1
            printf("Child_1 (PID %d) is now completed\n", child1Id);

        }

        if (pid3 == 0) { // CURRENTLY IN CHILD_1.1

            pid_t child1bId = getpid();
            printf("Child_1 (PID %d) created child_1.1 (PID %d)\n", child1Id, child1bId);

        }

    }

    return 0;

}