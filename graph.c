/*
* This program will implement the representation of dat in the form of a graph
* structure, along with many of the common algorithms on such a data structure
*/

#include<stdio.h>
#include<stdlib.h>

/* Max number of nodes in the graph */
int numnodes;
/* 
* Struct representing each node of a graph. Right now there is no data, but 
* we can add that later
*/
struct node{
    int key;
};
/* Struct represnting the elements of the adjacency list */
struct listnode{
    struct node n;
    struct listnode *nln;
};


/* main function */
int main(){
    int index = 0;
    int tail, head;
    struct listnode *ln;
    struct listnode *lastlistnode;

    /* Accept user input */
    printf("Enter the number of nodes in the graph\n");
    scanf("%d",&numnodes);
    struct listnode *graph[numnodes];
    printf("Enter information about the edges in the graph\n");
    for(index = 0;index < numnodes; index++ ){
        printf("Edge # %d: Tail :\n",index);
        scanf("%d", &tail);
        printf("Edge # %d: Head :\n",index);
        scanf("%d", &head);
        /* allocate and initialize a new listnode */
        ln = (struct listnode *)malloc(sizeof(struct listnode));
        if(ln == NULL){
            printf("Could not allocate memory. Exiting!!\n");
            return -1;
        }       
        ln->n.key = head;
        ln->nln = NULL;
        /* Add the newly allocated listnode to the end of corres adj list */
        lastlistnode = graph[tail];
        while(lastlistnode != NULL)
            lastlistnode = lastlistnode->nln;
        lastlistnode = ln;
    }
}
