#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define M 3//No of avail
#define N 5 //No of processes
#include <stdbool.h>
#include <time.h>
#include<unistd.h>
int  i,y, j, k; 
pthread_mutex_t mutex1; 
int init[M];
int avail [M];
int alloc [N][M]; 
int max [N][M];
int need [N][M];
//-
int *safeSeq;
int RanProcesses = 0;
bool SafeSeqModify();

pthread_cond_t condition;

//-
void displayInput();
void *process(void* procsID);

   void displayInput()
   {
   	
   	printf("Available Vector is:\n");
            for (i = 0; i < M; ++i)
            {
                     printf("%d, ",avail[i]);
            }
            printf("\n");
    printf("Allocation Matrix is:\n");
            
            for (i = 0; i < N; ++i)
            {
                        printf("// ");
                        for (j = 0; j < M; ++j)
                        {
                                printf("%d, ", alloc[i][j]);
                        }
                        printf("// \n");
            }
   	printf("Need Matrix is:\n");
            for (i = 0; i < N; ++i)
            {
	            printf("// ");
	            for (j = 0; j < M; ++j)
	            {
	                        printf("%d, ", need[i][j]);
	            }
	            printf("// \n");
            }
           

   	
		}    
	void *process(void* procsID)
	{
	int p = *((int*)procsID);

        
        // condition check
        while(p != safeSeq[RanProcesses])
                pthread_cond_wait(&condition, &mutex1);

pthread_mutex_lock(&mutex1);
	// process
        printf("\n--> Process  %d", p+1);
        printf("\n\t Allocated is : ");
        for(i=0; i<M; i++)
        {
        	
		        printf("%3d", alloc[p][i]);
		}
        printf("\n\tNeeded is    : ");
        for( i=0; i<M; i++)
        {
		
                printf("%3d", need[p][i]);
		}
        printf("\n\tAvailable are : ");
        for(i=0; i<M; i++)
        {
		
                printf("%3d", avail[i]);
 		}
        printf("\n"); sleep(1);

        printf("\tResource Allocated!");
        printf("\n"); 
		sleep(1);
        printf("\tProcess Code Running...");
        printf("\n"); 
		sleep(1); // process code
        printf("\tProcess Code Completed...");
        printf("\n"); 
		sleep(1);
        printf("\tProcess Releasing Resource...");
        printf("\n"); 
		sleep(1);
        printf("\tResource Released!");

	for( i=0; i<M; i++)
                avail[i] += alloc[p][i];

        printf("\n\tNow Available : ");
        for( i=0; i<M; i++)
                printf("%3d", avail[i]);
        printf("\n\n");

        sleep(1);

    	// condition broadcast
        RanProcesses++;
        
        pthread_mutex_unlock(&mutex1);
        pthread_cond_broadcast(&condition);
        sleep(10);
	//pthread_exit(NULL);	
	}   
	bool SafeSeqModi   fy()
	{
		
		
		 int TempResources[N];
        for( i=0; i<N; i++) 
		{
		TempResources[i] = avail[i];
		}
        bool finished[N];
        for( i=0; i<N; i++)
        {
		 finished[i] = false;
		}
        int nfinished=0;
        while(nfinished <N) {
                bool safe = false;

                for( i=0; i<N; i++) {
                        if(!finished[i]) {
                                bool possible = true;

                                for( j=0; j< M; j++)
                                        if(need[i][j] > TempResources[j]) {
                                                possible = false;
                                                break;
                                        }

                                if(possible) {
                                        for( j=0; j<N; j++)
                                                TempResources[j] += alloc[i][j];
                                        safeSeq[nfinished] = i;
                                        finished[i] = true;
                                        ++nfinished;
                                        safe = true;
                                }
                        }
                }

                if(!safe) {
                        for( k=0; k<N; k++) safeSeq[k] = -1;
                        return false; // no safe sequence found
                }
        }
        return true; // safe sequence found
		   }       
  int main()
  {
  	  printf("\t\t\t \t\t\t Banker\'s algorithm\n");
  	
  	    printf("Enter available VECTOR\n");
            
            for(i = 0; i < M; i++)
            {
                        
                        scanf("%d",&init[i]);
                        avail[i] = init[i];
            }
       printf("Enter Allocation Matrix\n");
            for(i = 0; i < N; i++)
            {
                         
            for(j = 0; j< M; j++)
            {
                        
                        scanf("%d",&alloc [i][j]);
                        
            }
            }
       printf("Enter MAX Matrix");
            for(i = 0; i < N; i++)
            {
                         
            for(j = 0; j< M; j++)
            {
                       
                        scanf("%d",&max[i][j]);
                        
            }
            }

            
            for (i = 0; i < N; ++i)
            {
                        for (j = 0; j < M; ++j)
                        {
                                    need[i][j] = max[i][j] - alloc[i][j];
                        }
            }
            

    pthread_mutex_init(&mutex1,NULL);
    pthread_attr_t attrDefault;
    pthread_attr_init(&attrDefault);
    pthread_t *tid = (malloc(sizeof(pthread_t) * N));

    int *pid = (int*) malloc(sizeof(int) * N);
	  displayInput();
		safeSeq = (int *)malloc(N * sizeof(*safeSeq));
        for( i=0; i<N; i++) safeSeq[i] = -1;

        if(!SafeSeqModify()) {
                printf("\nUnsafe State! The processes leads the system to a unsafe state, which may lead to deadlock.\n\n");
              exit(-1);
        }

        printf("\n\nSafe Sequence Found : ");
        for( i=0; i<N; i++) {
                printf("%-3d", safeSeq[i]+1);
        }

        printf("\nExecuting Processes...\n\n");
        sleep(1);
	
       
            for(i = 0; i < N; i++)
            {
                        *(pid + i) = i;
                        pthread_create((tid+i), &attrDefault,process, (pid+i));
            }

            
            for(i = 0; i < N; i++)
            {
                        pthread_join(*(tid+i),NULL);
            }
           
          
            free(tid);
            free(pid);
            free(safeSeq);
            return 0;
        }
