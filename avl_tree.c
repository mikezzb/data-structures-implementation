#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
} TreeNode;

typedef struct avl {
    struct TreeNode* root;
} avl;

int max(int a, int b){
    return (a > b) ? a : b;
}

int height(TreeNode *n){
    return n == NULL ? 0 : n->height;
}

TreeNode* initTreeNode(int val){
    TreeNode *n = (TreeNode*)malloc(sizeof(TreeNode));
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

avl* initAVL(int val){
    avl *n = (avl*)malloc(sizeof(avl));
    n->root = initTreeNode(val);
    return n;
}

void updateHeight(TreeNode* n){
    n->height = max(height(n->left), height(n->right)) + 1;
}

TreeNode* rotateLeft(TreeNode *n){
    TreeNode* k = n->right;
    n->right = k->left;
    k->left = n;

    updateHeight(n);
    updateHeight(k);
    return k;
}

TreeNode* rotateRight(TreeNode *n){
    TreeNode* k = n->left;
    n->left = k->right;
    k->right = n;

    updateHeight(n);
    updateHeight(k);
    return k;
}

TreeNode* doubleRotateLeft(TreeNode *n){
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

TreeNode* doubleRotateRight(TreeNode *n){
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

TreeNode* balance(TreeNode *n, int val, avl *a){
    if(n == NULL)
        return n;
    int balancingFactor = height(n->left) - height(n->right);
    if(balancingFactor == 2){
        if(val < n->left->val)
            n = rotateRight(n); // LL
        else
            n = doubleRotateLeft(n); // LR
    } else if(balancingFactor == -2){
        if(val > n->right->val)
            n = rotateLeft(n); // RR
        else
            n = doubleRotateRight(n); // RL
    }
    a->root = n;
    return n;
}

TreeNode* insert(TreeNode *n, int val, avl *a){
    if(n == NULL){
        n = initTreeNode(val);
    }
    else if(val < n->val){
        n->left = insert(n->left, val, a);
    }
    else if(val > n->val){
        n->right = insert(n->right, val, a);
    }
    updateHeight(n);
    return balance(n, val, a);
}

void preorder(TreeNode *n){
    if(n != NULL){
        printf("%d ", n->val);
        preorder(n->left);
        preorder(n->right);
    }
}

int main(void) {
    avl *n = initAVL(10);

    /* Constructing tree given in the above figure */
    insert(n->root, 20, n);
    insert(n->root, 30, n);
    insert(n->root, 40, n);
    insert(n->root, 50, n);
    insert(n->root, 25, n);

    /* The constructed AVL Tree would be
            30
            /  \
            20   40
        /  \     \
        10  25    50
    */

    printf("Preorder traversal of the constructed AVL"
            " tree is \n");
    preorder(n->root);
    putchar('\n');

    return 0;
}
