/*
 * implements the stack library functions
 * 
 * this library offers the following functions:
 * push
 * pop
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * structure to hold the elements of the stack
 */
struct st_element{
    /* holds pointer to the data being stored */
    void *data;
    /* pointers to the next and prev elements in the stack */
    struct st_element *next;
    struct st_element *prev;
};

/*
 * push_st()   pushes an element on to the stack
 * top      :   pointer to the top of the stack
 * data     :   pointer to the data to be added to the stack
 * 
 * returns pointer to the top of the stack, 
 * returns NULL in case ENOMEM
 */
struct st_element *push_st(struct st_element *top, void *indata){
    /* input data is NULL */
    if(indata == NULL){
        return NULL;
    }
    /* allocate a structure to store the data */
    struct st_element *new = NULL;
    new = (struct st_element *)malloc(sizeof(struct st_element));
    if(new == NULL){
        printf("failed to allocate memory\n");
        return NULL;
    }
    /* populate the new element */
    new->data = indata;
    new->prev = NULL;
    new->next = NULL;
    /* top element is NULL */
    if(top == NULL){
        top = new;
        return top;
    }
    top->next = new;
    new->prev = top;
    top = new;
    return top;
}

/*
 * pop_st()    pops the top element from the stack
 * top      :   pointer to the top of the stack
 * void *   :   void pointer that will point to the data being popped
 *
 * returns the top element of the stack
 * returns NULL for errors
 */
struct st_element *pop_st(struct st_element *top, void *d){
    /* empty stack */
    if(!top || !d || !top->data){
        return NULL;
    }
    /* store a pointer to the data */
    memcpy(d, top->data, sizeof(d));
    /* move the top pointer */
    top = top->prev;
    if(top != NULL){
        top->next = NULL;
    }
    return top;
}

/*
 * movetop_st()    moves the top element of the stack to the prev 
 *                 element
 * top      :   pointer to the top of the stack
 *
 * returns the top element of the stack
 * returns NULL for errors
 */
struct st_element *movetop_st(struct st_element *top){
    /* empty stack */
    if(!top){
        return NULL;
    }
    /* move the top pointer */
    top = top->prev;
    if(top != NULL){
        top->next = NULL;
    }
    return top;
}

/*
 * top_st()    returns the data member of the element at the top of stack
 * top      :   pointer to the top of the stack
 *
 * returns data member of the structure forming the stack, 
 * NULL for empty stack or errors
 */
void *top_st(struct st_element *top){
    /* empty stack */
    if(top == NULL){
        return NULL;
    }
    return top->data;
}

/*
 * free_st()    frees up the memory occupied by a stack
 * top      :   pointer to the top of the stack
 *
 */
void *free_st(struct st_element *top){
    struct st_element *a = NULL;
    /* empty stack */
    if(top == NULL){
        return NULL;
    }
    /* move the top pointer */
    while(top){
        a = top;
        top = top->prev;
        /* WE DO NOT FREE DATA BECAUSE THE CALLING PROGRAM MAY NEED IT.
         * WE DO NOT HAVE ANY RIGHT OVER THAT DATA.
         * WE JUST DELETE OUR OWN INFRASTRUCTURE
         */
        free(a);
    }
    return;
}
