//raise is also like kill but it is used to send the signal to itself(current process)..

so raise(SIGKILL)  is equalent to kill(SIGKILL,getpid());
