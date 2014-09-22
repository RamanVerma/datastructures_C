/*
 * fifoQueue demonstrates the implementation and basic operations
 * of a first in first out queue
 */
#include<stdio.h>
#include<stdlib.h>

/* pointers for the head and tail of the fifo queue */
struct element *head = NULL;
struct element *tail = NULL;
/* structure for each element of the queue */
struct element{
    /* pointer to the data stored on fifo queue */
    void *data;
    /* pointers to the next and previous elements in the queue */
    struct element *next;
    struct element *prev;
};

/*
 * add_Q()    adds an element to the fifo Queue
 * @data    void pointer to some data that has to be added to the queue
 *
 * returns integer 0 for success, -1 for failure or for NULL imput
 */
int add_Q(void *data){
    if(data == NULL)
        return -1;
    /*
     * wrap the incoming data into struct element
     */
    struct element *new = NULL;
    new = (struct element *)malloc(sizeof(struct element));
    if(new == NULL){
        printf("failed to allocate memory\n");
        return -1;
    }
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    /*
     * now add this new element to the queue
     */
    if(tail == NULL){
        /* empty queue */
        tail = new;
        head = new;
        return 0;
    }
    new->next = tail;
    tail->prev = new;
    tail = new;
    return 0;
}

/*
 * remove_Q() removes an element from the head of the queue
 *
 * returns a pointer to the data member of the head element, NULL for empty 
 * queue
 */
void *remove_Q(){
    void *r = NULL;
    if(head != NULL){
        r = head->data;
        head = head->prev;
    }
    return r;
}

/*
 * get_Q()    gets the data member of the head of the queue
 *          does not remove the leent from the queue
 *
 * returns pointer to the data member of the head element of the queue
 * NULL is returned for an empty queue
 */
void *get_Q(){
    if(head != NULL)
        return head->data;
    return NULL;
}
