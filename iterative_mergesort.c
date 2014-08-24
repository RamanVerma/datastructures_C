/*
 * demonstartes merge sort in an iterative
 * implementation
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ELEM 8

/*
 * struct for the data type to be sorted
 */
struct data{
    int key;
};

/*
 * merge_sublist    merge sorts two sorted sublists that are adjecent to 
 *      each other in the system's memory
 * @s1      :       pointer to the firt element of first sublist
 * @n1      :       length of the first sublist
 * @s3      :       pointer to the first element of a list where the sorted 
 *                  elements will be copied to.
 */
void merge_sublist(struct data* s1, int n1, struct data* s3){
    /*find a mid point in the list to be processes*/
    struct data* s2 = (s1 + (n1 / 2));
    int i = 0;
    int j = 0;
    int k = 0;
    /*
     * fundamental merge sort operation
     * iterate through both sublists and copy the data to new sublist
     */
    while(i < (n1 / 2) && (j < (n1 / 2))){
        if((s1 + i)->key <= (s2 + j)->key){
            (s3 + k)->key = (s1 + i)->key;
            i++;
        }else{
            (s3 + k)->key = (s2 + j)->key;
            j++;
        }
        k++;
    }
    /*
     * Now just copy the remaining elements of the input sublists to the
     * new sublist
     */
    while(i < (n1 / 2)){
        (s3 + k)->key = (s1 + i)->key;
        i++;
        k++;
    }
    while(j < n1){
        (s3 + k)->key = (s2 + j)->key;
        j++;
        k++;
    }
}

/*
 * merge_sort       merge sort algorithm(iterative version)
 * @inputlist      :       list to be sorted
 * @n              :       length of the list to be sorted
 * @sortedlist     :       list where sorted elements will be copied
 * 
 * returns the address where sorted list is located
 */
struct data *merge_sort(struct data *inputlist, int n, struct data *sortedlist){
    /* no need to sort in this case */
    if(n < 2){
        return inputlist;
    }
    int offset = 0;
    /*
     * do iterative merge sort
     */
    int chunk = 2;
    while(chunk <= n){
        /*
         * FIXME This code will work properly only for cases when 
         * log base 2 (length_of_list) is a integer
         */
        offset = 0;
        while((offset * chunk) < n){
            merge_sublist(inputlist + (chunk * offset), chunk, sortedlist + (chunk * offset));
            offset++;
        }
        /*
         * FIXME Is this in efficient
         */
        memcpy((void *)inputlist, (void *)sortedlist, sizeof(struct data) * MAX_ELEM);
        chunk = chunk * 2;
    }
    return sortedlist;
}

/*
 * main function
 */
int main(){
    struct data *userlist = NULL;
    struct data *sortedlist = NULL;
    int i = 0;
    /* 
     * allocate memory for the input and output arrays 
     */
    userlist = (struct data *)malloc(sizeof(struct data) * MAX_ELEM);
    if(userlist == NULL){
        printf("Unable to allocate memory. Abort");
        return 1;
    }
    sortedlist = (struct data *)malloc(sizeof(struct data) * MAX_ELEM);
    if(sortedlist == NULL){
        printf("Unable to allocate memory. Abort");
        return 1;
    }
    /* 
     * accept user input 
     */
    printf("Enter %d integers as input\n", MAX_ELEM);
    for(i = 0; i < MAX_ELEM; i++){
        scanf("%d", &((userlist + i)->key));
    }
    /* 
     * call merge sort
     */
    merge_sort(userlist, MAX_ELEM, sortedlist);
    /*
     * print the output
     */
    for(i = 0;i < MAX_ELEM; i++){
        printf("%d\t", (sortedlist + i)->key);
    }
    printf("\n");
    return 0;
}
