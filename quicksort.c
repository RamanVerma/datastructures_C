/*
 * demostrates quick sort alogorithm
 * pivot is selected with the median of three
 * formula, i.e median(left , middle, right)
 */

#include<stdio.h>

/*max length of array*/
#define MAX_ELEM 5

/*
 * get_median_of_three()    gets the median of three
 * integer values
 * @array:  pointer to the array that contains data
 * @a   :   index value
 * @b   :   index value
 * @c   :   index value
 *
 * returns the median value
 */
int get_median_of_three(int *array, int a, int b, int c){
    if(*(array + a) > *(array + b) && *(array + a) < *(array + c))
        return a;
    else if(*(array + b) > *(array + a) && *(array + b) < *(array + c))
        return b;
    else
        return c;
}

/*
 * swap()   swaps the elements at two locations in an
 * array
 * @array   :   pointer to the integer array in question
 * @p1      :   interger index1 for first element
 * @p2      :   interger index1 for first element
 */
void swap(int *array, int p1, int p2){
    int temp = *(array + p1);
    *(array + p1) = *(array + p2);
    *(array + p2) = temp;
    return;
}

/*
 * get_partition()  helper function for quickSort
 * @array   :   pointer to an integer array
 * @pivot   :   pivot position in the array
 * @begin   :   beginning index in the array
 * @end     :   ending index in the array
 *
 * returns the sorted position for the pivot value 
 */
int get_partition(int *array, int pivot, int begin, int end){
    int pivotvalue = *(array + pivot);
    int i = begin;
    int j = end;
    /*loop to find sorted position for the vale at the pivot*/
    while(i < j){
        /*move index i up until a value >= pivot value is found*/
        while((*(array + i) < pivotvalue) && (i < j)){
            i++;
        }
        /*move index j until a value < than the pivot value*/
        while((*(array + j) >= pivotvalue) && (j > (i - 1))){
            j--;
        }
        /*swap value at indices i and j*/
        if(i < j)
            swap(array, i, j);
    }
    if(j < 0)
        j = 0;
    /*put pivot value at index j*/
    swap(array, pivot, j);
    return j;
}

/*
 * quickSort()  sorts an array of integers using quick
 * sort algorithm
 * @array   :   pointer to the array to be sorted
 * @n       :   length of the array
 *
 */
void quickSort(int *array, int n){
    /*array size less than 2*/
    if(n < 2)
        return;
    int pivot = 0;
    int middle = n / 2;
    int start = 0;
    int end = 0;
    int partition = 0;
    /*stack for iterative processing of quick sort*/
    int stack[n];
    int top = -1;
    /*initialize the stack*/
    stack[++top] = 0;
    stack[++top] = (n - 1);
    do{
        /*pop end and start point for the array*/
        end = stack[top--];
        start = stack[top--];
        /*find the pivot key for the array*/
        pivot = get_median_of_three(array, start, middle, end);
        /*get the sorted position for the value at the pivot*/
        partition = get_partition(array, pivot, start, end);
        /*push the left sub array on stack if its len > 1*/
        if(((partition  - 1) - start) > 1){
            stack[++top] = start;
            stack[++top] = partition - 1;
        }
        /*push the right sub array on stack if its len > 1*/
        if((end - (partition + 1)) > 1){
            stack[++top] = partition + 1;
            stack[++top] = end;
        }
    }while(top > 0);
}

/*
 * main function
 */
void main(){
    int array[MAX_ELEM] = {0};
    int i = 0;
    /*get user input*/
    printf("Enter %ld values, separated by spaces\n", sizeof(array)/sizeof(array[0]));
    for(i = 0; i < sizeof(array)/sizeof(array[0]); i++){
        scanf("%d", &array[i]);
    }
    /*call the sorting algorithm*/
    quickSort(array, MAX_ELEM);    
    /*print output*/
    for(i = 0; i < sizeof(array)/sizeof(array[0]); i++){
        printf("%d\t", array[i]);
    }
    printf("\n");
}
