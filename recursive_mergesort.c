/*
 * demonstartes merge sort in an recursive
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
void merge_sort(struct data* s1, int n1, struct data* s3){
    /* no need to sort in this case */
    if(n1 < 2){
        return;
    }
    /*find a mid point in the list to be processes*/
    struct data* s2 = (s1 + (n1 / 2));
    /*
     * make recursive calls for the left part of sublist 
     */
    merge_sort(s1, (n1 / 2), s3);
    /* 
     * process the right part of the sublist
     */
    merge_sort(s1 + (n1 / 2), (n1 / 2), s3 + (n1 / 2));
    /* 
     * process the subarray changed in the previous 
     * recursive calls
     */
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
    /*
     * copy the sorted data to the orginal list, because it will 
     * be used in later merge_sort calls when resursion unwinds
     */
    memcpy((void *)s1, (void *)s3, sizeof(struct data) * n1);
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
