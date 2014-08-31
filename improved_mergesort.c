/*
 * improved version of merge sort
 * this code does not require O(n) extra space to perform merge operation.
 * it requires O(1) extra space and the fundamental merge function will 
 * still require O(n) copy/move operations.
 *
 * the idea is based on a hop function that shifts every element of an array
 * by 'h' places in a time complexity of O(n) and space complexity of O(1)
 *
 * this function is further used by the merge_sorted_arrays function that 
 * merges two sorted arrays, placed consecutively in the memory, using O(1)
 * space complexity and O(n) time complexity. this function will form the 
 * basis of a full fledged merge sort
 *
 * For full problem statement, please refer:
 * Fundamentals of Data Structures in C
 * Ellis Horowitz, Sartaj Sahni, Susan Anderson-Freed
 * Section 7.6 Merge Sort
 * Exercise 1 and 2(a)
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* Max number of elements on the input array */
#define MAX_ELEMS 16

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
     * source and destination indices in the array where an element has to be 
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
            source = destination - h;
            if(source < 0){
                /* rollover logic */
                source = n + source;
            }
            /* Now copy data from source to destination if source!=processing_
             * start_index
             */
            if(source != processing_start_index){
                memcpy((array + destination), (array + source), sizeof(struct data));
                destination = source;
            }
            /*
             * increment the number of elements that have been shifted
             */
            elems_shifted++;
        }while(source != processing_start_index);
        /* Now copy saved data to destination */
        memcpy((array + destination), save, sizeof(struct data));
    }
}

/*
 * merge_sorted_arrays()
 *                  merges two arrays that are already sorted, using O(n) copy
 *                  operations and O(1) space. This function can be utilized
 *                  in a merge sort algorithm, that uses O(1) space
 * @a1          :   first sorted array
 * @n1          :   length of the first sorted array
 * @a2          :   second sorted array
 * @n2          :   length of the second sorted array
 *
 * returns pointer to the final sorted array starting at the same memory loc
 * where the first sorted array has started
 *
 * Assumption 1 : first array is smaller than the second array
 * Assumption 2 : the arrays are located adjacent to each other in the system 
 *                  memory
 */
struct data * merge_sorted_arrays(struct data *a1, int n1,  \
                                    struct data *a2, int n2){
    int c1 = 0;
    int i2 = 0;
    /*
     * preserve the start of the first array
     */
    struct data *start = a1;
    /*
     * memory space to save the array elements
     */
    struct data *save = NULL;
    save = (struct data *)malloc(sizeof(struct data));
    if(save == NULL){
        printf("Unable to allocate memory\n");
        return start;
    }
    /*
     * run the comparison and switch-hop loop until one of the arrays has 
     * exhausted
     */
    while((c1 < n1) && (i2 < n2)){
        if(a1->key >= (a2 + i2)->key){
            /*
             * an element from the second array is smaller than an element
             * of the first array
             */
            i2++;
        }else{
            /*
             * an element from the first array is smaller than an element
             * of the second array.
             */
            /*
             * save the element from the second array and overwrite its
             * position by the element from the first array
             */
            memcpy(save, (a2 + i2), sizeof(struct data));
            memcpy((a2 + i2), a1, sizeof(struct data));
            /*
             * shift the first array by 'n1 - 1' positions
             */
            a1 = hop(a1, n1, n1 - 1);
            /*
             * overwrite the last element of first array with the first
             * element of the second array
             */
            memcpy((a1 + n1 - 1), a2, sizeof(struct data));
            /*
             * shift a sub section of second array by i2 positions. the
             * length of this sub section is 'i2 + 1'
             */
            a2 = hop(a2, i2 + 1, i2);
            /*
             * overwrite the 'i2'th index in the second array with the saved
             * element
             */
            memcpy((a2 + i2), save, sizeof(struct data));
            /*
             * increment the counter for # of elements of the first array
             * that have been processed in this code flow
             */
            c1++;
        }
    }
    /*
     * do a final shift, if all the elements of the first array were not
     * processes/moved in the else part of the above while code block
     *
     * during this shift we assume that the arrays are placed adjacent to 
     * each other in memory
     */
    if(c1 < n1){
        a1 = hop(a1, (n1 + n2), (n1 - c1));
    }
    /*
     * return the sorted array
     */
    return a1;
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
    printf("\n");
}

/*
 * generate_input_arrays()
 *                  creates two sorted arrays that are colocated in memory
 * @a           :   address of the array of type struct data
 * returns the index where the second array starts
 */
int generate_input_arrays(struct data *a){
    /*
     * get the size of input array
     */
    int n = sizeof(a)/sizeof(struct data);
    /*
     * get a random number that divides the array in two parts. divide 
     * rand() by n/2 just to avoid certain corner cases in array lengths
     */
    srand(time(NULL));
    int p = rand() % (n / 2);
    int x = 0;
    /*
     * populate the first array. elements have to be in sorted order
     */
    a->key = rand() % 10;
    for(x = 1; x < p; x++){
        (a + x)->key = (a + x -1)->key + (rand() % 10);
    }
    /*
     * populate the second array. elements have to be in sorted order
     */
    (a + p)->key = rand() % 10;
    for(x = (p + 1); x < n; x++){
        (a + x)->key = (a + x -1)->key + (rand() % 10);
    }
    return p;
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
     * generate input arrays
     */
    int p = generate_input_arrays(input);
    /* print the arrays before the sort */
    printf("Before sorting the arrays\n");
    printarray(input, (p - 1));
    printarray((input + p), (MAX_ELEMS - p));
    printf("partition: %d\n", p);
    /* call the merge sorted arrays function */
//    merge_sorted_arrays(input, p, (input + p), (MAX_ELEMS - p));
    /* print the arrays after the sort */
    printf("After sorting the arrays\n");
    printarray(input, (p - 1));
    printarray((input + p), (MAX_ELEMS - p));

}
