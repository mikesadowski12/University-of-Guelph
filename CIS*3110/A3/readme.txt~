------IMPORTANT-------------
1. If bad data is inputted on the command line, program will probably crash, no error checking at all.
2. FCFS sort of works, not sure exactly how it was intended to be implemented, but it does something similar to it.
3. Round Robin was not implemented correctly at all.
4. Processes do not actually run, not sure how it was suppsoed to work exactly but I just added up CPU and I/O burst times, etc, to create the "simulation".
--------------------------------------------------------------
My solution first parses the input file and stores all of the process in a linked list, that contains it's process ID, total threads,
and an array of threads. The thread struct contains the thread arrival time, number of cpu, and an array containing io times, and cpu burst times. This linked list will now act as the "queue" for the simulator.

Next, using the head of the linked list, the first process is popped off the queue, and the threads are simulated by adding the total time for the cpu bursts, and the io bursts into a global variable. This happens for every thread in each process. Once finished, the appropriate print messages are printed according to the flags. The overhead for switching a process state is 7 time units, because thats what was shown in one of the examples for the output in the assignment outline.

