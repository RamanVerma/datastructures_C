/*
 * demonstrates heap sort algorithm
 */

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

/* Max number of elements in the array */
#define MAX_ELEM 16

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
    int child = n + 1;
    int parent = child / 2;
    /*
     * bubble up the newly added element till it becomes smaller than
     * or equal to its parent
     */
    while(((root + child - 1)->key > (root + parent - 1)->key) && (parent > 0)){
        switch_elems(root, child - 1, parent - 1);
        child = parent;
        parent = child / 2;
    }
    return;
}

/*
 * adjust()         adjusts/sinks the root of a complete tree to a place
 *                  so that the tree becomes a max heap. the pre condition
 *                  is that the subtrees of the concerned root follow the
 *                  conditions of a max heap. so the utility of this function
 *                  lies in the fact that it will change this complete tree
 *                  in a max heap
 * @root        :   root of the complete tree to be adjusted
 * @n           :   # of elements in the complete tree
 *
 * returns the pointer to the root of the complete tree, which has now become 
 * a max heap
 * this code is based on a array based implementation of the complete tree
 */
struct data *adjust(struct data *root, int n){
    int rootloc = 1;
    int childloc = rootloc * 2;
    int maxchildkey = 0;
    int maxchildloc = childloc;
    struct data *save = root;
    /*
     * sink the root to that position where its key becomes greater than
     * or equal to the max key among its children, if any
     */
    while(childloc <= n){
        /*
         * assign the max child key to the left child's key
         */
        maxchildkey = (root + childloc - 1)->key;
        maxchildloc = childloc;
        /*
         * check that the right child exists and what's its relation wrt left
         * child's key value
         */
        if((childloc + 1) <= n){
            if((root + childloc)->key > maxchildkey){
                maxchildkey = (root + childloc)->key;
                maxchildloc = childloc + 1;
            }
        }
        /*
         * switch the root and the maxchild if root is smaller than the 
         * maxchild, and repeat the process in the subtree
         */
        if((root + rootloc - 1)->key < maxchildkey){
            switch_elems(root, rootloc - 1, maxchildloc - 1);
            rootloc = maxchildloc;
            childloc = rootloc * 2;
        }else{
            /*
             * reached the correct position for root element
             */
            break;
        }
    }
    return save;
}

/*
 * heapsort()       sorts an array in ascending order. the array has been 
 *                  arranged as a max heap.
 * @root        :   root of the max heap to be sorted
 * @n           :   # of elements in the max heap to be sorted
 *
 * returns the pointer to the first element of the sorted array
 */
struct data *heapsort(struct data *root, int n){
    int x = 1;
    int rootloc = 1;
    int finalelem = n;
    struct data *save = root;
    /*
     * run this loop for every element in the heap
     */
    for(x = 1; x < n; x++, finalelem--){
        switch_elems(root, rootloc - 1, finalelem - 1);
        root = adjust(root, n - x);
    }
    return save;
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
    printf("Initial max heap represented as an array\n");
    print_the_heap(array);
    /* call heapsort function */
    array = heapsort(array, MAX_ELEM);
    /* display the heap */
    printf("Sorted array\n");
    print_the_heap(array);
}
