# Banker-s-algo
implementation of Banker's algorithm for deadlock avoidance and resource allocation using multithreading and mutex locks.
so, lets first know what is bankers algorithm and why we need it.
 we all know deadlock problem in operating system ,when a waiting process holds a resource which is needed by other waiting process, the waiting becomes infinity and it is deadlock.
 so, can we avoid deadlock..?
 Answer is yes, by using bankers algorithm. if there is atleast one safe state, we move to that state and here there is no chance to get stuck in deadlock.

