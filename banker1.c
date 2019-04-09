#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define M 3//No of resources
#define N 5 //No of processes

int  i,y, j, k; 
    
 int init[M];
 int avail [M];
 int alloc [N][M]; 
 int max [N][M];
 int need [N][M];
    int alloc[5][3] = { { 0, 1, 0 }, // P0    // Allocation Matrix 
                        { 2, 0, 0 }, // P1 
                        { 3, 0, 2 }, // P2 
                        { 2, 1, 1 }, // P3 
                        { 0, 0, 2 } }; // P4 
  
    int max[5][3] = { { 7, 5, 3 }, // P0    // MAX Matrix 
                      { 3, 2, 2 }, // P1 
                      { 9, 0, 2 }, // P2 
                      { 2, 2, 2 }, // P3 
                      { 4, 3, 3 } }; // P4 
  
    int avail[3] = { 3, 3, 2 }; // Available Resources 
pthread_mutex_t mutex;
void *Safestate(void* procsID)
	{     	pthread_mutex_lock(&mutex);  
	    int pID = *(int*)procsID;
    	int c=0;
	 	int f[N], ind = 0; 
	 	
	 
   		for ( k = 0; k < N; k++)
		   { 
       		 f[k] = 0; 
    		} 
        
    	
            if (f[pID] == 0) { 
  
                int flag = 0; 
                for (j = 0; j < M; j++) {
				
                    if (need[pID][j] > avail[j]) {
					
                    flag = 1; 
                    break;
				}
                } 
  
                if (flag == 0) { 
               
                    ans[ind++] = pID; 
                    for (y = 0; y < M; y++) 
                        avail[y] += alloc[pID][y]; 
                    f[pID] = 1; 
                    
                } 
                else
                { pthread_mutex_unlock(&mutex);
                	Safestate(pID);
				}
            } 
    
	
 	 pthread_mutex_unlock(&mutex);
	
 	}
 	


int main()
{
    
     for (i = 0; i < N; ++i)
            {
                        for (j = 0; j < M; ++j)
                        {
                                   need[i][j] = max[i][j] - alloc[i][j]; 
                        }
            }
    
            pthread_mutex_init(&mutex,NULL);
            pthread_attr_t attrDefault;
            pthread_attr_init(&attrDefault);
            pthread_t *tid = malloc(sizeof(pthread_t) * N);

            int *pid = malloc(sizeof(int) * N);

            
            for(i = 0; i < N; i++)
            {
                        *(pid + i) = i;
                        pthread_create((tid+i), &attrDefault, Safestate, (pid+i));
            }
            for(i = 0; i < N; i++)
            {
                        pthread_join(*(tid+i),NULL);
            }
	
	printf("Following is the SAFE Sequence\n"); 
    for (i = 0; i < N - 1; i++) 
    printf(" P%d ->", ans[i]); 
    printf(" P%d", ans[N - 1]); 
  
    return (0); 
	
}
