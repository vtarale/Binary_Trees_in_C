#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    struct node *parent;
    struct node *left;
    struct node *right;
};

void insert(struct node **, int);
void delete(struct node **, int);
void inorder(struct node *);
void display(struct node *);
void del_inorder(struct node *);
void _destruct(struct node *);
void destruct(struct node **);

struct node *max = NULL;

int main(void){
    struct node *tree;
    tree = NULL;
    insert(&tree, 6);
    display(tree);
    insert(&tree, 9);
    display(tree);
    insert(&tree, 10);
    display(tree);
    insert(&tree, 5);
    display(tree);
    delete(&tree, 9);
    display(tree);
    destruct(&tree);
}

void insert(struct node **root, int val){
    struct node *newnode;
    newnode = malloc(sizeof(struct node));
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    if(*root == NULL){
        *root = newnode;
        (*root)->parent = NULL;
        return;
    }
    struct node *temp;
    struct node *old;
    temp = *root;
    while(temp != NULL){
        old = temp;
        if(val < temp->val){temp = temp->left;}
        else{temp = temp->right;}
    }
    if(val < old->val){
        old->left = newnode;
        old->left->parent = old;
        return;
    }
    old->right = newnode;
    old->right->parent = old;
}

void inorder(struct node *root){
    if(root != NULL){
        inorder(root->left);
        printf("%i\t", root->val);
        inorder(root->right);
    }
}

void display(struct node *tree){
    inorder(tree);
    printf("\n");
}

void del_inorder(struct node *root){
    if(root != NULL){
        del_inorder(root->left);
        if((root->left == NULL && root->right == NULL) || (root->left == NULL && root->right != NULL) || (root->left == NULL && root->right != NULL)){
            if(max == NULL){max = root;}
            else{
                if(max->val > root->val){
                    max = root;
                }
            }
        }
        del_inorder(root->right);
    }
}

void delete(struct node **root, int val){
    if(*root == NULL){
        printf("No solution\n");
    }
    struct node *temp, *old;

    if((*root)->val == val){temp = *root;}
    else{
        struct node *find;
        find = *root;
        while(find->val != val){
            if(find->val < val){find = find->right;}
            else{find = find->left;}
        }
        temp = find;
    }
    
    if(temp->left == NULL && temp->right == NULL){
        int w;
        struct node *parent;
        if(temp->parent->val < temp->val){w = 2;}
        else{w = 1;}
        parent = temp->parent;
        free(temp);
        if(w == 2){parent->right = NULL;}
        else{parent->left = NULL;}
    }
    else if(temp->left != NULL && temp->right == NULL){
        old = temp->left;
        temp->val = old->val;
        temp->left = old->left;
        temp->right = old->right;
        free(old);
    }
    else if((*root)->left == NULL && (*root)->right != NULL){
        old = (*root)->right;
        temp->val = old->val;
        temp->left = old->left;
        temp->right = old->right;
        free(old);
    }
    else{
        old = (*root)->right;
        del_inorder(old);
        if(max->left != NULL){
            if(max->val < max->parent->val){
                max->parent->left = max->left;
            }
            else{
                max->parent->right = max->left;
            }
        }
        else{
            if(max->val < max->parent->val){
                max->parent->left = max->right;
            }
            else{
                max->parent->right = max->right;
            }
        }
        max->left = NULL;
        max->right = NULL;
        max->parent = NULL;
        temp->val = max->val;
        free(max);
        max = NULL;
    }
}

void _destruct(struct node *root){
    if(root != NULL){
        _destruct(root->left);
        free(root);
        _destruct(root->right);
    }
}

void destruct(struct node **root){
    _destruct(*root);
    *root = NULL;
}