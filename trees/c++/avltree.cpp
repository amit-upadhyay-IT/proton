#include<iostream>
#include<stdlib.h>

struct AVLnode
{
    int data, height;
    AVLnode *left, *right;
};

AVLnode* single_left_rotation(AVLnode* X)
{
    AVLnode* W = X->left;
    X->left = W->right;
    W->right = X;
    X->height = std::max(X->left->height, X->right->height)+1;
    W->height = std::max(W->left->height, W->right->height)+1;
    return W;
}

AVLnode* single_right_rotate(AVLnode* W)
{
    AVLnode* X = W->right;
    W->right = X->left;
    X->left = W;
    X->height = std::max(X->left->height, X->right->height)+1;
    W->height = std::max(W->left->height, W->right->height)+1;
    return X;
}

AVLnode* left_right_rotate(AVLnode* Z)
{
    Z->left = single_right_rotate(Z->left);
    return single_left_rotation(Z);
}

AVLnode* right_left_rotate(AVLnode* Z)
{
    Z->right = single_left_rotation(Z->right);
    return single_right_rotate(Z);
}

AVLnode* insert(AVLnode* root, AVLnode* parent, int data)
{
    // case 1, first time insertion
    if (!root)
    {
        root = (AVLnode*)malloc(sizeof(AVLnode*));
        root->data = data;
        root->height = 0;
        root->left = root->right = NULL;
    }
    // case 2, when we already have some elements
    else if (data < root->data)
    {
        root->left = insert(root->left, root, data);
        if (root->left->height - root->right->height == 2)
        {
            if (data < root->left->data)// we need to do single left rotation
                root = single_left_rotation(root);
            else
                root = left_right_rotate(root);
        }
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, root, data);
        if (data > root->right->data)
            root = single_right_rotate(root);
        else
            root = right_left_rotate(root);
    }
    // data is in the tree already
    root->height = std::max(root->left->height, root->right->height) + 1;
    return root;
}

void preorder(AVLnode* root)
{
    if (root)
    {
        std::cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }
}

int main()
{

    AVLnode *root = NULL;

    root = insert(root, root, 100);
    root = insert(root, root, 80);
    root = insert(root, root, 70);
    root = insert(root, root, 60);
    root = insert(root, root, 50);

    preorder(root);

    return 0;
}
