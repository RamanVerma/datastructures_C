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
#include<string.h>

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
struct node *root2 = NULL;

/* denotes the top element of the stack */
struct st_element *top;
struct st_element *top2;

/*
 * generic function pointer for differnet kind of traversals
 */
int(*traverse)(struct node*, int *, int);

/*
 * printBSTree() prints the binary tree
 * @r       root node of the binary tree
 *
 */
void printBSTree(struct node *r){
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
            push_st(top, x);
        }
        /* process the last node that wasn't pushed on stack */
        printf("%d\t",x->key);
        /* 
         * lcvisited = (top node of stack), if x == (top of stack)->lchild
         * so that we do not trace the lchildren for this node again.
         */
        if((top_st(top) != NULL) && (x == ((struct node *)top_st(top))->lchild)){
            lcvisited = (struct node *)top_st(top);
        }
        /* push its right child on stack */
        if(x->rchild != NULL){
            push_st(top, x->rchild);
        }
    }while((x = (struct node *)pop_st(top)) != NULL);
    return 0;
}

/*
 * postorder_rec()    traverses a tree postorder, using recursive implem
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
int postorder_rec(struct node *stroot, int *out, int index){
    /* process the left child */
    if(stroot->lchild != NULL){
        index = postorder_rec(stroot->lchild, out, index);
    }
    /* process the right child */
    if(stroot->rchild != NULL){
        index = postorder_rec(stroot->rchild, out, index);
    }
    /* process self */
    *(out + index++) = stroot->key;
    return index;
}

/*
 * postorder_itr()    traverses a tree postorder, using iterative implem
 * @stroot  root of the binary subtree to be traversed
 * @out     pointer to the int array that will contain keys for all the nodes
 *          visited
 *
 * the function assumes that this pointer to int has sufficient memory 
 * allocated before it is passed to the function
 *
 * returns length of output array
 *
 * TODO remove the 0 to be passed as the third arg. it is there just to maintain
 * common signature across traverse functions.
 */
int postorder_itr(struct node *stroot, int *out, int a){
    int x = 0;
    struct node *lvnode = NULL;
    /* push the root element to the stack */
    push_st(top, (void *)stroot);
    /* loop while the stack is not empty */
    while(top_st(top) != NULL){
        /* look at the top element of stack and process it as subtree root */
        stroot = top_st(top);
        /* 
         * push the left node on stack, if it is not null AND it is not the 
         * last node visited AND the last node visited is not the right child 
         * of this node
         */
        if(stroot->lchild != NULL && stroot->lchild != lvnode && 
            stroot->rchild != lvnode){
            push_st(top, (void *)stroot->lchild);
            continue;
        }
        /* 
         * push the right node on stack, if it is not null AND it is not the
         * last node visited
         */
        if(stroot->rchild != NULL && stroot->rchild != lvnode){
            push_st(top, (void *)stroot->rchild);
            continue;
        }
        /* set the top node as the last visited node now */
        lvnode = stroot;
        /* no child of this node, so pop it and process */
        *(out + x) = *((int *)pop_st(top));
        x++;
    }
    return x;
}

/*
 * preorder_rec()    traverses a tree preorder, using recursive implem
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
int preorder_rec(struct node *stroot, int *out, int a){
    /* process the root node */
    *(out + a++) = stroot->key;
    /* process the left child, if it exists */
    if(stroot->lchild != NULL)
        a = preorder_rec(stroot->lchild, out, a);
    /* process the right child, if it exists */
    if(stroot->rchild != NULL)
        a = preorder_rec(stroot->rchild, out, a);
    return a;
}

/*
 * preorder_itr()    traverses a tree preorder, using iterative implem
 * @stroot  root of the binary subtree to be traversed
 * @out     pointer to the int array that will contain keys for all the nodes
 *          visited
 *
 * the function assumes that this pointer to int has sufficient memory 
 * allocated before it is passed to the function
 *
 * returns length of output array
 *
 * TODO remove the 0 to be passed as the third arg. it is there just to maintain
 * common signature across traverse functions.
 */
