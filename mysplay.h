#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>

using namespace std;

class node
{
public:
    node *left, *right;
    int size;
    int data;
};

int size(node *x)
{
    if(x == nullptr) return 0;
    else return x->size;
}

int left_size(node *x)
{
    if(x == nullptr) return 0;
    if(x->left == nullptr) return 0;
    else return x->left->size;
}

node *newNode(int data)
{
    node* x = (node*)malloc(sizeof(node));
    x->left = x->right = nullptr;
    x->data  = data;
    x->size = 1;
    return x;
}

void update(node *x)
{
    x->size = size(x->left)+size(x->right)+1;
}

node *rightRotate(node *x)
{
    node *y = x->left;
    x->left = y->right;
    y->right = x;

    update(x);
    update(y);
    return y;
}

node *leftRotate(node *x)
{
    node *y = x->right;
    x->right = y->left;
    y->left = x;

    update(x);
    update(y);
    return y;
}

node *splay(node *root, int s)
{
    if (root == nullptr || left_size(root)+1 == s)
        return root;

    if (left_size(root) >= s)
    {
        if (left_size(root->left) >= s)
        {
            root->left->left = splay(root->left->left, s);
            root = rightRotate(root);
        }
        else if (left_size(root->left)+1 < s) // Zig-Zag (Left Right)
        {
            root->left->right = splay(root->left->right, s-left_size(root->left)-1);

            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }

        return (root->left == nullptr)? root: rightRotate(root);
    }
    else
    {
        s = s-left_size(root)-1;
        if (left_size(root->right) >= s)
        {
            root->right->left = splay(root->right->left, s);

            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }
        else if (left_size(root->right)+1 < s)
        {
            root->right->right = splay(root->right->right, s-left_size(root->right)-1);
            root = leftRotate(root);
        }

        return (root->right == nullptr)? root: leftRotate(root);
    }
}

node *left_insert(node *root, node *ins)
{
    if(root == nullptr) return root;
    if(left_insert(root->left, ins) == nullptr) root->left = ins;
    update(root);
    return root;
}

node *insert(node *root, int s, int data)
{
    node *newnode = newNode(data);

    if (root == nullptr) return newnode;

    if(s <= 1) return left_insert(root, newnode);

    if(s > size(root)) s = size(root)+1;

    s = s-1;
    root = splay(root, s);

    newnode->right = root->right;
    root->right = newnode;

    update(newnode);
    update(root);

    return root;
}


node* del(node *root, int s)
{
    node *temp;
    if (!root)
        return nullptr;

    root = splay(root, s);

    if (!root->left)
    {
        temp = root;
        root = root->right;
    }
    else
    {
        temp = root;
        root = splay(root->left, s-1);
        root->right = temp->right;
    }

    free(temp);
    return root;
}

void preOrder(node *root)
{
    if (root != nullptr)
    {
        preOrder(root->left);
        printf("%d ", root->data);
        preOrder(root->right);
    }
}
