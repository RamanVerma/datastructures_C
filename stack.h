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

/* denotes the top element of the stack */
struct st_element *top;

/*
 * push_st()   pushes an element on to the stack
 * data     :   pointer to the data to be added to the stack
 *
 * returns pointer to the data added to the stack, 
 * returns NULL in case the input was NULL, or ENOMEM
 */
void *push_st(void *indata){
    /* imput data is NULL */
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
    /* no element in the stack yet */
    if(top == NULL){
        top = new;
        return top->data;
    }
    top->next = new;
    new->prev = top;
    top = new;
    return top->data;
}

/*
 * pop_st()    pops the top element from the stack
 *
 * returns the data contained in the top element of the stack,
 * returns NULL for errors
 */
void *pop_st(){
    /* empty stack */
    if(top == NULL){
        return NULL;
    }
    /* store a pointer to the data */
    void *data = top->data;
    /* move the top pointer */
    top = top->prev;
    if(top != NULL){
        top->next = NULL;
    }
    return data;
}

/*
 * top_st()    returns the data member of the element at the top of stack
 *
 * returns data member of the structure forming the stack, 
 * NULL for empty stack or errors
 */
void *top_st(){
    /* empty stack */
    if(top == NULL){
        return NULL;
    }
    return top->data;
}
