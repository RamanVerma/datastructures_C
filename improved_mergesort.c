/*
 * improved version of merge sort
 * this code does not require O(n) extra space to perform merge operation.
 * it requires O(1) extra space and the fundamental merge function will 
 * still require O(n) copy/move operations.
 *
 * the idea is based on a hop function that shifts every element of an array
 * by 'h' places in a time complexity of O(n) and space complexity of O(1)
 */

#include<stdio.h>
#include<stdlib.h>

/* Max number of elements on the input array */
#define MAX_ELEMS 8

/*
 * structure to contain data. each structure is identified by a unique key
 */
struct data{
    int alpha;
    int key;
};

/*
 * hop()    shifts each element of an array by 'h' places and achieves the 
 *          same in O(1) space and O(n) time complexity
 * @array   :   first element of the array
 * @n       :   number of eleents in the array
 * @h       :   number of shifts to be done for each element of the array
 *
 * returns the first element of the changed/shifted array
 */
struct data *hop(struct data *array, int n, int h){
    /*
     * preserve the start of the array
     */
    struct data *start = array;
    /*
     * invalid data conditions
     */
    if(array == NULL || n < 2 || h < 1 || h == n){
        printf("Invalid data\n");
        return start;
    }
    /*
     * memory space to save the array elements
     */
    struct data *save;
    save = (struct data *)malloc(sizeof(struct data));
    if(save == NULL){
        printf("Unable to allocate memory\n");
        return start;
    }
    /* number of elements shifted */
    int elems_shifted = 0;
    /* starting index for the processing */
    int processing_start_index = n;
    /*
     * source and destinatin indices in the array where an element has to be 
     * copied at any given point in the shift workflow
     */
    int source = 0;
    int destination = 0;
    /*
     * execute this loop until the number of elements shifted < total number 
     * of elements in the input array
     */
    while(elems_shifted < n){
        /*
         * determine the array index where the processing will begin and save
         * the data at this element
         */
        processing_start_index -= 1;
        memcpy(save, (array + processing_start_index), sizeof(struct data));
        destination = processing_start_index;
        do{
            /*
             * get the source index from where data has to be copied to the
             * index position being currently processed
             */
            source = processing_start_index - h;
            if(source < 0){
                /* rollover logic */
                source = n + source;
            }
            /* Now copy data from source to destination */
            memcpy((array + destination), (array + source), sizeof(struct data));
            /*
             * increment the number of elements that have been shifted
             */
            if(source != processing_start_index){
                elems_shifted++;
            }
        }while(source != processing_start_index);
        /* Now copy saved data to destination */
        memcpy((array + destination), save, sizeof(struct data));
    }
}

/*
 * printarray()     prints the array data
 * @input       :   pointer to the start of the array to be printed
 * @n           :   length of the array
 */
void printarray(struct data *input, int n){
    int index = 0;
    for(index = 0; index < n; index ++){
        printf("%d\t", (input + index)->key);
    }
}

/*
 * main function
 */
void main(){
    int random = 0;
    struct data *input = NULL;
    /*
     * allocate space to get the input array from the user
     */
    input = (struct data *)malloc(sizeof(struct data) * MAX_ELEMS);
    if(input == NULL){
        printf("Unable to allocate memory\n");
        return;
    }
    /*
     * get user inout
     */
    printf("Enter %d integers", MAX_ELEMS);
    int in = 0;
    for(in = 0; in < MAX_ELEMS; in++){
        scanf("%d", &((input + in)->key));
    }
    /* Generate a random number for the number of hops */
    random = MAX_ELEMS - 2; 
    /* print the array before the shift */
    printf("Before shifting the array by %d hops", random);
    printarray(input, MAX_ELEMS);
    /* call the hop function */
    hop(input, MAX_ELEMS, random);
    /* print the array after the shift */
    printf("After shifting the array by %d hops", random);
    printarray(input, MAX_ELEMS);
}
