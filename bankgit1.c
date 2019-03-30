#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define M 3//No of resources
#define N 5 //No of processes

int  i,y, j, k; 
pthread_mutex_t mutex1; 
int init[M];
int avail [M];
int alloc [N][M]; 
int max [N][M];
int need [N][M];
void displayInput();
void *process(void* procsID);
alloc[5][3] = { { 0, 1, 0 }, // P0    // Allocation Matrix 
                { 2, 0, 0 }, // P1 
                { 3, 0, 2 }, // P2 
                { 2, 1, 1 }, // P3 
                { 0, 0, 2 } }; // P4 
  
max[5][3] = { { 7, 5, 3 }, // P0    // MAX Matrix 
              { 3, 2, 2 }, // P1 
              { 9, 0, 2 }, // P2 
              { 2, 2, 2 }, // P3 
              { 4, 3, 3 } }; // P4 
              
avail[3] = { 3, 3, 2 }; // Available Resources 
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
	int pID = *(int*)procsID;	
	}          
  int main()
  {
    pthread_mutex_init(&mutex1,NULL);
    pthread_attr_t attrDefault;
    pthread_attr_init(&attrDefault);
    pthread_t *tid = malloc(sizeof(pthread_t) * N);

    int *pid = malloc(sizeof(int) * N);
	displayInput();
        
            for(i = 0; i < N; i++)
            {
                        *(pid + i) = i;
                        pthread_create((tid+i), &attrDefault,process, (pid+i));
            }

            
            for(i = 0; i < N; i++)
            {
                        pthread_join(*(tid+i),NULL);
            }
            return 0;
        }
