/*
 * demonstartes merge sort in an iterative
 * implementation
 */

#include<stdio.h>

/*
 * struct for the data type to be sorted
 */
struct data{
    int key;
};

/*
 * merge_sublist    merge sorts two sublists
 * @s1      :       pointer to the firt element of first sublist
 * @n1      :       length of the first sublist
 * @s3      :       pointer to the first element of a list where the sorted 
 *                  elements will be copied to.
 */

void merge_sublist(struct data* s1, int n1, struct data* s3){
    /*find a mid point in the list to be processes*/
    struct data* s2 = (s1 + ((n1 / 2) + 1));
    int i = 0;
    int j = 0;
    int k = 0;
    /*
     * fundamental merge sort operation
     */
    while(i <= (n1 / 2) && (j < n1)){
        if((s1 + i)->key <= (s2 + j)->key){
            (s3 + k)->key = (s1 + i)->key;
            i++;
        }else{
            (s3 + k)->key = (s2 + j)->key;
            j++;
        }
        k++;
    }
    while(i <= (n1 / 2)){
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
 * main function
 */
void main(){
}
