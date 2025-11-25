#include<stdio.h>
#include<stdlib.h>

#define MAX 100
int Queue[MAX];
int rear=-1,front=-1;
int Visited[MAX];

void create_graph(int** graph,int n)
{
    int t;
    printf("Enter adjency list:");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            
            printf("Graph[%d][%d]:",i,j);
            scanf("%d",&t);
            graph[i][j]=t;
        }
    }
}
int enque(int vertex)
{
    if (rear==MAX-1){printf("overflow");exit(-1);}
    
}
