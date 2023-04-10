This program currently has a race condition and is not appropriate for a concurrent environment. Using 
Pthreads mutex locks (section 7.3.1), fix the race conditions. Test your now-thread-safe 
stack by creating 200 concurrent threads in main() that intermix pushing and popping values. 

Use a loop in main() to create all those threads. Apply all the things you've learned about creating 
and joining threads from previous chapters. 

Write one testStack function, and use it as the entry point for each thread. 
h
The testStack function should intermix 3 push operations with 3 pop operations in a loop that 
executes 500 times. 

All threads use the same stack. 

gcc -pthread stack-ptr.c -o stack-ptr is an example command to compile and link 
your program 

# os_3

