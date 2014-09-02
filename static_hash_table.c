/*
 * demonstartes a static hash table with the following operations possible:
 * add a new entry
 * delete an entry
 * search an entry
 * modify the key for an entry
 * modify the attributes for an entry
 *
 * this hash table employs chaining strategy for overflow management
 *
 * For full problem statement, please refer:
 * Fundamentals of Data Structures in C
 * Ellis Horowitz, Sartaj Sahni, Susan Anderson-Freed
 * Section 8.2 Static Hashing
 * Exercise 13
 */

#include<stdio.h>
#include<string.h>

/*
 * max number of buckets in the table
 */
#define MAX_BUCKETS 50
/* length of the key */
#define KEY_LEN 5
/* constants */
#define DESCRIPTION "description"
#define REORDERLEVEL "reorderlevel"
#define INVENTORY "inventory"

/* function pointer to the hash function to be used */
int(*hash)(int);

/* structure for the key value pair to be entered in the hash table */
struct data{
    /* key for the table */
    int key;
    char description[10];
    int reorderlevel;
    int inventory;
};

/*
 * bucket of the hash table(with chaining for overflow)
 */
struct bucket{
    struct data *d;
    struct bucket *nextslot;
};

/*
 * divisor()    hash function that uses the remainder to get to the hash value
 * @key     :   int key for the hash table entry
 *
 * returns integer, as the location where the entry can be stored
 */
int divisor(int key){
    return (key % MAX_BUCKETS);
}

/*
 * definition of the hash table
 */
struct bucket ht[MAX_BUCKETS];

/*
 * init()       initialize hash table
 * @table   :   first entry of the table
 * @n       :   length of the table
 *
 * sets the relevant pointers to NULL
 */
void init(struct bucket *table, int n){
    int index = 0;
    for(index = 0; index < n; index++){
        (table + index)->d = NULL;
        (table + index)->nextslot = NULL;
    }
    return;
}

/*
 * add()        adds an entry to the hash table
 * @entry   :   entry to be added
 * @table   :   hash table to which this entry has to be added
 *
 * returns 0 for success, -1 if the entry already exists and -2 on other err
 */
int add(struct data *entry, struct bucket *table){
    int hashvalue = 0;
    struct bucket *b = NULL;
    /*
     * check for invalid data
     */
    if(entry == NULL || table == NULL){
        printf("Invalid input data for add operation\n");
        return -2;
    }
    /*
     * get the hash value and reach the bucket where entry has to be inserted
     */
    hashvalue = hash(entry->key);
    b = (table + hashvalue);
    /*
     * check if the the entry is present already in the hash table, else add
     * it to the end
     */
    while(b->d != NULL){
        if(b->d->key == entry->key)
            return -1;
        b = b->nextslot;
    }
    b->d = entry;
    return 0;
}

/*
 * delete()     deletes an entry from the hash table
 * @key     :   key of the entry to be deleted from the table
 * @table   :   hash table from which the entry has to be deleted
 *
 * returns pointer to the slot on success, NULL if the entry is not found
 */
struct bucket *delete(int key, struct bucket *table){
    int hashvalue = hash(key);
    struct bucket *b = NULL;
    struct bucket *p = NULL;
    b = (table + hashvalue);
    /*
     * check if this bucket was empty
     */
    if(b->d == NULL){
        return NULL;
    }else if(b->d->key == key){
        (table + hashvalue)->nextslot = b->nextslot;
        return b;
    }
    /*
     * keep tab on the prev bucket slot and keep moving through the link until
     * you find the one with the key
     */
    while(b->d->key != key){
        p = b;
        b = b->nextslot;
        /*
         * reached end of the list
         */
        if(b == NULL)
            return b;
    }
    /*
     * found the entry, rewire the links and return 0 
     */
    p->nextslot = b->nextslot;
    return b;
}

/*
 * search()     searches for an entry in the hash table
 * @key     :   key of the entry to be searched
 * @table   :   table to be searched
 *
 * returns a pointer to the entry, if found, else returns a NULL pointer
 */
struct data *search(int key, struct bucket *table){
    int hashvalue = hash(key);
    struct bucket *b = NULL;
    struct data *ptr = NULL;
    b = (table + hashvalue);
    /*
     * check if this bucket was empty
     */
    if(b->d == NULL){
        return ptr;
    }
    /*
     * search for the entry in the proper bucket
     */
    while(b != NULL){
        if(b->d->key == key){
            ptr = b->d;
            break;
        }else{
            b = b->nextslot;
        }
    }
    return ptr;
}

/*
 * editkey()    edits the key for an entry in the hash table
 * @keyold  :   old value of the key
 * @table   :   pointer to the table where the entry resides
 * @keynew  :   new value of the key
 *
 * returns 0 on success and -1, if the oldkey is not found in the table
 */
int editkey(int keyold, struct bucket *table, int keynew){
    struct bucket *b = NULL;
    /*
     * delete the old key from the table
     */
    b = delete(keyold, table);
    /*
     * old key not found in the table
     */
    if(b == NULL)
        return -1;
    /*
     * change the key and add the entry back to the table
     */
    b->d->key = keynew;
    return (add(b->d, table));
}

/*
 * editattr()   edits an attribute of an entry in the hash table
 * @key     :   key of the entry whose attribute has to be changed
 * @table   :   pointer to the table where the entry resides
 * @attr    :   attribute to be edited
 * @value   :   new value for the attribute
 *
 * returns 0 , on success and -1, if the emtry os not found in the hash table.
 *      -2 in case of invalid data
 */
int editattr(int key, struct bucket *table, char *attr, char *value){
    struct data *ptr = NULL;
    /* invalid data */
    if(attr == NULL){
        return -2;
    }
    /* search the table for the key */
    ptr = search(key, table);
    /* key is not found */
    if(ptr == NULL){
        return -1;
    }
    /* check what attribute is to be edited */
    if(strcmp(attr, DESCRIPTION) == 0){
        /* edit description */
        strncpy(ptr->description, value, sizeof(char) * 10); 
    }else if(strcmp(attr, REORDERLEVEL) == 0){
        /* edit reorder level */
        if(!isdigit(value))
            return -2;
        ptr->reorderlevel = atoi(value);
    }else if(strcmp(attr, INVENTORY) == 0){
        /* edit inventory */
        if(!isdigit(value))
            return -2;
        ptr->inventory = atoi(value);
    }else{
        /* wrong attribute */
        return -2;
    }
    return 0;
}

/*
 * main function
 */
void main(){
}
