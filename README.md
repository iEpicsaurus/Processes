# Fork-Processes
 C implementation of parent and child processes communicating using the pipe.

assignment1_part1

- This program communicates between parent and child processes. 
- Processes are created using fork().
- Proper timing between messages is enforced using wait().

assignment1_part2

- This program communicates between parent and child processes using the pipe. Processes are created using fork().
- This program reads two values as command line arguments; parent reads X, child reads Y.
- Child writes to pipe, parent reads from pipe to obtain value.
- Parent then adds the two values and pints the summed value.