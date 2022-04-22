An uninteded way to do the 42 project: pipex.

We use the execve function to create a file, write the arguments in it (with the pipe), then execute bash on this file (still with execve).  And so the behaviour of the pipe operator is perfectly replicated.
