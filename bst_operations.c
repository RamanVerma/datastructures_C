/*
 * bstree_operations demonstrates various traversal/search methods
 * for a binary search tree. 
 * the traversal code can be used for binary trees also. 
 * Just the add_node_to_bst function cannot be used for binary trees. 
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"fifoQueue.h"
#include"stack.h"

/* Num of elements to be added to the tree */
#define MAX_ELEMS 5

/*
 * node structure for the trees to be used in this code
 */
struct node{
    /* key for the node */
    int key;
    /* left and right children for the node */
    struct node *lchild;
    struct node *rchild;
};

/* root node for the tree */
struct node *root = NULL;

/*
 * generic function pointer for differnet kind of traversals
 */
int(*traverse)(struct node*, int *, int);

/*
 * printBTree() prints the binary tree
 * @r       root node of the binary tree
 *
 */
void printBTree(struct node *r){
    struct node *x = NULL;
    bool maybeDone = false;
    /* temp node to be used to print new line */
    struct node *newline = (struct node *)malloc(sizeof(struct node));
    if(newline == NULL){
        printf("failed to allocate memory\n");
        return;
    }
    newline->key = -1;
    /* initialize the FIFO queue */
    if(r != NULL){
        add_Q(r);
        add_Q(newline);
    }
    /* Execute the loop until queue is empied */
    while((x = remove_Q()) != NULL){
        /* found new line indicator */
        if(x->key == -1){
            /*
             * if maybeDone is true, we have found second successive new line
             * indicator
             */
            if(maybeDone)
                return;
            /*
             * print new line, 
             * push new line indicator,
             * set maybeDone flag to true
             */
            printf("\n");
            add_Q(newline);
            maybeDone = true;
            continue;
        }
        printf("%d\t", x->key);
        /* set maybeDone = false and push the children on queue, if any */
        maybeDone = false;
        if(x->lchild != NULL)
            add_Q(x->lchild);
        if(x->rchild != NULL)
            add_Q(x->rchild);

    }
}

/*
 * inorder_rec()    traverses a tree inorder, using recursive implementation
 * @stroot  root of the binary subtree to be traversed
 * @out     pointer to the int array that will contain keys for all the nodes
 *          visited
 * @index   index for the integer array, where next key will be saved
 *
 * returns int index for storing next element in the out array
 *
 * the function assumes that this pointer to int has sufficient memory 
 * allocated before it is passed to the function
 */
int inorder_rec(struct node *stroot, int *out, int index){
    /* process the left child, if any */
    if(stroot->lchild != NULL){
        index = inorder_rec(stroot->lchild, out, index);
    }
    /* process the current node */
    *(out + index) = stroot->key;
    index++;
    /* process the right child, if any */
    if(stroot->rchild != NULL){
        index = inorder_rec(stroot->rchild, out, index);
    }
    return index;
}

/*
 * inorder_itr()    traverses a tree inorder, using iterative implementation
 * @stroot  root of the binary subtree to be traversed
 * @out     pointer to the int array that will contain keys for all the nodes
 *          visited
 *
 * the function assumes that this pointer to int has sufficient memory 
 * allocated before it is passed to the function
 *
 * returns 0 on success and -1 on failure
 *
 * TODO remove the 0 to be passed as the third arg. it is there just to maintain
 * common signature across traverse functions.
 * FIXME enless loop !!!
 */
int inorder_itr(struct node *stroot, int *out, int a){
    /* empty sub tree */
    if(stroot == NULL){
        return -1;
    }
    struct node *x = NULL;
    struct node *lcvisited = NULL;
    /* push subtree root to the stack */
    x = stroot;
    do{
        /* push all nodes on stack till they have lchild */
        for(;(x->lchild != NULL) && (x != lcvisited);x = x->lchild){
            push_st(x);
        }
        /* process the last node that wasn't pushed on stack */
        printf("%d\t",x->key);
        /* 
         * lcvisited = (top node of stack), if x == (top of stack)->lchild
         * so that we do not trace the lchildren for this node again.
         */
        if((top_st() != NULL) && (x == ((struct node *)top_st())->lchild)){
            lcvisited = (struct node *)top_st();
        }
        /* push its right child on stack */
        if(x->rchild != NULL){
            push_st(x->rchild);
        }
    }while((x = (struct node *)pop_st()) != NULL);
    return 0;
}

