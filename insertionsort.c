/*
 * demonstrates insertion sort
 * comparison function can be customized and 
 * passed as an argument
 */

#include<stdio.h>
#include<stdbool.h>

/*max number of elements in the array*/
#define MAX_ELEM 5

/*
 * function prototypes
 */
bool(*compare)(int, int);
bool compare_ascending(int, int);
bool compare_descending(int, int);
int insertionSort(int *, int, bool(*)(int, int));

/*
 * compare_ascending()  compares two integers and returns
 *  true if the first argument < second argument
 *  @x  :   integer argument to be compared
 *  @y  :   integer argument to be compared against
 *
 *  returns true: when x < y, false otherwise
 */
bool compare_ascending(int x, int y){
    return ((x < y) ? true: false);
}

/*
 * compare_descending()  compares two integers and returns
 *  true if the first argument > second argument
 *  @x  :   integer argument to be compared
 *  @y  :   integer argument to be compared against
 *
 *  returns true: when x > y, false otherwise
 */
bool compare_descending(int x, int y){
    return ((x > y) ? true: false);
}

/*
 * insertionsort()  sorts an array of integers
 * @array   : pointer to the integer array to be sorted
 * @n       : number of elements in the array
 * @fptr    : pointer to the comparison function
 *
 * employs insertion sort for sorting
 * returns 0 upon success
 */
int insertionSort(int *array, int n, bool(*fptr)(int, int)){
    /*array already sorted*/
    if(n < 2)
        return 0;
    int i = 0;
    int j = 0;
    int element = 0;
    /*out loop to iterate over all the elements to be inserted*/
    for(i = 1; i <= (n - 1); i++){
        element = *(array + i);
        /*inner loop to compare and shift elements*/
        for(j = (i - 1); j >= 0; j--){
            if(fptr(element, *(array + j))){
                /*condition for shifting*/
                *(array + j + 1) = *(array + j);
            }else{
                /*found the right position for this element*/
                *(array + j + 1) = element;
                break;
            }
        }
        /*insert the element at the start of the array*/
        if(j < 0){
            *(array) = element;
        }
    }
    return 0;
}

/*
 * main funciton
 */
void main(){
    int array[MAX_ELEM] = {0};
    int i = 0;
    /*get user input*/
    printf("Enter %ld values, separated by spaces\n", sizeof(array)/sizeof(array[0]));
    for(i = 0; i < sizeof(array)/sizeof(array[0]); i++){
        scanf("%d", &array[i]);
    }
    compare = compare_ascending;
    /*call insertion sort*/
    insertionSort(array, sizeof(array)/sizeof(array[0]), compare);
    /*print output*/
    for(i = 0; i < sizeof(array)/sizeof(array[0]); i++){
        printf("%d\t", array[i]);
    }
    printf("\n");
}
