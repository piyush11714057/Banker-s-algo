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
  {  printf("Enter available VECTOR\n");
            
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
