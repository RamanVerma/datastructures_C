/*
 * demonstrates heap sort algorithm
 */

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

/* Max number of elements in the array */
#define MAX_ELEM 8

/*
 * data stricture for the elements to e sorted
 */
struct data{
    int alpha;
    int key;
};

/*
 * switch()         switches two elements in an array
 * @root        :   root of the heap represented as an array
 * @a           :   element at index a
 * @b           :   element at index b
 */
void switch_elems(struct data *root, int a, int b){
    struct data save;
    memcpy(&save, (root + a), sizeof(struct data));
    memcpy((root + a), (root + b), sizeof(struct data));
    memcpy((root + b), &save, sizeof(struct data));
}

/*
 * add_to_heap()    adds an element to the heap structure
 * @root        :   root of the heap structure
 * @elem        :   element to be added to the structure
 * @n           :   current length of the heap structure
 *
 * tree is represented in the array representation
 */
void add_to_heap(struct data *root, struct data *elem, int n){
    /*
     * copy the element to nth location in the array
     */
    memcpy((root + n), elem, sizeof(struct data));
    /*
     * heap is empty
     */
    if(n == 0){
        return;
    }
    int parent = (n + 1) / 2;
    /*
     * bubble up the newly added element till it becomes greater than
     * or equal to its parent
     */
    while(((root + n - 1)->key > (root + parent - 1)->key) && (parent > 0)){
        switch_elems(root, n - 1, parent - 1);
        n = parent;
        parent = n / 2;
    }
    return;
}

/*
 * print_the_heap() prints the heap as an array
 * @root        :   root of the heap structure
 */
void print_the_heap(struct data *root){
    int i = 0;
    for(i = 0; i < MAX_ELEM; i++){
        printf("%d\t", (root + i)->key);
    }
    printf("\n");
}

/*
 * main function
 */
void main(){
    int i = 0;
    /*
     * allocate an array of type struct data 
     */
    struct data *array = NULL;
    array = (struct data *)malloc(sizeof(struct data) * MAX_ELEM);
    if(array == NULL){
        printf("Failed to allocate memory\n");
        return;
    }
    /*
     * initialize the input array to hold '\0' values
     */
    memset(array, '\0', sizeof(array));
    struct data temp;
    /*
     * generate some random integer values as input to the tree
     */
    srand(time(NULL));
    for(i = 0; i < MAX_ELEM; i++){
        temp.key = rand() % 100;
        add_to_heap(array, &temp, i);
    }
    /* display the heap */
    print_the_heap(array);
}