/*
 * breadth_first_search()   performs bredth firt search on the tree
 * @stroot      :   root of the binary sub tree to be searched
 * @key         :   key to be searched
 *
 * returns the pointer to data, or NULL if key is not found or error
 */
struct node *breadth_first_search(struct node *stroot, int key){
    struct node *x = NULL;
    if(stroot == NULL){
        return x;
    }
    /* add the sub tree root to the fifo queue */
    add_Q(stroot);
    /* process all the nodes in the sub tree breadth wise */
    while((x = remove_Q()) != NULL){
        /* break, if key is found */
        if(x->key == key){
            break;
        }
        add_Q(x->lchild);
        add_Q(x->rchild);
    }
    return x;
}

/*
 * addNodeToBst()   adds a node to a binary search tree
 * @n       new node to be added to the bst
 *
 * returns void
 */
void addNodeToBst(struct node *n){
    /* empty tree */
    if(root == NULL){
        root = n;
        return;
    }
    struct node *subtreeRoot = root;
    while(1){
        /* duplicate key */
        if(n->key == subtreeRoot->key)
            break;
        /* new node has key lesser than the root */
        if(n->key < subtreeRoot->key){
            if(subtreeRoot->lchild == NULL){
                subtreeRoot->lchild = n;
                break;
            }else{
                subtreeRoot = subtreeRoot->lchild;
                continue;
            }
        }
        /* new node has key greater than the root */
        if(n->key > subtreeRoot->key){
            if(subtreeRoot->rchild == NULL){
                subtreeRoot->rchild = n;
                break;
            }else{
                subtreeRoot = subtreeRoot->rchild;
                continue;
            }
        }
    }
}

/*
 * printMenu()  prints a menu for user to choose among various traversal 
 *              techniques
 */
void printMenu(){
    printf("Choose a number between 0 and 6, to select the traversal technique "
           "and implementation\n");
    printf("0. exit\n");
    printf("1. inorder (recursive implementation)\n");
    printf("2. inorder (iterative implementation)\n");
    printf("3. preorder (recursive implementation)\n");
    printf("4. preorder (iterative implementation)\n");
    printf("5. postorder (recursive implementation)\n");
    printf("6. postorder (iterative implementation)\n");
    printf("7. breadth first search\n");
    printf("8. compare binary trees\n");
}

/*
 * main function
 */
void main(){
    struct node *n = NULL;
    int *out = NULL;
    int num;
    int option;
    srand(time(NULL));
    int key = -1;
    /*
     * create a tree
     */
    int x = 0;
    for(x = 0;x < MAX_ELEMS; x++){
        /*
         * allocate memory to the node structure
         */
        n = (struct node *)malloc(sizeof(struct node));
        if(n == NULL){
            printf("failed to allocate memory\n");
            return;
        }
        /*
         * generate a random key and initialize the left and right children
         */
        n->key = rand() % 100;
        n->lchild = NULL;
        n->rchild = NULL;
        addNodeToBst(n);
    }
    /* print the BTree */
    printBTree(root);
    /*
     * select the kind of traversal, or search method to be used
     */
    while(1){
        printMenu();
        scanf("%i", &option);
        if(option == 0)
            return;
        else if(option >=1 && option <=8)
            break;
    }
    /*
     * allocate memory for the int array of size equal to the num of nodes
     * in the tree
     */
    out = (int *)malloc(sizeof(int) * MAX_ELEMS);
    if(out == NULL){
            printf("failed to allocate memory\n");
            return;
    }
    /*
     * now hook into the correct kind of traversal function and call it
     */
    switch (option){
        case 1: 
                traverse = inorder_rec;
                break;
        case 2: 
                traverse = inorder_itr;
                break;
        case 7:
                printf("Type in the integer key to be searched\n");
                scanf("%d",&key);
                n = breadth_first_search(root, key);
                if(n != NULL)
                    printf("%d\n",n->key);
                else
                    printf("Not found");
                break;
        case 8: 
                break;
        default:
                return;
    }
    /* if the user had selected traverse operations */
    if(option >= 1 && option <= 6){
        num = traverse(root, out, 0);
        /*
         * print the output
         * if we traverse the loop to MAX_ELEMS, we may print garbage to the
         * end because MAX_ELEMS is the maximum possible elements that can be
         * stored in the array. The array will have less number of elements,
         * in case duplicate number was generated by random int key generation
         */
        for(x = 0;x < num; x++){
            printf("%i\t", *(out + x));
        }
    }
    printf("\n");
    return;
}
