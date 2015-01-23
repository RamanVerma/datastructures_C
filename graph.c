/*
* This program will implement the representation of data in the form of a graph
* structure, along with many of the common algorithms on this data structure
*/
    
#include<stdio.h>
#include<string.h>
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

/*
* addEdge	:	adds an edge to the adjecency list or adjacency matrix
* @g		:	pointer to the first adjacency list
* @head		: 	head of the edge to be added
* @tail		:	tail of the edge to be added
*
* returns void
*/
void addEdge(struct listnode **g, int head, int tail){
    struct listnode *ln, *lastlistnode;
    /* allocate and initialize a new listnode */
    ln = (struct listnode *)malloc(sizeof(struct listnode));
    if(ln == NULL){
        printf("Could not allocate memory. Exiting!!\n");
        return;
    }       
    ln->n.key = head;
    ln->nln = NULL;
    /* Add the newly allocated listnode to the end of tail node's adj list */
    if(g[tail] == NULL){
        g[tail] = ln;
    } else {
        lastlistnode = g[tail];
        while(lastlistnode->nln != NULL)
            lastlistnode = lastlistnode->nln;
        lastlistnode->nln = ln;
    }
    /* allocate and initialize a new listnode */
    ln = (struct listnode *)malloc(sizeof(struct listnode));
    if(ln == NULL){
        printf("Could not allocate memory. Exiting!!\n");
        return;
    }       
    ln->n.key = tail;
    ln->nln = NULL;
    /* Add the newly allocated listnode to the end of head node's adj list */
    if(g[head] == NULL){
        g[head] = ln;
    } else {
        lastlistnode = g[head];
        while(lastlistnode->nln != NULL)
            lastlistnode = lastlistnode->nln;
        lastlistnode->nln = ln;
    }
}

/*
* displayGraph  :   displays the graph represented either as adjacency list
*                   or matrix
* @g            :   pointer to the graph structure
* @num          :   number of nodes in the graph
*
* returns void
*/
void displayGraph(void **g, int num){
    int index = 0;
    struct listnode *lnptr;
    /* create a loop to go over all the nodes */
    printf("===Displaying Graph===\n");
    for(index = 0;index < num; index++){
        printf("Node %d : ", index);
        if((lnptr = (struct listnode *)g[index]) == NULL)
            continue;
        while(lnptr != NULL){
            printf(" - %d - ", lnptr->n.key);
            lnptr = lnptr->nln;
        }
        printf("\n");
    }
    printf("=====================\n");
}

/* main function */
int main(){
    int index = 0;
    int tail, head, numnodes, numedges;
    /* Accept user input */
    printf("Enter the number of nodes in the graph\n");
    scanf("%d",&numnodes);
    printf("Enter the number of edges in the graph\n");
    scanf("%d",&numedges);
    /* allocate an array of pointers to listnode structures */
    struct listnode **graph = (struct listnode **)calloc(numnodes, sizeof(struct listnode *));
    if(graph == NULL){
        printf("Could not allocate memory. Exiting!!");
        return -1;
    }
    /* accept user input describing all edges and add them to the adj list */
    printf("Enter information about the edges in the graph\n");
    for(index = 0;index < numedges; index++ ){
        printf("Edge # %d: Tail : ",index);
        scanf("%d", &tail);
        printf("Edge # %d: Head : ",index);
        scanf("%d", &head);
        addEdge(graph, head, tail);
    }
    /* display the graph */
    displayGraph((void **)graph, numnodes);
}