int preorder_itr(struct node *stroot, int *out, int a){
    a = 0;
    struct node *n = NULL;
    /* checking the corner case when subroot is NULL */
    if(stroot == NULL)
        return 0;
    /* initialize the stack */
    push_st(top, (void *)stroot);
    /* process the entries in the stack, till it gets empty */
    while((n = (struct node *)pop_st(top)) != NULL){
        /* add the key to output array */
        *(out + a++) = n->key;
        /* push the current root's children to the stack, if they exist */
        if(n->rchild != NULL)
            push_st(top, (void *)n->rchild);
        if(n->lchild != NULL)
            push_st(top, (void *)n->lchild);
    }    
    return a;
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
 * depth_first_search()   performs depth first search on the tree
 * @stroot      :   root of the binary sub tree to be searched
 * @key         :   key to be searched
 *
 * depth first search is very similar to preorder traversal. The only
 * difference being that we traverse till a value is not found. Depth
 * first search is essentially a tree traversal where we travel from
 * root to the leaves down a single path at a time, and then cover the
 * next untraversed path closely similar to the current one.
 * So, it translates into a pre/in/post order traversal. preorder
 * traversal will be the most efficient because we compare a node while
 * we are at it, and can avoid un necessary traversals.
 *
 * returns the pointer to data, or NULL if key is not found or error
 */
struct node *depth_first_search(struct node *stroot, int key){
    /* what if root is NULL */
    if(stroot == NULL)
        return NULL;
    struct node *n = NULL;
    struct node *m = NULL;
    /* push the rot on the stack */
    push_st(top, (void *)stroot);
    /* run through this loop till the stack is empty */
    while((n = (struct node *)pop_st(top)) != NULL){
        /* if key is found, exit the loop */
        if (n->key == key){
            m = n;
            break;
        }
        /* push the current root's children to the stack, if they exist */
        if(n->rchild != NULL)
            push_st(top, (void *)n->rchild);
        if(n->lchild != NULL)
            push_st(top, (void *)n->lchild);
    }
    return m;
}

/*
 * compareTrees()   compares two trees, given their root nodes
 * @stroot1     :   root of the first subtree
 * @stroot2     :   root of the second subtree
 *
 * two subtrees are considered similar if they produce same 
 * result on preorder traversal
 *
 * returns 0 if the trees are similar, 1 otherwise
 */
int compareTrees(struct node *stroot1, struct node *stroot2){
    /* cases when one or both root nodes are NULL */
    if(stroot1 == NULL && stroot2 == NULL)
        return 0;
    if((stroot1 == NULL && stroot2 != NULL) || (stroot1 != NULL && stroot2 == NULL))
        return 1;
    /* both the roots nodes are NOT NULL */
    struct node *n = NULL;
    struct node *m = NULL;
    /* compare the root nodes and push them on respective stacks, if equal */
    if(stroot1->key != stroot2->key){
        return 1;
    } else {
        push_st(top, (void *)stroot1);
        push_st(top2, (void *)stroot2);
    }
    /* process each node of both the trees, while traversing them */
    while(1){
        n = pop_st(top);
        m = pop_st(top2);
        /* nodes from both the stacks are NULL, stacks empty */
        if(n == NULL && m == NULL)
            return 0;
        /* node from one of the stacks os NULL, mismatch */
        if((n == NULL && m != NULL) || (n != NULL && m == NULL))
            return 1;
        /* keys dont match */
        if(n->key != m->key)
            return 1;
        /* push the current root's children to the stack, if they exist */
        if(n->rchild != NULL)
            push_st(top, (void *)n->rchild);
        if(n->lchild != NULL)
            push_st(top, (void *)n->lchild);
        if(m->rchild != NULL)
            push_st(top2, (void *)m->rchild);
        if(m->lchild != NULL)
            push_st(top2, (void *)m->lchild);
    }
}

/*
 * copyBSTree()     makes a copy of the BSTree
 * @root        :   root node of the binary search tree to be copied
 *
 * returns the root node of the copy
 */
struct node *copyBSTree(struct node *root){
    /* condition for recursion to unwind */
    if(root == NULL)
        return NULL;
    /* allocate memory for a new node */
    struct node *copy = (struct node *)malloc(sizeof(struct node));
    if(copy == NULL){
        printf("No memory. Will exit\n");
        return NULL;
    }
    /* process the left child recursively */
    copy->lchild = copyBSTree(root->lchild);
    /* process the right child recursively */
    copy->rchild = copyBSTree(root->rchild);
    /* copy the data */
    memcpy(&copy->key, &root->key, sizeof(root->key));
    return copy;
}

/*
 * addNodeToBst()   adds a node to a binary search tree
 * @root     root node of the tree
 * @n       new node to be added to the bst
 *
 * returns pointer to the root of the tree
 */
struct node *addNodeToBst(struct node *root, struct node *n){
    /* empty tree */
    if(root == NULL){
        root = n;
        return root;
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
    return root;
}

/*
 * printMenu()  prints a menu for user to choose among various traversal 
 *              techniques
 */
void printMenu(){
    printf("=============================================\n");
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
    printf("8. depth first search\n");
    printf("9. compare binary trees\n");
    printf("10. copy a tree\n");
}

/*
 * makeBSTree()   make a binary search tree
 * @root    :   pointer to the root node
 *
 * returns a pointer to the root node, or NULL in case of an error
 */
struct node *makeBSTree(struct node *r){
    struct node *n = NULL;
    int x = 0;
    for(x = 0;x < MAX_ELEMS; x++){
        /*
         * allocate memory to the node structure
         */
        n = (struct node *)malloc(sizeof(struct node));
        if(n == NULL){
            printf("failed to allocate memory\n");
            return NULL;
        }
        /*
         * generate a random key and initialize the left and right children
         */
        n->key = rand() % 100;
        n->lchild = NULL;
        n->rchild = NULL;
        r = addNodeToBst(r, n);
    }
    return r;
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
    int toss = 0;
    int x = 0;
    /*
     * create a tree
     */
    root = makeBSTree(root);
    printf("=============================================\n");
    printf("------------------Working tree---------------\n");
    /* print the BTree */
    printBSTree(root);
    /*
     * select the kind of traversal, or search method to be used
     */
    while(1){
        printMenu();
        scanf("%i", &option);
        if(option == 0)
            return;
        else if(option >= 1 && option <= 10)
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
    printf("=============================================\n");
    /*
     * now hook into the correct kind of traversal function and call it
     */
    switch (option){
        /* inorder traversal - recursive */
        case 1: 
                traverse = inorder_rec;
                break;
        /* inorder traversal - iterative */
        case 2: 
                traverse = inorder_itr;
                break;
        /* preorder traversal - recursive */
        case 3: 
                traverse = preorder_rec;
                break;
        /* preorder traversal - iterative */
        case 4: 
                traverse = preorder_itr;
                break;
        /* postorder traversal - recursive */
        case 5: 
                traverse = postorder_rec;
                break;
        /* postorder traversal - iterative */
        case 6: 
                traverse = postorder_itr;
                break;
        /* Breadth First Search */
        case 7:
                printf("Type in the integer key to be searched\n");
                scanf("%d",&key);
                n = breadth_first_search(root, key);
                if(n != NULL)
                    printf("%d\n",n->key);
                else
                    printf("Not found");
                break;
        /* Depth First Search */
        case 8: 
                printf("Type in the integer key to be searched\n");
                scanf("%d",&key);
                n = depth_first_search(root, key);
                if(n != NULL)
                    printf("%d\n",n->key);
                else
                    printf("Not found");
                break;
        /* Compare two trees */
        case 9: 
                /* toss : 0 = make similar tree, 1 = make new tree */
                toss = rand() % 2;
                root2 = ((toss == 0) ? root : makeBSTree(root2));
                /* Print the second tree */
                printf("Here's the second BSTree\n");
                printBSTree(root2);
                /* do the comparison and print the result as a statement */
                printf("Trees are %s similar\n", (compareTrees(root, root2) == 0 ) ? "" : "NOT" );
                break;
        /* Copy a tree */
        case 10:
                root2 = copyBSTree(root);
                printf("Here's the copied bstree\n");
                printBSTree(root2);
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
