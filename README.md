# Processes
 C implementation of processes using both fork and threads.

part1

- This program communicates between parent and child processes. 
- Processes are created using fork().
- Proper timing between messages is enforced using wait().

part2

- This program communicates between parent and child processes using the pipe. Processes are created using fork().
- This program reads two values as command line arguments; parent reads X, child reads Y.
- Child writes to pipe, parent reads from pipe to obtain value.
- Parent then adds the two values and prints the summed value.

part3

- This program shows how the behaviour of processes and threads differ.