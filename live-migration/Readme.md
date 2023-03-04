These C code snippets allocate and write memory in a `while(1)` loop.

Both snippets are used for testing live migration when the guest's memory is constantly changing between rounds. However, `memory-test2.c` is more reliable since it does not deallocate the memory.

Usage:
```
# Guest
student@vm:~/live-migration$ make
student@vm:~/live-migration$ ./memory-test2

# Host
student@host:~/$ # migrate VM and measure rounds

```
