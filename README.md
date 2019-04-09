# Banker-s-algo
implementation of Banker's algorithm for deadlock avoidance and resource allocation using multithreading and mutex locks.
so, lets first know what is bankers algorithm and why we need it.
 we all know deadlock problem in operating system ,when a waiting process holds a resource which is needed by other waiting process, the waiting becomes infinity and it is deadlock. We know that we can prevent dead lock by breaking any one of the necessory conditions.
 so, can we avoid deadlock..?
 Answer is yes, by using bankers algorithm. 
 how can we avoid deadlock ?
 Safe state is a state where deadlock can never happen, where as unsafe state may cause a deadlock
 if there is atleast one safe state, we move to that state and  there will be  no chance to get stuck in deadlock.
 Sounds awesome, isn't it.
  lets talk more about it
My logic for implementing bankers algo is that first we'll check for safe sequence and if safe sequence exist then we allocate,update and 
satisfy the maximum requests it can make, this will check the worst possible case.
 we use threads for having concurrent access but we ensure that they cant change value of shared variables using mutex locks.
 we show our threads as if they are process and show the implementation of bankers algo.
 
 ----------------------------------------Just a quick revision of bankers algo is below--------------------------------------------
 DESCRIPTION
Banker's Algorithm
The banker’s algorithm is a resource allocation and deadlock avoidance algorithm that tests for safety by simulating the allocation for predetermined maximum possible amounts of all resources, then makes an “s-state” check to test for possible activities, before deciding whether allocation should be allowed to continue.
Following Data structures are used to implement the Banker’s Algorithm:
Let ‘n’ be the number of processes in the system and ‘m’ be the number of resources types.

Available : 
	It is a 1-d array of size ‘m’ indicating the number of available resources of each type.
	Available[ j ] = k means there are ‘k’ instances of resource type Rj

Max :
	It is a 2-d array of size ‘n*m’ that defines the maximum demand of each process in a system.
	Max[ i, j ] = k means process Pi may request at most ‘k’ instances of resource type Rj.

Allocation :
	It is a 2-d array of size ‘n*m’ that defines the number of resources of each type currently allocated to each process.
	Allocation[ i, j ] = k means process Pi is currently allocated ‘k’ instances of resource type Rj

Need :
	 It is a 2-d array of size ‘n*m’ that indicates the remaining resource need of each process.
	Need [ i,  j ] = k means process Pi currently allocated ‘k’ instances of resource type Rj
	Need [ i,  j ] = Max [ i,  j ] – Allocation [ i,  j ]


Allocationi specifies the resources currently allocated to process Pi and Needi specifies the additional resources that process Pi may still request to complete its task.
Banker’s algorithm consist of Safety algorithm and Resource request algorithm
Resource Request Algorithm
This describes the behavior of the system when a process makes a resource request in the form of a request matrix. The steps are:
1.	If number of requested instances of each resource is less than the need (which was declared previously by the process), go to step 2.
2.	If number of requested instances of each resource type is less than the available resources of each type, go to step 3. If not, the process has to wait because sufficient resources are not available yet.
3.	Now, assume that the resources have been allocated. Accordingly do,
Available = Available - Requesti
Allocation(i) = Allocation(i) + Request(i)
Need(i) = Need(i) - Request(i)
// i have taken the worse case , to have a healthy check

This step is done because the system needs to assume that resources have been allocated. So there will be less resources available after allocation. The number of allocated instances will increase. The need of the resources by the process will reduce. That's what is represented by the above three operations.
After completing the above three steps, check if the system is in safe state by applying the safety algorithm. If it is in safe state, proceed to allocate the requested resources. Else, the process has to wait longer.
________________________________________
Safety Algorithm
1.	Let Work and Finish be vectors of length m and n, respectively. Initially,
2.	Work = Available
3.	Finish[i] =false for i = 0, 1, ... , n - 1.
This means, initially, no process has finished and the number of available resources is represented by the Available array.
4.	Find an index i such that both
5.	Finish[i] ==false
6.	Needi <= Work
If there is no such i present, then proceed to step 4.
It means, we need to find an unfinished process whose need can be satisfied by the available resources. If no such process exists, just go to step 4.
7.	Perform the following:
8.	Work = Work + Allocation;
9.	Finish[i] = true;
Go to step 2.
When an unfinished process is found, then the resources are allocated and the process is marked finished. And then, the loop is repeated to check the same for all other processes.
If Finish[i] == true for all i, then the system is in a safe state.
That means if all processes are finished, then the system is in safe state.
