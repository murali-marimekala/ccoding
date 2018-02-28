#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

int isBSTUtil(struct node* node, int min, int max)
{
    //Check base case and return true
    if(node == NULL)
        return 1;

    //Make sure node data is not less than min and gerater than maximum
    //If so return false     
    if(node->data < min || node->data > max)
        return 0;

    return isBSTUtil(node->left,min,node->data-1) && isBSTUtil(node->right,node->data+1,max);
}

int isBST(struct node *node)
{
    return(isBSTUtil(node,INT_MIN,INT_MAX));
}

struct node* newNode(int data)
{
    struct node* node=(struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

int main()
{
    struct node* root = newNode(4);
    root->left = newNode(2);
    root->right = newNode(5);
    root->left->left = newNode(1);
    root->left->right = newNode(3);

    if(isBST(root))
        printf("Is a BST\n");
    else
        printf("Is not a BST\n");
    return 0;
}
