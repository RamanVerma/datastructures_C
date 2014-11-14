/*
 * threaded binary search trees
 * threaded bstree are an optimization over the bstree. a node stores a special
 * pointer called a thread, to its predecessor node if its left child is NULL.
 * also, it stores a similar pointer to its successor node, if its right child
 * is NULL.
 * node structure is modified a bit to identify whether a left/right  pointer 
 * is a child node or a thread.
 * also, threaded bstree have a head node whos left child points to the root of 
 * the bstree. its right child points to itself. its significance lies in the 
 * fact that the node with smallest and the node with the highest keys point 
 * to it.
 */

#include<stdio.h>
#include"stack.h"
#include"fifoQueue.h"
#include"time.h"

/* max number of elements for the threaded bstree */
#define MAX_ELEMS 10

/* threaded node structure for bstree */
struct threaded_node{
    /* key element of the node */
    int key;
    /* pointers to the left/right child, or predecessor/successor nodes */
    struct threaded_node *lpointer;
    struct threaded_node *rpointer;
    /* identifiers if a left/right pointer is a thread/child pointer; 1=child */
    int islchild;
    int isrchild;
};

/* top element for the stack */
struct st_element *top;
/* typedef threaded_node for a simpler name */
typedef struct threaded_node tnode;

/*
 * printTbstree()   prints the threaded bstree level wise and then lists the 
 *                  successor and predecessor nodes
 *
 * @h       :   head node of the threaded bstree to be printed
 *
 * return nothing
 */
void printTbstree(tnode *h){
    if(!h || !h->lpointer)
        return;
    /* create a place holder node to represent new line */
    tnode *newline = (tnode *)malloc(sizeof(sizeof(tnode)));
    if(!newline){
        printf("No memory.\n");
        return;
    }
    newline->key = -1;
    /* root node is pointed to by head's left child */
    tnode *a = h->lpointer;
    /* add root and a new line place holder to the fifo Queue */
    add_Q((void *)a);
    add_Q((void *)newline);
    /* run through the loop until the fifo Queue gets empty */
    while(a=remove_Q()){
        /* if the retrieved node is the new line placeholder */
        if(a->key == -1){
            printf("\n");
        }else{
            /* got a valid node from the tree */
            printf("%d\t", a->key);
            /* add this node's left and right children(if any) to fifo Queue */
            if(a->islchild)
                add_Q(a->lpointer);
            if(a->isrchild)
                add_Q(a->rpointer);
            /* add this node to a stack, if it has a thread */
            if(!a->islchild || !a->isrchild)
                push_st(top, a);
        }
    }
    /* Now process the stack structure for nodes with threads */
    while(a=pop_st(top)){
        if(!a->islchild)
            printf("Node %d : Predecessor Node : %d\n", a->key, a->lpointer->key);
        if(!a->isrchild)
            printf("Node %d : Successor Node : %d\n", a->key, a->rpointer->key);
    }
    return;
}

/*
 * findSuccessor()    function to successor node to any given node
 * @n       :   node whose successor is to be found
 * @top     :   top pointer for a stack where the path to this node from the
 *              root of the bstree was recorded
 *
 * returns pointer to the successor node or NULL, in case there is no 
 * successor
 */
tnode *findSuccessor(tnode *n, struct st_element *top){
    tnode *p = NULL;
    /* run thru the loop until stack is not empty */
    while(p=pop_st(top)){
        /* condition for predecessor: current node is left child of parent */
        if(p->lpointer == n)
            break;
        n = p;
    }
    /* if we reached here, there is no predecessor */
    return p;
}

/*
 * findPredecessor()    function to predecessor node to any given node
 * @n       :   node whose predecessor is to be found
 * @top     :   top pointer for a stack where the path to this node from the
 *              root of the bstree was recorded
 *
 * returns pointer to the predecessor node or NULL, in case there is no 
 * predecessor
 */
tnode *findPredecessor(tnode *n, struct st_element *top){
    tnode *p = NULL;
    /* run thru the loop until stack is not empty */
    while(p=pop_st(top)){
        /* condition for predecessor: current node is right child of parent */
        if(p->rpointer == n)
            break;
        n = p;
    }
    /* if we reached here, there is no predecessor */
    return p;
}

/*
 * addNode()    adds a node to the threaded bstree
 * @h       :   head node of the tree
 * @n       :   node to be added to the threaded bstree
 *
 * returns a pointer to the head of the tree
 */
tnode *addNode(tnode *h, tnode *n){
    /* special case: head is NULL OR root is NULL */
    if(!h || !h->lpointer){
        /* head is NULL */
        if(!h){
            /* allocate head node */
            h = (tnode *)malloc(sizeof(tnode));
            if(!h){
                printf("No memory.\n");
                return NULL;
            }
        }
        h->lpointer = n;
        h->islchild = 1;
        h->isrchild = 0;
        h->rpointer = h;
        /* add threads to the new node */
        n->islchild = 0;
        n->isrchild = 0;
        n->lpointer = h;
        n->rpointer = h;
        return h;
    }
    /* traverse thru the bstree to find a place to insert the new node */
    tnode *a = h->lpointer;
    while(1){
        /* if found a match, just return */
        if(a->key == n->key)
            return h;
        /* push the current node on a stack */
        push_st(top, (void *)a);
        if(a->key < n->key){
            if(a->isrchild)
                    a = a->rpointer;
            else
                break;
        } else {
            if(a->islchild)
                a = a->lpointer;
            else
                break;
        }
    }
    /* 
     * by now, we have reached the correct place for the new node in the 
     * threaded bstree structure. push the new node on stack.
     */
    push_st(top, (void *)n);
    if(a->key > n->key){
        a->islchild = 1;
        a->lpointer = n;
    } else {
        a->isrchild = 1;
        a->rpointer = n;
    }
    /* add threads to the newly added node */
    n->islchild = 0;
    n->isrchild = 0;
    n->lpointer = findPredecessor(n, top);
    if(!n->lpointer)
        n->lpointer = h;
    n->rpointer = findSuccessor(n, top);
    if(!n->rpointer)
        n->rpointer = h;
    return h;
}

/*
 * makeTbstree()   make a threaded binary search tree
 * @h       :   pointer to the head node
 *
 * returns a pointer to the head node, or NULL in case of an error
 */
tnode *makeTbstree(tnode *h){
    tnode *n = NULL;
    int x = 0;
    for(x = 0;x < MAX_ELEMS; x++){
        /*
         * allocate memory to the node structure
         */
        n = (tnode *)malloc(sizeof(tnode));
        if(!n){
            printf("failed to allocate memory\n");
            return NULL;
        }
        /*
         * generate a random key and initialize the left and right children
         */
        n->key = rand() % 100;
        n->islchild = 0;
        n->isrchild = 0;
        n->lpointer = NULL;
        n->rpointer = NULL;
        h = addNode(h, n);
    }
    return h;
}

/*
 * main function
 */
void main(){
    srand(time(NULL));
    /* allocate head node */
    tnode *h = (tnode *)malloc(sizeof(tnode));
    if(!h){
        printf("No memory.\n");
        return;
    }
    h->lpointer = NULL;
    h->islchild = 1;
    h->isrchild = 0;
    h->rpointer = h;
    /*
     * create a threaded bstree
     */
    h = makeTbstree(h);
    printf("=============================================\n");
    printf("------------------Working tree---------------\n");
    /* print the Threaded BSTree */
    printTbstree(h);
}
